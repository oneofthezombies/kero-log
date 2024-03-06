#include "kero_log.h"
#include "kero_mpsc.h"

namespace kero {
namespace log {

Event::Event(std::source_location &&location, std::string &&message,
             const Level level)
    : location_(location), message_(message), level_(level) {}

Sender::Sender(std::source_location &&location, std::string &&message,
               const Level level)
    : event_{std::move(location), std::move(message), level} {}

auto Sender::send() -> void {
  if (sent_) {
    // TODO: debug log with message
    return;
  }

  sent_ = true;
}

auto Local::debug(std::string &&message, std::source_location &&location) const
    -> Sender {
  return Sender{std::move(location), std::move(message), Level::Debug};
}

auto Local::info(std::string &&message, std::source_location &&location) const
    -> Sender {
  return Sender{std::move(location), std::move(message), Level::Info};
}

auto Local::warn(std::string &&message, std::source_location &&location) const
    -> Sender {
  return Sender{std::move(location), std::move(message), Level::Warn};
}

auto Local::error(std::string &&message, std::source_location &&location) const
    -> Sender {
  return Sender{std::move(location), std::move(message), Level::Error};
}

auto local() -> const Local & {
  thread_local Local local{};
  return local;
}

Center::Center(kero::mpsc::Tx<Event> &&tx, kero::mpsc::Rx<Event> &&rx)
    : tx_{std::move(tx)}, rx_{std::move(rx)} {}

auto CreateCenter() -> Center {
  auto [tx, rx] = kero::mpsc::channel<Event>();
  return Center{std::move(tx), std::move(rx)};
}

auto center() -> Center & {
  static Center center = CreateCenter();
  return center;
}

auto example() -> void {
  auto &center = kero::log::center();
  kero::log::local().debug("").data("", 1).send();
}

} // namespace log
} // namespace kero
