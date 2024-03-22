#ifndef KERO_LOG_INTERNAL_GLOBAL_CONTEXT_H
#define KERO_LOG_INTERNAL_GLOBAL_CONTEXT_H

#include "core.h"
#include "kero_spsc.h"
#include "runner_event.h"
#include "transport.h"
#include "utils.h"
#include <iostream>
#include <memory>
#include <unordered_map>

namespace kero {
namespace log {

class GlobalContext {
public:
  class Builder {
  public:
    Builder() noexcept = default;
    ~Builder() noexcept = default;
    KERO_STRUCT_TYPE_PIN(Builder);

    auto Build() const noexcept -> std::unique_ptr<GlobalContext>;
  };

  struct SharedState {
    std::unordered_map<std::string, spsc::Rx<std::unique_ptr<kero::log::Log>>>
        log_rx_map{};
    std::deque<std::unique_ptr<kero::log::Log>> orphaned_logs{};
    std::vector<std::unique_ptr<Transport>> transports{};
    std::reference_wrapper<std::ostream> system_error_stream;

    SharedState(std::ostream& system_error_stream) noexcept;
    ~SharedState() noexcept = default;
    KERO_STRUCT_TYPE_PIN(SharedState);
  };

  ~GlobalContext() noexcept = default;
  KERO_STRUCT_TYPE_PIN(GlobalContext);

  auto UseSystemErrorStream(std::ostream& stream) noexcept -> void;
  auto LogSystemError(std::string&& message) noexcept -> void;

  auto AddLogRx(const std::string& thread_id,
                spsc::Rx<std::unique_ptr<kero::log::Log>>&& log_rx) noexcept
      -> Result<void>;
  auto RemoveLogRx(const std::string& thread_id) noexcept -> Result<void>;

  auto Shutdown(ShutdownConfig&& config) noexcept -> void;
  auto AddTransport(std::unique_ptr<Transport>&& transport) noexcept -> void;
  auto IsLogsEmpty() const noexcept -> bool;
  auto ConsumeLog() noexcept -> void;

private:
  GlobalContext(mpsc::Tx<std::unique_ptr<RunnerEvent>>&& runner_event_tx,
                std::thread&& runner_thread) noexcept;

  NullStream null_stream_{};
  SharedState shared_state_;
  mutable std::mutex shared_state_mutex_{};
  mpsc::Tx<std::unique_ptr<RunnerEvent>> runner_event_tx_;
  std::thread runner_thread_;
};

auto GetGlobalContext() -> GlobalContext&;

auto RunOnThread(mpsc::Rx<std::unique_ptr<RunnerEvent>>&& runner_event_rx)
    -> void;

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_GLOBAL_CONTEXT_H
