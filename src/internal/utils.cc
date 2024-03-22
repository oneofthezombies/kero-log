#include "utils.h"

#include <iomanip>
#include <sstream>

namespace kero {
namespace log {

NullStream::NullStream() noexcept : std::ostream{&null_buffer} {}

auto NullStream::NullBuffer::overflow(int c) noexcept -> int { return c; }

auto ThreadIdToString(const std::thread::id& thread_id) -> std::string {
  std::stringstream ss;
  ss << thread_id;
  return ss.str();
}

auto TimePointToIso8601(const std::chrono::system_clock::time_point& time_point)
    -> std::string {
  auto timer = std::chrono::system_clock::to_time_t(time_point);
  std::tm tm_utc{};
  gmtime_r(&timer, &tm_utc);
  std::stringstream ss;
  ss << std::put_time(&tm_utc, "%FT%TZ");
  return ss.str();
}

} // namespace log
} // namespace kero
