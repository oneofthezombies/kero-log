#include "kero_core.h"
#include <gtest/gtest.h>

TEST(ResultVoidTest, IsOk) {
  kero::core::Result<void, int> result;
  EXPECT_TRUE(result.IsOk());
}

TEST(ResultVoidTest, IsError) {
  kero::core::Result<void, int> result{1};
  EXPECT_TRUE(result.IsErr());
}

TEST(ResultVoidTest, Error) {
  kero::core::Result<void, int> result{1};
  EXPECT_EQ(1, *result.Err());
}

TEST(ResultVoidTest, ErrorConsume) {
  kero::core::Result<void, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultVoidTest, ErrorConsumeTwice) {
  kero::core::Result<void, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultVoidTest, MoveOnlyError) {
  kero::core::Result<void, std::unique_ptr<int>> result{
      std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
}

TEST(ResultVoidTest, MoveOnlyErrorConsume) {
  kero::core::Result<void, std::unique_ptr<int>> result{
      std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultVoidTest, MoveOnlyErrorConsumeTwice) {
  kero::core::Result<void, std::unique_ptr<int>> result{
      std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, IsOk) {
  kero::core::Result<bool, int> result{true};
  EXPECT_TRUE(result.IsOk());
}

TEST(ResultBoolTest, IsError) {
  kero::core::Result<bool, int> result{1};
  EXPECT_TRUE(result.IsErr());
}

TEST(ResultBoolTest, Ok) {
  kero::core::Result<bool, int> result{true};
  EXPECT_TRUE(*result.Ok());
}

TEST(ResultBoolTest, OkConsume) {
  kero::core::Result<bool, int> result{true};
  EXPECT_TRUE(*result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, OkConsumeTwice) {
  kero::core::Result<bool, int> result{true};
  EXPECT_TRUE(*result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyOk) {
  kero::core::Result<std::unique_ptr<bool>, int> result{
      std::make_unique<bool>(true)};
  EXPECT_TRUE(**result.Ok());
}

TEST(ResultBoolTest, MoveOnlyOkConsume) {
  kero::core::Result<std::unique_ptr<bool>, int> result{
      std::make_unique<bool>(true)};
  EXPECT_TRUE(**result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyOkConsumeTwice) {
  kero::core::Result<std::unique_ptr<bool>, int> result{
      std::make_unique<bool>(true)};
  EXPECT_TRUE(**result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, Error) {
  kero::core::Result<bool, int> result{1};
  EXPECT_EQ(1, *result.Err());
}

TEST(ResultBoolTest, ErrorConsume) {
  kero::core::Result<bool, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, ErrorConsumeTwice) {
  kero::core::Result<bool, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyError) {
  kero::core::Result<bool, std::unique_ptr<int>> result{
      std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
}

TEST(ResultBoolTest, MoveOnlyErrorConsume) {
  kero::core::Result<bool, std::unique_ptr<int>> result{
      std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyErrorConsumeTwice) {
  kero::core::Result<bool, std::unique_ptr<int>> result{
      std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}
