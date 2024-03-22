#include "error_code.h"

namespace kero {
namespace log {

auto operator<<(std::ostream& os, ErrorCode code) -> std::ostream& {
  os << static_cast<std::underlying_type_t<ErrorCode>>(code);
  return os;
}

} // namespace log
} // namespace kero
