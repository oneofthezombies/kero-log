#include "log_builder.h"

#include "core.h"
#include "local_context.h"

namespace kero {
namespace log {

LogBuilder::LogBuilder(std::string&& message, std::source_location&& location,
                       const Level level) noexcept
    : log_{std::make_unique<kero::log::Log>(std::move(message),
                                            std::move(location), level)} {}

auto LogBuilder::Log() noexcept -> Result<void> {
  if (!log_) {
    return Result<void>{kero::core::Error{ErrorCode::kLogAlreadyConsumed,
                                          "Log already consumed, cannot log."}};
  }

  if (auto& local_context = GetLocalContext()) {
    local_context->SendLog(std::move(log_));
    return Result<void>{};
  } else {
    return Result<void>{
        kero::core::Error{ErrorCode::kLocalContextNotFound,
                          "Failed to get LocalContext, cannot log."}};
  }
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
