#include "event.h"

namespace kero {
namespace log {
namespace internal {
namespace event {

SetLogLevel::SetLogLevel(const Level level) : level{level} {}

Shutdown::Shutdown(std::chrono::milliseconds&& timeout)
    : timeout{std::move(timeout)} {}

AddTransport::AddTransport(std::unique_ptr<Transport>&& transport)
    : transport{std::move(transport)} {}

Log::Log(std::unique_ptr<kero::log::Log>&& log) : log{std::move(log)} {}

} // namespace event
} // namespace internal
} // namespace log
} // namespace kero
