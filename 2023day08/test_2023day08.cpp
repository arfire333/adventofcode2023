#include <gtest/gtest.h>
#include "2023day08.cpp"

TEST(Test2023day08, str2node) {
  ASSERT_EQ(str2node("ABC"), 4276803);
  ASSERT_EQ(str2node("ABD"), 4276804);
  ASSERT_EQ(str2node("CCC"), 4408131);
}
