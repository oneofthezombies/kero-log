#ifndef KERO_LOG_INTERNAL_LOCAL_CONTEXT_H
#define KERO_LOG_INTERNAL_LOCAL_CONTEXT_H

#include "core.h"
#include "kero_spsc.h"
#include <memory>

namespace kero {
namespace log {

class LocalContext {
public:
  class Builder {
  public:
    Builder() = default;
    ~Builder() = default;
    KERO_STRUCT_TYPE_PIN(Builder);

    auto Build() const noexcept -> Result<LocalContext>;
  };

  ~LocalContext() noexcept;
  KERO_STRUCT_TYPE_MOVE(LocalContext);

  auto SendLog(std::unique_ptr<kero::log::Log>&& log) const noexcept -> void;

private:
  LocalContext(spsc::Tx<std::unique_ptr<kero::log::Log>>&& log_tx,
               std::string&& thread_id) noexcept;

  spsc::Tx<std::unique_ptr<kero::log::Log>> log_tx_;
  std::string thread_id_;
};

auto GetLocalContext() -> std::unique_ptr<LocalContext>&;

} // namespace log
} // namespace kero

#endif // KERO_LOG_INTERNAL_LOCAL_CONTEXT_H
