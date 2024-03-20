#include "runner.h"

#include "../log_builder.h"
#include <optional>

namespace kero {
namespace log {
namespace internal {

template <typename> inline constexpr bool always_false_v = false;

auto Runner::Builder::Build(mpsc::Rx<std::unique_ptr<Event>>&& event_rx)
    -> Runner {

  auto thread = std::thread([event_rx = std::move(event_rx)]() {
    auto log_level = Level::kInfo;
    std::optional<std::chrono::steady_clock::time_point> shutdown_deadline{};
    auto transports = std::vector<std::unique_ptr<Transport>>{};

    while (true) {
      const auto shutdown_requested = shutdown_deadline.has_value();
      if (shutdown_requested &&
          std::chrono::steady_clock::now() > *shutdown_deadline) {
        break;
      }

      auto event_opt = event_rx.TryReceive();
      if (shutdown_requested && !event_opt) {
        break;
      }

      if (!event_opt) {
        continue;
      }

      auto& event_ptr = *event_opt;
      if (!event_ptr) {
        kero::log::Debug("event must not be null").Log();
        continue;
      }

      std::visit(
          [&log_level, &shutdown_deadline, &transports](auto&& event) {
            using T = std::decay_t<decltype(event)>;

            if constexpr (std::is_same_v<T, event::SetLogLevel>) {
              event::SetLogLevel& event_set_log_level = event;
              log_level = event_set_log_level.level;
            } else if constexpr (std::is_same_v<T, event::Shutdown>) {
              if (shutdown_deadline) {
                kero::log::Debug("shutdown already scheduled").Log();
                return;
              }

              event::Shutdown& shutdown = event;
              shutdown_deadline =
                  std::chrono::steady_clock::now() + shutdown.timeout;
            } else if constexpr (std::is_same_v<T, event::AddTransport>) {
              event::AddTransport& event_add_transport = event;
              transports.push_back(std::move(event_add_transport.transport));
            } else if constexpr (std::is_same_v<T, event::Log>) {
              event::Log& event_log = event;
              if (!event_log.log) {
                kero::log::Debug("log must not be null").Log();
                return;
              }

              const kero::log::Log& log = *event_log.log;
              if (log.level > log_level) {
                return;
              }

              for (const auto& transport : transports) {
                if (!transport) {
                  kero::log::Debug("transport must not be null").Log();
                  continue;
                }

                transport->OnLog(log);
              }
            } else {
              static_assert(always_false_v<T>, "non-exhaustive visitor!");
            }
          },
          *event_ptr);
    }
  });

  return Runner{std::move(thread)};
}

Runner::Runner(std::thread&& thread) : thread_{std::move(thread)} {}

auto Runner::Wait() -> void { thread_.join(); }

} // namespace internal
} // namespace log
} // namespace kero
