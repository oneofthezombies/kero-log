#include "kero_log.h"

auto main() -> int {
  auto center = kero::log::Center::Builder{}.Build();
  center.SetLogLevel(kero::log::Level::kDebug);
  center.AddTransport(std::make_unique<kero::log::ConsoleTransport>());
  auto logger = center.CreateLogger("example");
  kero::log::Debug("Hello, world!").Log(logger);
  center.Shutdown();

  kero::log::GlobalCenter().SetLogLevel(kero::log::Level::kDebug);
  kero::log::GlobalCenter().AddTransport(
      std::make_unique<kero::log::ConsoleTransport>());
  kero::log::Debug("Hello, world!").Log();
  kero::log::GlobalCenter().Shutdown();
  return 0;
}
