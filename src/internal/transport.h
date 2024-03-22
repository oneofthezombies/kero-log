#ifndef KERO_LOG_INTERNAL_TRANSPORT_H
#define KERO_LOG_INTERNAL_TRANSPORT_H

#include "core.h"

namespace kero {
namespace log {

class Transport {
public:
  Transport() noexcept;
  Transport(const Level level) noexcept;
  virtual ~Transport() noexcept = default;
  KERO_STRUCT_TYPE_MOVE(Transport);

  auto SetLevel(const Level level) noexcept -> void;
  auto GetLevel() const noexcept -> Level;

  virtual auto OnLog(const Log& log) noexcept -> void = 0;

protected:
  Level level_;
};

class ConsolePlainTextTransport : public Transport {
public:
  ConsolePlainTextTransport() noexcept = default;
  virtual ~ConsolePlainTextTransport() noexcept = default;
  KERO_STRUCT_TYPE_MOVE(ConsolePlainTextTransport);

  virtual auto OnLog(const Log& log) noexcept -> void override;
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_TRANSPORT_H
