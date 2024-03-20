#include "log_builder.h"

namespace kero {
namespace log {

LogBuilder::LogBuilder(std::string&& message, std::source_location&& location,
                       const Level level)
    : log_{std::make_unique<kero::log::Log>(std::move(message),
                                            std::move(location), level)} {}

auto LogBuilder::Log(Logger& logger) -> void {
  if (!log_) {
    kero::log::Debug("log must not be null").Log();
    return;
  }

  logger.Log(std::move(log_));
}

auto Debug(std::string&& message, std::source_location&& location)
    -> LogBuilder {
  return LogBuilder{std::move(message), std::move(location), Level::kDebug};
}

auto Info(std::string&& message, std::source_location&& location)
    -> LogBuilder {
  return LogBuilder{std::move(message), std::move(location), Level::kInfo};
}

auto Warn(std::string&& message, std::source_location&& location)
    -> LogBuilder {
  return LogBuilder{std::move(message), std::move(location), Level::kWarn};
}

auto Error(std::string&& message, std::source_location&& location)
    -> LogBuilder {
  return LogBuilder{std::move(message), std::move(location), Level::kError};
}

} // namespace log
} // namespace kero
