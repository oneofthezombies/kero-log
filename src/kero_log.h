#ifndef KERO_LOG_H
#define KERO_LOG_H

#include "kero_mpsc.h"
#include <format>
#include <source_location>
#include <sstream>
#include <string_view>

namespace kero {
namespace log {

enum class Level : int8_t {
  Error = 0,
  Warn = 1,
  Info = 2,
  Debug = 3,
};

struct Event {
  Event(std::source_location &&location, std::string &&message,
        const Level level);
  Event(Event &&) = default;
  auto operator=(Event &&) -> Event & = default;
  ~Event() = default;

  Event(const Event &) = delete;
  auto operator=(const Event &) -> Event & = delete;

  std::unordered_map<std::string, std::string> data_;
  std::source_location location_;
  std::string message_;
  Level level_;
};

struct Sender {
  Sender(std::source_location &&location, std::string &&message,
         const Level level);
  ~Sender() = default;

  Sender(Sender &&) = delete;
  Sender(const Sender &) = delete;
  auto operator=(Sender &&) -> Sender & = delete;
  auto operator=(const Sender &) -> Sender & = delete;

  template <typename T>
  [[nodiscard]] auto data(std::string &&key, T &&value) -> Sender &;

  auto send() -> void;

private:
  Event event_;
  bool sent_{false};
};

struct Local {
  [[nodiscard]] auto
  debug(std::string &&message,
        std::source_location &&location = std::source_location::current()) const
      -> Sender;

  [[nodiscard]] auto
  info(std::string &&message,
       std::source_location &&location = std::source_location::current()) const
      -> Sender;

  [[nodiscard]] auto
  warn(std::string &&message,
       std::source_location &&location = std::source_location::current()) const
      -> Sender;

  [[nodiscard]] auto
  error(std::string &&message,
        std::source_location &&location = std::source_location::current()) const
      -> Sender;
};

auto local() -> const Local &;

struct Center {
  Center(kero::mpsc::Tx<Event> &&tx, kero::mpsc::Rx<Event> &&rx);
  ~Center() = default;

  Center(Center &&) = delete;
  Center(const Center &) = delete;
  auto operator=(Center &&) -> Center & = delete;
  auto operator=(const Center &) -> Center & = delete;

private:
  kero::mpsc::Tx<Event> tx_;
  kero::mpsc::Rx<Event> rx_;
};

auto center() -> Center &;

////////////////////////////////////////////////////////////////
// Template definitions begin
////////////////////////////////////////////////////////////////

template <typename T>
auto Sender::data(std::string &&key, T &&value) -> Sender & {
  if (auto it = event_.data_.find(key); it != event_.data_.end()) {
    // TODO: debug log with key and value
  }

  std::stringstream ss;
  ss << value;
  event_.data_[std::move(key)] = ss.str();
  return *this;
}

////////////////////////////////////////////////////////////////
// Template definitions end
////////////////////////////////////////////////////////////////

} // namespace log
} // namespace kero

#endif // KERO_LOG_H
