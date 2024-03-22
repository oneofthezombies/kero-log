#ifndef KERO_LOG_INTERNAL_ERROR_CODE_H
#define KERO_LOG_INTERNAL_ERROR_CODE_H

#include <cstdint>
#include <ostream>

namespace kero {
namespace log {

enum class ErrorCode : int32_t {
  kUnknown = 0,
  kLogRxAlreadyRegistered = 1,
  kLogRxNotFound = 2,
  kLogAlreadyConsumed = 3,
  kLocalContextNotFound = 4,
};

auto operator<<(std::ostream& os, ErrorCode code) -> std::ostream&;

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_ERROR_CODE_H
