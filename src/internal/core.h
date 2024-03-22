#ifndef KERO_LOG_INTERNAL_CORE_H
#define KERO_LOG_INTERNAL_CORE_H

#include "../kero_common.h"
#include "error_code.h"
#include "kero_mpsc.h"
#include <source_location>
#include <unordered_map>

namespace kero {
namespace log {

template <typename T> using Result = kero::Result<T, kero::Error<ErrorCode>>;

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
  ~Log() noexcept = default;
  KERO_STRUCT_TYPE_MOVE(Log);
};

struct ShutdownConfig {
  std::chrono::milliseconds timeout;

  ShutdownConfig() noexcept;
  ShutdownConfig(std::chrono::milliseconds&& timeout) noexcept;
  ~ShutdownConfig() noexcept = default;
  KERO_STRUCT_TYPE_MOVE(ShutdownConfig);
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_CORE_H
