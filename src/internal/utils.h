#ifndef KERO_LOG_INTERNAL_UTILS_H
#define KERO_LOG_INTERNAL_UTILS_H

#include "kero_mpsc.h"

namespace kero {
namespace log {

template <typename> inline constexpr bool always_false_v = false;

class NullStream : public std::ostream {
public:
  NullStream() noexcept;
  ~NullStream() noexcept = default;
  KERO_STRUCT_TYPE_PIN(NullStream);

private:
  class NullBuffer : public std::streambuf {
  public:
    NullBuffer() noexcept = default;
    ~NullBuffer() noexcept = default;
    KERO_STRUCT_TYPE_PIN(NullBuffer);

    virtual auto overflow(int c) noexcept -> int override;
  };

  NullBuffer null_buffer{};
};

auto ThreadIdToString(const std::thread::id& thread_id) -> std::string;

auto TimePointToIso8601(const std::chrono::system_clock::time_point& time_point)
    -> std::string;

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_UTILS_H
