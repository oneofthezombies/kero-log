#ifndef KERO_LOG_INTERNAL_EVENT_H
#define KERO_LOG_INTERNAL_EVENT_H

#include "../core.h"
#include <variant>

namespace kero {
namespace log {
namespace internal {
namespace event {

struct SetLogLevel {
  Level level;

  SetLogLevel(const Level level);
  ~SetLogLevel() = default;
  KERO_STRUCT_TYPE_MOVE(SetLogLevel);
};

struct Shutdown {
  std::chrono::milliseconds timeout;

  Shutdown(std::chrono::milliseconds&& timeout);
  ~Shutdown() = default;
  KERO_STRUCT_TYPE_MOVE(Shutdown);
};

struct AddTransport {
  std::unique_ptr<Transport> transport;

  AddTransport(std::unique_ptr<Transport>&& transport);
  ~AddTransport() = default;
  KERO_STRUCT_TYPE_MOVE(AddTransport);
};

struct Log {
  std::unique_ptr<kero::log::Log> log;

  Log(std::unique_ptr<kero::log::Log>&& log);
  ~Log() = default;
  KERO_STRUCT_TYPE_MOVE(Log);
};

} // namespace event

using Event = std::variant<event::SetLogLevel,  //
                           event::Shutdown,     //
                           event::AddTransport, //
                           event::Log>;

} // namespace internal
} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_EVENT_H