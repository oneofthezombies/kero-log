#include "global_context.h"

#include "core.h"
#include "runner_event.h"
#include "transport.h"
#include <iostream>

namespace kero {
namespace log {

auto GlobalContext::Builder::Build() const noexcept
    -> std::unique_ptr<GlobalContext> {
  auto [runner_event_tx, runner_event_rx] =
      mpsc::Channel<std::unique_ptr<RunnerEvent>>::Builder{}.Build();
  auto runner_thread = std::thread{RunOnThread, std::move(runner_event_rx)};
  return std::unique_ptr<GlobalContext>{
      new GlobalContext{std::move(runner_event_tx), std::move(runner_thread)}};
}

GlobalContext::SharedState::SharedState(
    std::ostream& system_error_stream) noexcept
    : system_error_stream{system_error_stream} {}

GlobalContext::GlobalContext(
    mpsc::Tx<std::unique_ptr<RunnerEvent>>&& runner_event_tx,
    std::thread&& runner_thread) noexcept
    : shared_state_{null_stream_}, runner_event_tx_{std::move(runner_event_tx)},
      runner_thread_{std::move(runner_thread)} {}

auto GlobalContext::UseSystemErrorStream(std::ostream& stream) noexcept
    -> void {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);
  shared_state_.system_error_stream = std::ref(stream);
}

auto GlobalContext::LogSystemError(std::string&& message) noexcept -> void {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);
  shared_state_.system_error_stream.get() << message << std::endl;
}

auto GlobalContext::AddLogRx(
    const std::string& thread_id,
    spsc::Rx<std::unique_ptr<kero::log::Log>>&& log_rx) noexcept
    -> Result<void> {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);
  if (shared_state_.log_rx_map.find(thread_id) !=
      shared_state_.log_rx_map.end()) {
    return Result<void>{Error{ErrorCode::kLogRxAlreadyRegistered,
                              "Key " + thread_id + " already exists"}};
  }

  shared_state_.log_rx_map.emplace(thread_id, std::move(log_rx));
  return Result<void>{};
}

auto GlobalContext::RemoveLogRx(const std::string& thread_id) noexcept
    -> Result<void> {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);
  auto entry = shared_state_.log_rx_map.find(thread_id);
  if (entry == shared_state_.log_rx_map.end()) {
    return Result<void>{
        Error{ErrorCode::kLogRxNotFound, "Key " + thread_id + " not found"}};
  }

  while (auto log = entry->second.TryReceive()) {
    shared_state_.orphaned_logs.push_back(std::move(*log));
  }

  shared_state_.log_rx_map.erase(thread_id);
  return Result<void>{};
}

auto GlobalContext::Shutdown(ShutdownConfig&& config) noexcept -> void {
  runner_event_tx_.Send(
      std::make_unique<RunnerEvent>(runner_event::Shutdown{std::move(config)}));
  runner_thread_.join();
}

auto GlobalContext::AddTransport(
    std::unique_ptr<Transport>&& transport) noexcept -> void {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);
  shared_state_.transports.push_back(std::move(transport));
}

auto GlobalContext::IsLogsEmpty() const noexcept -> bool {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);
  if (!shared_state_.orphaned_logs.empty()) {
    return false;
  }
  for (const auto& [thread_id, log_rx] : shared_state_.log_rx_map) {
    if (!log_rx.IsEmpty()) {
      return false;
    }
  }
  return true;
}

auto GlobalContext::ConsumeLog() noexcept -> void {
  std::lock_guard<std::mutex> lock(shared_state_mutex_);

  auto consume = [this](const std::unique_ptr<kero::log::Log>& log_ptr) {
    if (!log_ptr) {
      shared_state_.system_error_stream.get()
          << "Internal: log_ptr must not be null." << std::endl;
      return;
    }

    for (auto& transport : shared_state_.transports) {
      if (log_ptr->level > transport->GetLevel()) {
        continue;
      }

      transport->OnLog(*log_ptr);
    }
  };

  if (!shared_state_.orphaned_logs.empty()) {
    auto log = std::move(shared_state_.orphaned_logs.front());
    shared_state_.orphaned_logs.pop_front();

    consume(log);
    return;
  }

  for (const auto& [thread_id, log_rx] : shared_state_.log_rx_map) {
    auto log = log_rx.TryReceive();
    if (!log) {
      continue;
    }

    consume(*log);
    return;
  }
}

auto GetGlobalContext() -> GlobalContext& {
  static std::unique_ptr<GlobalContext> global_context{nullptr};
  static std::once_flag flag{};
  std::call_once(flag,
                 []() { global_context = GlobalContext::Builder{}.Build(); });
  return *global_context;
}

auto RunOnThread(mpsc::Rx<std::unique_ptr<RunnerEvent>>&& runner_event_rx)
    -> void {
  std::optional<std::chrono::steady_clock::time_point> shutdown_deadline{};

  while (true) {
    const auto shutdown_requested = shutdown_deadline.has_value();
    if (shutdown_requested &&
        std::chrono::steady_clock::now() > *shutdown_deadline) {
      break;
    }

    auto event_opt = runner_event_rx.TryReceive();
    if (shutdown_requested && !event_opt && GetGlobalContext().IsLogsEmpty()) {
      break;
    }

    if (event_opt) {
      auto& event_ptr = *event_opt;
      if (!event_ptr) {
        GetGlobalContext().LogSystemError(
            "Internal: event_ptr must not be null.");
        continue;
      }

      std::visit(
          [&shutdown_deadline](auto&& event) {
            using T = std::decay_t<decltype(event)>;

            if constexpr (std::is_same_v<T, runner_event::Shutdown>) {
              if (shutdown_deadline) {
                GetGlobalContext().LogSystemError(
                    "Shutdown already scheduled.");
                return;
              }

              runner_event::Shutdown& shutdown = event;
              shutdown_deadline =
                  std::chrono::steady_clock::now() + shutdown.config.timeout;
            } else {
              static_assert(always_false_v<T>,
                            "every RunnerEvent must be handled.");
            }
          },
          *event_ptr);
    }

    GetGlobalContext().ConsumeLog();
  }
}

} // namespace log
} // namespace kero