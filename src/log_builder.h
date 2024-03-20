#ifndef KERO_LOG_LOG_BUILDER_H
#define KERO_LOG_LOG_BUILDER_H

#include "core.h"
#include "kero_mpsc.h"
#include "logger.h"
#include <source_location>
#include <sstream>

namespace kero {
namespace log {

class LogBuilder {
public:
  LogBuilder(std::string&& message, std::source_location&& location,
             const Level level);
  ~LogBuilder() = default;
  KERO_STRUCT_TYPE_PIN(LogBuilder);

  template <typename T>
  [[nodiscard]] auto Data(std::string&& key, T&& value) -> LogBuilder&;

  auto Log(Logger& logger = LocalLogger()) -> void;

private:
  std::unique_ptr<kero::log::Log> log_;
};

[[nodiscard]] auto
Debug(std::string&& message,
      std::source_location&& location = std::source_location::current())
    -> LogBuilder;

[[nodiscard]] auto
Info(std::string&& message,
     std::source_location&& location = std::source_location::current())
    -> LogBuilder;

[[nodiscard]] auto
Warn(std::string&& message,
     std::source_location&& location = std::source_location::current())
    -> LogBuilder;

[[nodiscard]] auto
Error(std::string&& message,
      std::source_location&& location = std::source_location::current())
    -> LogBuilder;

template <typename T>
auto LogBuilder::Data(std::string&& key, T&& value) -> LogBuilder& {
  std::stringstream ss;
  ss << std::forward<T>(value);

  auto entry = log_->data.find(key);
  if (entry != log_->data.end()) {
    kero::log::Debug("Overwriting existing data key").Data("key", key).Log();

    entry->second = ss.str();
  } else {
    log_->data.emplace(std::move(key), ss.str());
  }

  return *this;
}

} // namespace log
} // namespace kero

#endif // KERO_LOG_LOG_BUILDER_H