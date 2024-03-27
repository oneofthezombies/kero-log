#ifndef KERO_LOG_KERO_COMMON_H
#define KERO_LOG_KERO_COMMON_H

/*
 * This file contains common types and functions that are used across the "kero"
 * namespace.
 */

#include <memory>
#include <ostream>
#include <string>

namespace kero {
namespace core {

template <typename T>
  requires std::is_enum_v<T>
struct Error {
  T code;
  std::string message;

  Error(const T code, std::string&& message) noexcept
      : code{code}, message{std::move(message)} {}
};

template <typename T>
auto operator<<(std::ostream& os, const Error<T>& error) noexcept
    -> std::ostream& {
  os << "Error code: " << error.code << " message: " << error.message;
  return os;
}

template <typename T, typename E> class Result {
public:
  Result(T&& value) noexcept
      : value_{std::make_unique<T>(std::move(value))}, error_{nullptr} {}
  Result(E&& error) noexcept
      : value_{nullptr}, error_{std::make_unique<E>(std::move(error))} {}

  auto IsOk() const noexcept -> bool { return !!value_; }
  auto IsErr() const noexcept -> bool { return !!error_; }

  auto Ok() noexcept -> std::unique_ptr<T> { return std::move(value_); }
  auto Err() noexcept -> std::unique_ptr<E> { return std::move(error_); }

private:
  std::unique_ptr<T> value_;
  std::unique_ptr<E> error_;
};

template <typename E> class Result<void, E> {
public:
  Result() noexcept : is_ok_{true}, error_{nullptr} {}
  Result(E&& error) noexcept
      : is_ok_{false}, error_{std::make_unique<E>(std::move(error))} {}

  auto IsOk() const noexcept -> bool { return is_ok_; }
  auto IsErr() const noexcept -> bool { return !!error_; }

  auto Err() noexcept -> std::unique_ptr<E> { return std::move(error_); }

private:
  bool is_ok_;
  std::unique_ptr<E> error_;
};

} // namespace core
} // namespace kero

#endif // KERO_LOG_KERO_COMMON_H
