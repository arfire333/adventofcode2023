#include <gtest/gtest.h>
#include "2023day13.cpp"

TEST(Test2023day13, col_match_true) {
  vector<string> p = {{"#.##..##.", "..#.##.#.", "##......#", "##......#",
                       "..#.##.#.", "..##..##.", "#.#.##.#."}};
  bool answer = col_match(p, 4, 5);
  ASSERT_TRUE(answer);
}

TEST(Test2023day13, col_match_false) {
  vector<string> p = {{"#.##..##.", "..#.##.#.", "##......#", "##......#",
                       "..#.##.#.", "..##..##.", "#.#.##.#."}};
  bool answer = col_match(p, 3, 5);
  ASSERT_FALSE(answer);
}

TEST(Test2023day13, row_match_true) {
  vector<string> p = {{"#.##..##.", "..#.##.#.", "##......#", "##......#",
                       "..#.##.#.", "..##..##.", "#.#.##.#."}};
  bool answer = row_match(p, 2, 3);
  ASSERT_TRUE(answer);
}

TEST(Test2023day13, row_match_false) {
  vector<string> p = {{"#.##..##.", "..#.##.#.", "##......#", "##......#",
                       "..#.##.#.", "..##..##.", "#.#.##.#."}};
  bool answer = row_match(p, 2, 4);
  ASSERT_FALSE(answer);
}
TEST(Test2023day13, horizontal_match_good) {
  vector<string> p = {{"#...##..#", "#....#..#", "..##..###", "#####.##.",
                       "#####.##.", "..##..###", "#....#..#"}};
  int answer = horizontal_split(p);
  ASSERT_EQ(answer, 4);
}
TEST(Test2023day13, horizontal_match_bad) {
  vector<string> p = {{"#.##..##.", "..#.##.#.", "##......#", "##......#",
                       "..#.##.#.", "..##..##.", "#.#.##.#."}};
  int answer = horizontal_split(p);
  ASSERT_EQ(answer, 0);
}
TEST(Test2023day13, vertical_match_good) {
  vector<string> p = {{"#.##..##.", "..#.##.#.", "##......#", "##......#",
                       "..#.##.#.", "..##..##.", "#.#.##.#."}};
  int answer = vertical_split(p);
  ASSERT_EQ(answer, 5);
}
TEST(Test2023day13, vertical_match_bad) {
  vector<string> p = {{"#...##..#", "#....#..#", "..##..###", "#####.##.",
                       "#####.##.", "..##..###", "#....#..#"}};
  int answer = vertical_split(p);
  ASSERT_EQ(answer, 0);
}