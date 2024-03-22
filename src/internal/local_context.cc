#include "local_context.h"

#include "global_context.h"
#include <memory>
#include <sstream>

namespace kero {
namespace log {

auto LocalContext::Builder::Build() const noexcept -> Result<LocalContext> {
  auto thread_id = ThreadIdToString(std::this_thread::get_id());
  auto [log_tx, log_rx] =
      spsc::Channel<std::unique_ptr<kero::log::Log>>::Builder{}.Build();
  auto result = GetGlobalContext().AddLogRx(thread_id, std::move(log_rx));
  if (result.IsErr()) {
    return Result<LocalContext>{std::move(*result.Err())};
  }
  return Result<LocalContext>{
      LocalContext{std::move(log_tx), std::move(thread_id)}};
}

LocalContext::LocalContext(spsc::Tx<std::unique_ptr<kero::log::Log>>&& log_tx,
                           std::string&& thread_id) noexcept
    : log_tx_{std::move(log_tx)}, thread_id_{std::move(thread_id)} {}

LocalContext::~LocalContext() noexcept {
  GetGlobalContext().RemoveLogRx(thread_id_);
}

auto LocalContext::SendLog(std::unique_ptr<kero::log::Log>&& log) const noexcept
    -> void {
  log_tx_.Send(std::move(log));
}

auto GetLocalContext() -> std::unique_ptr<LocalContext>& {
  thread_local std::unique_ptr<LocalContext> local_context{nullptr};
  thread_local std::once_flag flag{};

  std::call_once(flag, [&]() {
    auto result = LocalContext::Builder{}.Build();
    if (result.IsOk()) {
      local_context = result.Ok();
    } else {
      std::stringstream ss{};
      ss << "Failed to build LocalContext: " << *result.Err();
      GetGlobalContext().LogSystemError(ss.str());
    }
  });

  return local_context;
}

} // namespace log
} // namespace kero
