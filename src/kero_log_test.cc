#include "kero_log.h"
#include "gtest/gtest.h"

TEST(LogTest, Stack) {
  auto center = kero::log::Center{};
  auto thread = center.RunOnThread();
  auto sender = center.CreateSender("test-category");
  kero::log::Debug("test").Send(sender);
  thread.join();
}

TEST(LogTest, Global) {
  auto &center = kero::log::GlobalCenter();
  auto thread = center.RunOnThread();
  auto sender = center.CreateSender("test-category");
  kero::log::Debug("test").Send(sender);
  thread.join();
}

TEST(LogTest, Local) {
  auto &center = kero::log::GlobalCenter();
  auto thread = center.RunOnThread();
  auto &sender = kero::log::LocalSender();
  kero::log::Debug("test").Send(sender);
  thread.join();
}
