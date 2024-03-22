#include "runner_event.h"

namespace kero {
namespace log {
namespace runner_event {

Shutdown::Shutdown(ShutdownConfig&& config) noexcept
    : config{std::move(config)} {}

} // namespace runner_event
} // namespace log
} // namespace kero
