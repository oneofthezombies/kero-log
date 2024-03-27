#ifndef KERO_LOG_INTERNAL_UTILS_H
#define KERO_LOG_INTERNAL_UTILS_H

#include <ostream>
#include <thread>

namespace kero {
namespace log {

template <typename> inline constexpr bool always_false_v = false;

class NullStream : public std::ostream {
public:
  NullStream() noexcept;
  ~NullStream() noexcept = default;

  NullStream(NullStream&&) = delete;
  NullStream(const NullStream&) = delete;
  auto operator=(NullStream&&) -> NullStream& = delete;
  auto operator=(const NullStream&) -> NullStream& = delete;

private:
  class NullBuffer : public std::streambuf {
  public:
    NullBuffer() noexcept = default;
    ~NullBuffer() noexcept = default;

    NullBuffer(NullBuffer&&) = delete;
    NullBuffer(const NullBuffer&) = delete;
    auto operator=(NullBuffer&&) -> NullBuffer& = delete;
    auto operator=(const NullBuffer&) -> NullBuffer& = delete;

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
