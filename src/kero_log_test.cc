#include "kero_log.h"
#include "gtest/gtest.h"

TEST(LogTest, Basic) {
  kero::log::Center{}.UseSystemErrorStream();
  auto transport = std::make_unique<kero::log::ConsolePlainTextTransport>();
  transport->SetLevel(kero::log::Level::kDebug);
  kero::log::Center{}.AddTransport(std::move(transport));
  kero::log::Error("Error message").Log();
  kero::log::Warn("Warn message").Log();
  kero::log::Info("Info message").Log();
  kero::log::Debug("Debug message").Log();
  kero::log::Info("Info message with data").Data("string", "value").Log();
  kero::log::Info("Info message with data").Data("int", 1).Log();
  std::thread t([]() {
    kero::log::Error("Error message from thread").Log();
    kero::log::Warn("Warn message from thread").Log();
    kero::log::Info("Info message from thread").Log();
    kero::log::Debug("Debug message from thread").Log();
    for (int i = 0; i < 10000; ++i) {
      kero::log::Info("Info message from thread").Data("int", i).Log();
    }
    std::cout << "Thread done" << std::endl;
  });
  t.join();
  kero::log::Center{}.Shutdown(
      kero::log::ShutdownConfig{std::chrono::milliseconds{100}});
}
