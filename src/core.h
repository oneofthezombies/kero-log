#ifndef KERO_LOG_CORE_H
#define KERO_LOG_CORE_H

#include "kero_mpsc.h"
#include <chrono>
#include <source_location>
#include <unordered_map>

namespace kero {
namespace log {

auto TimePointToIso8601(const std::chrono::system_clock::time_point& time_point)
    -> std::string;

enum class Level : int8_t {
  kError = 0,
  kWarn = 10,
  kInfo = 20,
  kDebug = 30,
};

auto LevelToString(const Level level) -> std::string;

struct Log {
  std::unordered_map<std::string, std::string> data{};
  std::string category{};
  std::string message;
  std::source_location location;
  Level level;

  Log(std::string&& message, std::source_location&& location,
      const Level level);
  ~Log() = default;
  KERO_STRUCT_TYPE_MOVE(Log);
};

struct ShutdownConfig {
  std::chrono::milliseconds timeout;

  ShutdownConfig();
  ~ShutdownConfig() = default;
  KERO_STRUCT_TYPE_MOVE(ShutdownConfig);
};

class Transport {
public:
  Transport() = default;
  virtual ~Transport() = default;
  KERO_STRUCT_TYPE_MOVE(Transport);

  virtual auto OnLog(const Log& log) -> void = 0;
};

class ConsoleTransport : public Transport {
public:
  ConsoleTransport() = default;
  virtual ~ConsoleTransport() = default;
  KERO_STRUCT_TYPE_MOVE(ConsoleTransport);

  auto OnLog(const Log& log) -> void override;
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_CORE_H
