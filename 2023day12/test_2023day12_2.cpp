#include <gtest/gtest.h>
#include "2023day12_2.cpp"
string buildthem(const string& pattern,
                 const vector<int8_t> n,
                 vector<uint8_t>& out) {
  stringstream ss;
  for (int i = 0; i < REPLICAS; i++) {
    ss << pattern << "?";
  }
  ss << pattern;
  for (int i = 0; i < REPLICAS + 1; i++) {
    for (const auto& num : n) {
      out.emplace_back(num);
    }
  }

  return ss.str();
}
TEST(Test2023day12_2, failing19) {
  record r(".????????.", {1, 2});
  auto answer = r.count();
  ASSERT_EQ(answer, 15);
}
TEST(Test2023day12_2, failing12) {
  record r(".??#?.#???#?", {1, 1, 1, 1});
  ASSERT_EQ(r.count(), 2);
}
TEST(Test2023day12_2, longfailing12) {
  vector<uint8_t> n;
  string pattern = buildthem(".??#?.#???#?", {1, 1, 1, 1}, n);
  record r(pattern, n);
  int64_t answer = r.count();
  ASSERT_EQ(answer, 2002);
}

TEST(Test2023day12_2, failing38) {
  record r("????#???.???#??", {7, 2});
  ASSERT_EQ(r.count(), 4);
}
TEST(Test2023day12_2, shortestCountUnknown) {
  record r("?", {1});
  ASSERT_EQ(r.count(), 1);
}
TEST(Test2023day12_2, shortestCountKnown1) {
  record r("####", {4});
  ASSERT_EQ(r.count(), 1);
}
TEST(Test2023day12_2, shortestCountKnown0) {
  record r(".", {1});
  ASSERT_EQ(r.count(), 0);
}
TEST(Test2023day12_2, shortCount) {
  record r("??#", {1, 1});
  ASSERT_EQ(r.count(), 1);
}
TEST(Test2023day12_2, multipleAllQs) {
  record r("????", {1, 1});
  ASSERT_EQ(r.count(), 3);
}
TEST(Test2023day12_2, longShortCount) {
  record r("??#???#???#???#???#", {1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
  int64_t answer = r.count();
  ASSERT_EQ(answer, 1);
}

TEST(Test2023day12_2, longShortCount2) {
  vector<uint8_t> n;
  string pattern = buildthem("?#?#?#?#?#?#?#?", {1, 3, 1, 6}, n);
  record r(pattern, n);
  int64_t answer = r.count();
  ASSERT_EQ(answer, 1);
}

TEST(Test2023day12_2, LongCount) {
  vector<uint8_t> n;
  string pattern = buildthem("????.#...#...", {4, 1, 1}, n);
  record r(pattern, n);
  int64_t answer = r.count();
  ASSERT_EQ(answer, 16);
}
TEST(Test2023day12_2, Counti2) {
  vector<uint8_t> n;
  string pattern = buildthem("?###????????", {3, 2, 1}, n);
  record r(pattern, n);
  int64_t answer = r.count();
  ASSERT_EQ(answer, 506250);
}
TEST(Test2023day12_2, User4) {
  vector<uint8_t> n;
  string pattern = buildthem("??????#??????.?", {2, 4, 1, 1, 1}, n);
  record r(pattern, n);
  int64_t answer = r.count();
  ASSERT_EQ(answer, 7822159);
}
TEST(Test2023day12_2, shortCount2) {
  record r("???.###", {1, 1, 3});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12_2, Count) {
  record r("?###????????", {3, 2, 1});
  ASSERT_EQ(r.count(), 10);
}

TEST(Test2023day12_2, verifyBad) {
  record r(".###...#.#.#", {3, 2, 1});
  ASSERT_EQ(r.count(), 0);
}

TEST(Test2023day12_2, verifyGood) {
  record r("#.#.###", {1, 1, 3});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12_2, verifyBad_TrailingBroken) {
  record r(".##.###", {1, 1, 3});
  ASSERT_EQ(r.count(), 0);
}

TEST(Test2023day12_2, verifyGood_TrailingGood) {
  record r(".#.###......", {1, 3});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12_2, verifyGood_NothingBroken) {
  record r("............", {});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12_2, verifyGood_EverythingBroken) {
  record r("#########", {9});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12_2, verifyGood_ExtraNumbers) {
  record r("#########", {9, 3});
  ASSERT_EQ(r.count(), 0);
}

TEST(Test2023day12_2, verifyGood_SuperLong) {
  record r("###############################################################",
           {63});
  ASSERT_EQ(r.count(), 1);
}
TEST(Test2023day12_2, verifyGood_SuperShort) {
  record r("#", {1});
  ASSERT_EQ(r.count(), 1);
}

TEST(Test2023day12_2, suspicious1) {
  vector<uint8_t> n;
  string pattern = buildthem("??????#??????.?", {2, 4, 1, 1, 1}, n);
  record r(pattern, n);
  int64_t answer = r.count();
  ASSERT_EQ(answer, 7822159);
}