#include "core.h"

namespace kero {
namespace log {

auto LevelToString(const Level level) noexcept -> std::string {
  switch (level) {
  case Level::kError:
    return "ERROR";
  case Level::kWarn:
    return "WARN";
  case Level::kInfo:
    return "INFO";
  case Level::kDebug:
    return "DEBUG";
  default:
    return "UNKNOWN";
  }
}

Log::Log(std::string&& message, std::source_location&& location,
         const Level level) noexcept
    : message(std::move(message)), location(std::move(location)), level(level) {
}

ShutdownConfig::ShutdownConfig() noexcept
    : timeout{std::chrono::milliseconds{1000}} {}

ShutdownConfig::ShutdownConfig(std::chrono::milliseconds&& timeout) noexcept
    : timeout{std::move(timeout)} {}

} // namespace log
} // namespace kero
