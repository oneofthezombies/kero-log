#include "transport.h"

#include "utils.h"
#include <iostream>

namespace kero {
namespace log {

Transport::Transport() noexcept : level_{Level::kInfo} {}

Transport::Transport(const Level level) noexcept : level_{level} {}

auto Transport::SetLevel(const Level level) noexcept -> void { level_ = level; }

auto Transport::GetLevel() const noexcept -> Level { return level_; }

auto ConsolePlainTextTransport::OnLog(const Log& log) noexcept -> void {
  const auto datetime = TimePointToIso8601(std::chrono::system_clock::now());
  std::cout << datetime << " " << LevelToString(log.level) << " "
            << log.location.file_name() << ":" << log.location.line() << ":"
            << log.location.column() << " " << log.location.function_name()
            << ": " << log.message;
  for (const auto& [key, value] : log.data) {
    std::cout << " " << key << ": " << value;
  }
  std::cout << std::endl;
}

} // namespace log
} // namespace kero
