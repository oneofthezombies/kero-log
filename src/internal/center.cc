#include "center.h"

#include "global_context.h"

namespace kero {
namespace log {

auto Center::UseSystemErrorStream(std::ostream& stream) noexcept -> void {
  GetGlobalContext().UseSystemErrorStream(stream);
}

auto Center::Shutdown(ShutdownConfig&& config) noexcept -> void {
  GetGlobalContext().Shutdown(std::move(config));
}

auto Center::AddTransport(std::unique_ptr<Transport>&& transport) noexcept
    -> void {
  GetGlobalContext().AddTransport(std::move(transport));
}

} // namespace log
} // namespace kero
