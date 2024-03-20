#include "core.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace kero {
namespace log {

auto TimePointToIso8601(const std::chrono::system_clock::time_point& time_point)
    -> std::string {
  auto timer = std::chrono::system_clock::to_time_t(time_point);
  std::tm tm_utc{};
  gmtime_r(&timer, &tm_utc);
  std::stringstream ss;
  ss << std::put_time(&tm_utc, "%FT%TZ");
  return ss.str();
}

auto LevelToString(const Level level) -> std::string {
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
    return "unknown";
  }
}

Log::Log(std::string&& message, std::source_location&& location,
         const Level level)
    : message(std::move(message)), location(std::move(location)), level(level) {
}

ShutdownConfig::ShutdownConfig() : timeout{std::chrono::milliseconds{1000}} {}

auto ConsoleTransport::OnLog(const Log& log) -> void {
  const auto datetime = TimePointToIso8601(std::chrono::system_clock::now());
  std::cout << datetime << " " << LevelToString(log.level) << " "
            << log.location.file_name() << ":" << log.location.line() << ":"
            << log.location.column() << " " << log.location.function_name()
            << " " << log.message << std::endl;
}

} // namespace log
} // namespace kero
