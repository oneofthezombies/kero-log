#ifndef KERO_LOG_INTERNAL_RUNNER_EVENT_H
#define KERO_LOG_INTERNAL_RUNNER_EVENT_H

#include "core.h"
#include <variant>

namespace kero {
namespace log {
namespace runner_event {

struct Shutdown {
  ShutdownConfig config;

  Shutdown(ShutdownConfig&& config) noexcept;
  Shutdown(Shutdown&&) noexcept = default;
  ~Shutdown() noexcept = default;
  auto operator=(Shutdown&&) noexcept -> Shutdown& = default;

  Shutdown(const Shutdown&) = delete;
  auto operator=(const Shutdown&) -> Shutdown& = delete;
};

} // namespace runner_event

using RunnerEvent = std::variant<runner_event::Shutdown>;

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_RUNNER_EVENT_H
