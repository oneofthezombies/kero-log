#include "kero_log.h"
#include "kero_mpsc.h"

#include <memory>

namespace kero {
namespace log {

Event::Event(std::string &&message, std::source_location &&location,
             const Level level)
    : message(std::move(message)), location(std::move(location)), level(level) {
}

Mail::Mail(Event &&event, std::string &&category)
    : event(std::move(event)), category(std::move(category)) {}

Sender::Sender(std::string &&category, kero::mpsc::Tx<Mail> &&tx)
    : category_(std::move(category)), tx_(std::move(tx)) {}

auto Sender::Send(Event &&event) -> void {
  auto category = category_;
  tx_.Send(Mail{std::move(event), std::move(category)});
}

Builder::Builder(std::string &&message, std::source_location &&location,
                 const Level level)
    : event_{std::move(message), std::move(location), level} {}

auto Builder::Send(Sender &sender) -> void {
  if (sent_) {
    // TODO: log error
    return;
  }

  sender.Send(std::move(event_));
  sent_ = true;
}

auto Debug(std::string &&message, std::source_location &&location) -> Builder {
  return Builder{std::move(message), std::move(location), Level::kDebug};
}

auto Info(std::string &&message, std::source_location &&location) -> Builder {
  return Builder{std::move(message), std::move(location), Level::kInfo};
}

auto Warn(std::string &&message, std::source_location &&location) -> Builder {
  return Builder{std::move(message), std::move(location), Level::kWarn};
}

auto Error(std::string &&message, std::source_location &&location) -> Builder {
  return Builder{std::move(message), std::move(location), Level::kError};
}

Center::Center() : channel_{kero::mpsc::Channel<Mail>::Builder{}.Build()} {}

auto Center::CreateSender(std::string &&category) -> Sender {
  return Sender{std::move(category), channel_.tx.Clone()};
}

auto GlobalCenter() -> Center & {
  static std::unique_ptr<Center> center{nullptr};
  static std::once_flag flag{};
  std::call_once(flag, []() { center.reset(new Center{}); });
  return *center;
}

} // namespace log
} // namespace kero
