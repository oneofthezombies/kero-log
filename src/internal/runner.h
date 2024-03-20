#ifndef KERO_LOG_INTERNAL_RUNNER_H
#define KERO_LOG_INTERNAL_RUNNER_H

#include "event.h"
#include "kero_mpsc.h"

namespace kero {
namespace log {
namespace internal {

class Runner {
public:
  class Builder {
  public:
    Builder() = default;
    ~Builder() = default;
    KERO_STRUCT_TYPE_PIN(Builder);

    auto Build(mpsc::Rx<std::unique_ptr<Event>>&& event_rx) -> Runner;
  };

  ~Runner() = default;
  KERO_STRUCT_TYPE_MOVE(Runner);

  auto Wait() -> void;

private:
  Runner(std::thread&& thread);

  std::thread thread_;
};

} // namespace internal
} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_RUNNER_H
