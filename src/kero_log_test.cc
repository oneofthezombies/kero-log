#include "kero_log.h"
#include "gtest/gtest.h"

TEST(LogTest, Base) {
  auto center = kero::log::Center();
  center.Run();
  auto sender = center.CreateSender("test-category");
  kero::log::Debug("test").Send(sender);
}
