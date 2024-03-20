#include "logger.h"

#include "center.h"
#include <sstream>
#include <thread>

namespace kero {
namespace log {

Logger::Logger(std::string&& category,
               mpsc::Tx<std::unique_ptr<internal::Event>>&& event_tx)
    : category_(std::move(category)), event_tx_{std::move(event_tx)} {}

auto Logger::Log(std::unique_ptr<kero::log::Log>&& log) -> void {
  log->category = category_;
  event_tx_.Send(
      std::make_unique<internal::Event>(internal::event::Log{std::move(log)}));
}

auto LocalLogger(Center& center) -> Logger& {
  thread_local std::unique_ptr<Logger> logger{nullptr};
  thread_local std::once_flag flag{};
  std::call_once(flag, [&center]() {
    auto ss = std::stringstream{};
    ss << "thread-" << std::this_thread::get_id();
    logger.reset(new Logger{center.CreateLogger(ss.str())});
  });
  return *logger;
}

} // namespace log
} // namespace kero