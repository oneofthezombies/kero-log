#ifndef KERO_LOG_INTERNAL_CORE_H
#define KERO_LOG_INTERNAL_CORE_H

#include "../kero_core.h"
#include "error_code.h"
#include <chrono>
#include <source_location>
#include <unordered_map>

namespace kero {
namespace log {

template <typename T>
using Result = kero::core::Result<T, kero::core::Error<ErrorCode>>;

enum class Level : int8_t {
  kError = 0,
  kWarn = 10,
  kInfo = 20,
  kDebug = 30,
};

auto LevelToString(const Level level) noexcept -> std::string;

struct Log {
  std::unordered_map<std::string, std::string> data{};
  std::string message;
  std::source_location location;
  Level level;

  Log(std::string&& message, std::source_location&& location,
      const Level level) noexcept;
  Log(Log&&) noexcept = default;
  ~Log() noexcept = default;
  auto operator=(Log&&) noexcept -> Log& = default;

  Log(const Log&) = delete;
  auto operator=(const Log&) -> Log& = delete;
};

struct ShutdownConfig {
  std::chrono::milliseconds timeout;

  ShutdownConfig() noexcept;
  ShutdownConfig(std::chrono::milliseconds&& timeout) noexcept;
  ShutdownConfig(ShutdownConfig&&) noexcept = default;
  ~ShutdownConfig() noexcept = default;
  auto operator=(ShutdownConfig&&) noexcept -> ShutdownConfig& = default;

  ShutdownConfig(const ShutdownConfig&) = delete;
  auto operator=(const ShutdownConfig&) -> ShutdownConfig& = delete;
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_CORE_H
