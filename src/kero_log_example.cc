#include "center.h"
#include "log_builder.h"
#include "logger.h"

auto main() -> int {
  auto center = kero::log::Center::Builder{}.Build();
  center.SetLogLevel(kero::log::Level::kDebug);
  auto logger = center.CreateLogger("example");
  kero::log::Debug("Hello, world!").Log(logger);
  center.Shutdown();

  kero::log::GlobalCenter().SetLogLevel(kero::log::Level::kDebug);
  kero::log::Debug("Hello, world!").Log();
  kero::log::GlobalCenter().Shutdown();
  return 0;
}
