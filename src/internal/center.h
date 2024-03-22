#ifndef KERO_LOG_INTERNAL_CENTER_H
#define KERO_LOG_INTERNAL_CENTER_H

#include "kero_mpsc.h"
#include "transport.h"
#include <iostream>

namespace kero {
namespace log {

class Center {
public:
  Center() noexcept = default;
  ~Center() noexcept = default;
  KERO_STRUCT_TYPE_PIN(Center);

  auto UseSystemErrorStream(std::ostream& stream = std::cerr) noexcept -> void;
  auto Shutdown(ShutdownConfig&& config = ShutdownConfig{}) noexcept -> void;
  auto AddTransport(std::unique_ptr<Transport>&& transport) noexcept -> void;
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_CENTER_H
