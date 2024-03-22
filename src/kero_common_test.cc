#include "kero_common.h"
#include <gtest/gtest.h>

TEST(ResultVoidTest, IsOk) {
  kero::Result<void, int> result;
  EXPECT_TRUE(result.IsOk());
}

TEST(ResultVoidTest, IsError) {
  kero::Result<void, int> result{1};
  EXPECT_TRUE(result.IsErr());
}

TEST(ResultVoidTest, Error) {
  kero::Result<void, int> result{1};
  EXPECT_EQ(1, *result.Err());
}

TEST(ResultVoidTest, ErrorConsume) {
  kero::Result<void, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultVoidTest, ErrorConsumeTwice) {
  kero::Result<void, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultVoidTest, MoveOnlyError) {
  kero::Result<void, std::unique_ptr<int>> result{std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
}

TEST(ResultVoidTest, MoveOnlyErrorConsume) {
  kero::Result<void, std::unique_ptr<int>> result{std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultVoidTest, MoveOnlyErrorConsumeTwice) {
  kero::Result<void, std::unique_ptr<int>> result{std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, IsOk) {
  kero::Result<bool, int> result{true};
  EXPECT_TRUE(result.IsOk());
}

TEST(ResultBoolTest, IsError) {
  kero::Result<bool, int> result{1};
  EXPECT_TRUE(result.IsErr());
}

TEST(ResultBoolTest, Ok) {
  kero::Result<bool, int> result{true};
  EXPECT_TRUE(*result.Ok());
}

TEST(ResultBoolTest, OkConsume) {
  kero::Result<bool, int> result{true};
  EXPECT_TRUE(*result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, OkConsumeTwice) {
  kero::Result<bool, int> result{true};
  EXPECT_TRUE(*result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyOk) {
  kero::Result<std::unique_ptr<bool>, int> result{std::make_unique<bool>(true)};
  EXPECT_TRUE(**result.Ok());
}

TEST(ResultBoolTest, MoveOnlyOkConsume) {
  kero::Result<std::unique_ptr<bool>, int> result{std::make_unique<bool>(true)};
  EXPECT_TRUE(**result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyOkConsumeTwice) {
  kero::Result<std::unique_ptr<bool>, int> result{std::make_unique<bool>(true)};
  EXPECT_TRUE(**result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Ok());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, Error) {
  kero::Result<bool, int> result{1};
  EXPECT_EQ(1, *result.Err());
}

TEST(ResultBoolTest, ErrorConsume) {
  kero::Result<bool, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, ErrorConsumeTwice) {
  kero::Result<bool, int> result{1};
  EXPECT_EQ(1, *result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyError) {
  kero::Result<bool, std::unique_ptr<int>> result{std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
}

TEST(ResultBoolTest, MoveOnlyErrorConsume) {
  kero::Result<bool, std::unique_ptr<int>> result{std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}

TEST(ResultBoolTest, MoveOnlyErrorConsumeTwice) {
  kero::Result<bool, std::unique_ptr<int>> result{std::make_unique<int>(1)};
  EXPECT_EQ(1, **result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
  EXPECT_FALSE(result.Err());
  EXPECT_FALSE(result.IsOk());
  EXPECT_FALSE(result.IsErr());
}
