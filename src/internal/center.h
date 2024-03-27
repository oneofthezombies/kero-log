#ifndef KERO_LOG_INTERNAL_CENTER_H
#define KERO_LOG_INTERNAL_CENTER_H

#include "transport.h"
#include <iostream>

namespace kero {
namespace log {

class Center {
public:
  Center() noexcept = default;
  ~Center() noexcept = default;

  Center(Center&&) = delete;
  Center(const Center&) = delete;
  auto operator=(Center&&) -> Center& = delete;
  auto operator=(const Center&) -> Center& = delete;

  auto UseSystemErrorStream(std::ostream& stream = std::cerr) noexcept -> void;
  auto Shutdown(ShutdownConfig&& config = ShutdownConfig{}) noexcept -> void;
  auto AddTransport(std::unique_ptr<Transport>&& transport) noexcept -> void;
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_CENTER_H
