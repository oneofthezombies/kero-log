#include "kero_log.h"
#include "kero_mpsc.h"

#include <iostream>

namespace kero {
namespace log {

namespace impl {

Event::Event(std::string &&message, std::source_location &&location,
             const Level level)
    : message(std::move(message)), location(std::move(location)), level(level) {
}

} // namespace impl

Sender::Sender(std::string &&category, kero::mpsc::Tx<Event> &&tx)
    : category_(std::move(category)), tx_(std::move(tx)) {}

auto Sender::Send(Event &&event) -> void {
  event->category = category_;
  tx_.Send(std::move(event));
}

auto LocalSender() -> Sender & {
  thread_local std::unique_ptr<Sender> sender{nullptr};
  thread_local std::once_flag flag{};
  std::call_once(flag, []() {
    auto ss = std::stringstream{};
    ss << "thread-" << std::this_thread::get_id();
    sender.reset(new Sender{GlobalCenter().CreateSender(ss.str())});
  });
  return *sender;
}

Builder::Builder(std::string &&message, std::source_location &&location,
                 const Level level)
    : event_{std::make_unique<impl::Event>(std::move(message),
                                           std::move(location), level)} {}

auto Builder::Send(Sender &sender) -> void {
  if (!event_) {
    // TODO: log error
    return;
  }

  sender.Send(std::move(event_));
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

Center::Center() : channel_{kero::mpsc::Channel<Event>::Builder{}.Build()} {}

auto Center::CreateSender(std::string &&category) -> Sender {
  return Sender{std::move(category), channel_.tx.Clone()};
}

auto Center::RunOnThread() -> std::thread {
  auto receiver = std::thread([rx = std::move(channel_.rx)]() {
    while (true) {
      auto event = rx.Receive();
      std::cout << "category: " << event->category << std::endl;
      std::cout << "message: " << event->message << std::endl;
    }
  });
  return receiver;
}

auto GlobalCenter() -> Center & {
  static std::unique_ptr<Center> center{nullptr};
  static std::once_flag flag{};
  std::call_once(flag, []() { center.reset(new Center{}); });
  return *center;
}

} // namespace log
} // namespace kero
