#ifndef KERO_LOG_INTERNAL_TRANSPORT_H
#define KERO_LOG_INTERNAL_TRANSPORT_H

#include "core.h"

namespace kero {
namespace log {

class Transport {
public:
  Transport() noexcept;
  Transport(const Level level) noexcept;
  Transport(Transport&&) noexcept = default;
  virtual ~Transport() noexcept = default;
  auto operator=(Transport&&) noexcept -> Transport& = default;

  Transport(const Transport&) = delete;
  auto operator=(const Transport&) -> Transport& = delete;

  auto SetLevel(const Level level) noexcept -> void;
  auto GetLevel() const noexcept -> Level;

  virtual auto OnLog(const Log& log) noexcept -> void = 0;

protected:
  Level level_;
};

class ConsolePlainTextTransport : public Transport {
public:
  ConsolePlainTextTransport() noexcept = default;
  ConsolePlainTextTransport(ConsolePlainTextTransport&&) noexcept = default;
  virtual ~ConsolePlainTextTransport() noexcept = default;
  auto operator=(ConsolePlainTextTransport&&) noexcept
      -> ConsolePlainTextTransport& = default;

  ConsolePlainTextTransport(const ConsolePlainTextTransport&) = delete;
  auto operator=(const ConsolePlainTextTransport&)
      -> ConsolePlainTextTransport& = delete;

  virtual auto OnLog(const Log& log) noexcept -> void override;
};

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_TRANSPORT_H
