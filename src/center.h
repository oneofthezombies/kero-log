#ifndef KERO_LOG_CENTER_H
#define KERO_LOG_CENTER_H

#include "internal/runner.h"

namespace kero {
namespace log {

class Logger;
enum class Level : int8_t;

class Center {
public:
  class Builder {
  public:
    Builder() = default;
    ~Builder() = default;
    KERO_STRUCT_TYPE_PIN(Builder);

    auto Build() -> Center;
  };

  ~Center() = default;
  KERO_STRUCT_TYPE_MOVE(Center);

  auto SetLogLevel(const Level level) -> void;
  auto Shutdown(ShutdownConfig&& config = ShutdownConfig{}) -> void;
  auto AddTransport(std::unique_ptr<Transport>&& transport) -> void;
  auto CreateLogger(std::string&& category = "") -> Logger;

private:
  Center(mpsc::Tx<std::unique_ptr<internal::Event>>&& event_tx,
         internal::Runner&& runner);

  mpsc::Tx<std::unique_ptr<internal::Event>> event_tx_;
  internal::Runner runner_;
};

auto GlobalCenter() -> Center&;

} // namespace log
} // namespace kero

#endif // KERO_LOG_CENTER_H
