#ifndef KERO_LOG_H
#define KERO_LOG_H

#include "kero_mpsc.h"
#include <source_location>
#include <sstream>
#include <thread>
#include <unordered_map>

namespace kero {
namespace log {

enum class Level : int8_t {
  kError = 0,
  kWarn = 10,
  kInfo = 20,
  kDebug = 30,
};

namespace impl {

struct Event {
  std::unordered_map<std::string, std::string> data{};
  std::string category{};
  std::string message;
  std::source_location location;
  Level level;

  Event(std::string &&message, std::source_location &&location,
        const Level level);
  Event(Event &&) = default;
  ~Event() = default;
  auto operator=(Event &&) -> Event & = default;

  Event(const Event &) = delete;
  auto operator=(const Event &) -> Event & = delete;
};

} // namespace impl

using Event = std::unique_ptr<impl::Event>;

class Sender {
public:
  Sender(std::string &&category, kero::mpsc::Tx<Event> &&tx);
  Sender(Sender &&) = default;
  ~Sender() = default;
  auto operator=(Sender &&) -> Sender & = default;

  Sender(const Sender &) = delete;
  auto operator=(const Sender &) -> Sender & = delete;

  auto Send(Event &&event) -> void;

private:
  std::string category_;
  kero::mpsc::Tx<Event> tx_;
};

auto LocalSender() -> Sender &;

class Builder {
public:
  Builder(std::string &&message, std::source_location &&location,
          const Level level);
  ~Builder() = default;

  Builder(Builder &&) = delete;
  Builder(const Builder &) = delete;
  auto operator=(Builder &&) -> Builder & = delete;
  auto operator=(const Builder &) -> Builder & = delete;

  template <typename T>
  [[nodiscard]] auto Data(std::string &&key, T &&value) -> Builder & {
    if (auto it = event_->data.find(key); it != event_->data.end()) {
      // TODO: debug log with key and value
    }

    std::stringstream ss;
    ss << std::forward<T>(value);
    event_->data[std::move(key)] = ss.str();
    return *this;
  }

  auto Send(Sender &sender) -> void;

private:
  Event event_;
};

[[nodiscard]] auto
Debug(std::string &&message,
      std::source_location &&location = std::source_location::current())
    -> Builder;

[[nodiscard]] auto
Info(std::string &&message,
     std::source_location &&location = std::source_location::current())
    -> Builder;

[[nodiscard]] auto
Warn(std::string &&message,
     std::source_location &&location = std::source_location::current())
    -> Builder;

[[nodiscard]] auto
Error(std::string &&message,
      std::source_location &&location = std::source_location::current())
    -> Builder;

class Center {
public:
  Center();
  ~Center() = default;
  Center(Center &&) = default;
  auto operator=(Center &&) -> Center & = default;

  Center(const Center &) = delete;
  auto operator=(const Center &) -> Center & = delete;

  auto CreateSender(std::string &&category = "") -> Sender;

  auto RunOnThread() -> std::thread;
  auto Poll() -> void;

private:
  kero::mpsc::Channel<Event> channel_;
};

auto GlobalCenter() -> Center &;

} // namespace log
} // namespace kero

#endif // KERO_LOG_H
