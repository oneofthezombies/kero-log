#include "kero_log.h"
#include "gtest/gtest.h"

TEST(LogTest, Base) {
  auto center = kero::log::Center();
  auto sender = center.CreateSender("test");
  kero::log::Debug("test").Send(sender);
}
