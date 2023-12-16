#include <gtest/gtest.h>
#include "2023day12.cpp"
TEST(Test2023day12, shortCount) {
  record r("??#", {1, 1});
  ASSERT_EQ(r.count(), 1);
}
TEST(Test2023day12, shortCount2) {
  record r("???.###", {1, 1, 3});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12, Count) {
  record r("?###????????", {3, 2, 1});
  ASSERT_EQ(r.count(), 10);
}

TEST(Test2023day12, verifyBad) {
  record r(".###...#.#.#", {3, 2, 1});
  ASSERT_EQ(r.valid(r.number), false);
  ASSERT_EQ(r.valid(), false);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyGood) {
  record r("#.#.###", {1, 1, 3});
  ASSERT_EQ(r.valid(r.number), true);
  ASSERT_EQ(r.valid(), true);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyBad_TrailingBroken) {
  record r(".##.###", {1, 1, 3});
  ASSERT_EQ(r.valid(r.number), false);
  ASSERT_EQ(r.valid(), false);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyGood_TrailingGood) {
  record r(".#.###......", {1, 3});
  ASSERT_EQ(r.valid(r.number), true);
  ASSERT_EQ(r.valid(), true);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyGood_NothingBroken) {
  record r("............", {});
  ASSERT_EQ(r.valid(r.number), true);
  ASSERT_EQ(r.valid(), true);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyGood_EverythingBroken) {
  record r("#########", {9});
  ASSERT_EQ(r.valid(r.number), true);
  ASSERT_EQ(r.valid(), true);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyGood_ExtraNumbers) {
  record r("#########", {9, 3});
  ASSERT_EQ(r.valid(r.number), false);
  ASSERT_EQ(r.valid(), false);
  std::cout << r << " : " << r.count() << "\n";
}

TEST(Test2023day12, verifyGood_SuperLong) {
  record r("###############################################################",
           {63});
  ASSERT_EQ(r.valid(r.number), true);
  ASSERT_EQ(r.valid(), true);
  std::cout << r << " : " << r.count() << "\n";
}
TEST(Test2023day12, verifyGood_SuperShort) {
  record r("#", {1});
  ASSERT_EQ(r.valid(r.number), true);
  ASSERT_EQ(r.valid(), true);
  std::cout << r << " : " << r.count() << "\n";
}