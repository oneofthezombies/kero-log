#include "center.h"

#include "logger.h"

namespace kero {
namespace log {

auto Center::Builder::Build() -> Center {
  auto [event_tx, event_rx] =
      mpsc::Channel<std::unique_ptr<internal::Event>>::Builder{}.Build();
  auto runner = internal::Runner::Builder{}.Build(std::move(event_rx));
  return Center{std::move(event_tx), std::move(runner)};
}

Center::Center(mpsc::Tx<std::unique_ptr<internal::Event>>&& event_tx,
               internal::Runner&& runner)
    : event_tx_{std::move(event_tx)}, runner_{std::move(runner)} {}

auto Center::SetLogLevel(const Level level) -> void {
  event_tx_.Send(
      std::make_unique<internal::Event>(internal::event::SetLogLevel{level}));
}

auto Center::Shutdown(ShutdownConfig&& config) -> void {
  event_tx_.Send(std::make_unique<internal::Event>(
      internal::event::Shutdown{std::move(config.timeout)}));
  runner_.Wait();
}

auto Center::AddTransport(std::unique_ptr<Transport>&& transport) -> void {
  event_tx_.Send(std::make_unique<internal::Event>(
      internal::event::AddTransport{std::move(transport)}));
}

auto Center::CreateLogger(std::string&& category) -> Logger {
  return Logger{std::move(category), event_tx_.Clone()};
}

auto GlobalCenter() -> Center& {
  static std::unique_ptr<Center> center{nullptr};
  static std::once_flag flag{};
  std::call_once(flag,
                 []() { center.reset(new Center{Center::Builder{}.Build()}); });
  return *center;
}

} // namespace log
} // namespace kero