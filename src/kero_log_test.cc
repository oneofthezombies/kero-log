#include "center.h"
#include "log_builder.h"
#include "logger.h"
#include "gtest/gtest.h"

TEST(LogTest, LocalCenter) {
  auto center = kero::log::Center::Builder{}.Build();
  center.SetLogLevel(kero::log::Level::kDebug);
  center.AddTransport(std::make_unique<kero::log::ConsoleTransport>());
  auto logger = center.CreateLogger("example");
  kero::log::Debug("Hello, world!").Log(logger);
  center.Shutdown();
}

TEST(LogTest, GlobalCenter) {
  kero::log::GlobalCenter().SetLogLevel(kero::log::Level::kDebug);
  kero::log::GlobalCenter().AddTransport(
      std::make_unique<kero::log::ConsoleTransport>());
  kero::log::Debug("Hello, world!").Log();
  kero::log::GlobalCenter().Shutdown();
}
