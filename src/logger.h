#ifndef KERO_LOG_LOGGER_H
#define KERO_LOG_LOGGER_H

#include "center.h"

namespace kero {
namespace log {

class Center;

class Logger {
public:
  Logger(std::string&& name,
         mpsc::Tx<std::unique_ptr<internal::Event>>&& event_tx);
  ~Logger() = default;
  KERO_STRUCT_TYPE_MOVE(Logger);

  auto Log(std::unique_ptr<kero::log::Log>&& log) -> void;

private:
  std::string category_;
  mpsc::Tx<std::unique_ptr<internal::Event>> event_tx_;
};

auto LocalLogger(Center& center = GlobalCenter()) -> Logger&;

} // namespace log
} // namespace kero

#endif // KERO_LOG_LOGGER_H