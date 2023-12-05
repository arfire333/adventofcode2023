#include <gtest/gtest.h>
#include <climits>
#include "2023day05.cpp"

TEST(Test2023day05, Nothing) {
  ASSERT_EQ(1, 1);
}

TEST(Test2023day05, SparseMap_Small) {
  SparseMap map;
  map.name("Small");
  map.add({0, 100, 5});
  ASSERT_EQ(map.at(0), 0);
  ASSERT_EQ(map.at(100), 0);
  ASSERT_EQ(map.at(101), 1);
  ASSERT_EQ(map.at(102), 2);
}

TEST(Test2023day05, SparseMap_Large) {
  int64_t big = 2147483647;
  ASSERT_EQ(big, INT_MAX);
  SparseMap map;
  map.name("Large");
  map.add({0, 100, 5});
  ASSERT_EQ(map.at(0), 0);
  ASSERT_EQ(map.at(100), 0);
  ASSERT_EQ(map.at(101), 1);
  ASSERT_EQ(map.at(102), 2);
}