#include "files/2/q.h"

#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

using ::testing::ElementsAre;

TEST(MyVectorStudentTest, DefaultConstructorProducesEmptyVector) {
  MyVector vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);

  EXPECT_EQ(vec.pop_back(), 0);
  EXPECT_EQ(vec.get_error(), ErrorCode::kPopFromEmptyVector);
}

TEST(MyVectorStudentTest, SizedConstructorInitialisesZeros) {
  MyVector vec(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.ConvertToStdVector(), std::vector<int>({0, 0, 0}));
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorStudentTest, CopyConstructorCopiesDataAndError) {
  MyVector original;
  original.push_back(10);
  original.push_back(20);
  EXPECT_EQ(original.find(99), -1);
  EXPECT_EQ(original.get_error(), ErrorCode::kNotFound);

  MyVector copy(original);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_THAT(copy.ConvertToStdVector(), ElementsAre(10, 20));
  EXPECT_EQ(copy.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorStudentTest, InsertFrontAndBack) {
  MyVector vec;
  vec.insert(1, -1);  // front insert into empty vector
  vec.insert(2, 0);   // insert after first element
  vec.insert(3, 1);   // insert after second element

  EXPECT_THAT(vec.ConvertToStdVector(), ElementsAre(1, 2, 3));
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorStudentTest, InsertInvalidIndexLeavesVectorUnchanged) {
  MyVector vec;
  vec.push_back(42);

  vec.insert(7, 5);
  EXPECT_EQ(vec.get_error(), ErrorCode::kIndexError);
  EXPECT_THAT(vec.ConvertToStdVector(), ElementsAre(42));
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorStudentTest, AtHandlesInvalidIndices) {
  MyVector vec;
  vec.push_back(5);

  EXPECT_EQ(vec.at(0), 5);
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);
  EXPECT_EQ(vec.at(1), -1);
  EXPECT_EQ(vec.get_error(), ErrorCode::kIndexError);
}

TEST(MyVectorStudentTest, FindReportsMissingValues) {
  MyVector vec;
  vec.push_back(9);
  vec.push_back(8);

  EXPECT_EQ(vec.find(8), 1);
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);
  EXPECT_EQ(vec.find(0), -1);
  EXPECT_EQ(vec.get_error(), ErrorCode::kNotFound);
}

TEST(MyVectorStudentTest, PopFrontAndBackRemoveElementsInOrder) {
  MyVector vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  EXPECT_EQ(vec.pop_front(), 1);
  EXPECT_EQ(vec.pop_back(), 3);
  EXPECT_THAT(vec.ConvertToStdVector(), ElementsAre(2));
  EXPECT_EQ(vec.get_error(), ErrorCode::kNoError);
}

}  // namespace
