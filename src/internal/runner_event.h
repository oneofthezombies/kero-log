#ifndef KERO_LOG_INTERNAL_RUNNER_EVENT_H
#define KERO_LOG_INTERNAL_RUNNER_EVENT_H

#include "core.h"
#include "kero_mpsc.h"
#include <variant>

namespace kero {
namespace log {
namespace runner_event {

struct Shutdown {
  ShutdownConfig config;

  Shutdown(ShutdownConfig&& config) noexcept;
  ~Shutdown() noexcept = default;
  KERO_STRUCT_TYPE_MOVE(Shutdown);
};

} // namespace runner_event

using RunnerEvent = std::variant<runner_event::Shutdown>;

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_RUNNER_EVENT_H
