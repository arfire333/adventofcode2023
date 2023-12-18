#include <gtest/gtest.h>
#include "2023day13_2.cpp"

TEST(Test2023day13, col_match) {
  vector<string> p = {{
      "#.##..##.",
      "..#.##.#.",
      "##......#",
      "##......#",
      "..#.##.#.",
      "..##..##.",
      "#.#.##.#.",
  }};
  int answer = col_match(p, 4, 5);
  ASSERT_EQ(answer, 0);
  answer = col_match(p, 0, 1);
  ASSERT_EQ(answer, 2);
  answer = col_match(p, 7, 8);
  ASSERT_EQ(answer, 7);
}

TEST(Test2023day13, row_match_true) {
  vector<string> p = {{
      "#.##..##.",
      "..#.##.#.",
      "##......#",
      "##......#",
      "..#.##.#.",
      "..##..##.",
      "#.#.##.#.",
  }};
  int answer = row_match(p, 2, 3);
  ASSERT_EQ(answer, 0);
  answer = row_match(p, 0, 1);
  ASSERT_EQ(answer, 5);
}

TEST(Test2023day13, horizontal_match_good) {
  vector<string> p = {{
      "#...##..#",
      "#....#..#",
      "..##..###",
      "#####.##.",
      "#####.##.",
      "..##..###",
      "#....#..#",
  }};
  int answer = horizontal_split(p);
  ASSERT_EQ(answer, 1);
}
TEST(Test2023day13, horizontal_match_bad) {
  vector<string> p = {{
      "#.##..##.",
      "..#.##.#.",
      "##......#",
      "##......#",
      "..#.##.#.",
      "..##..##.",
      "#.#.##.#.",
  }};
  int answer = horizontal_split(p);
  ASSERT_EQ(answer, 3);
}
TEST(Test2023day13, vertical_match_good) {
  vector<string> p = {{
      "#.##..##.",
      "..#.##.#.",
      "##......#",
      "##......#",
      "..#.##.#.",
      "..##..##.",
      "#.#.##.#.",
  }};
  int answer = vertical_split(p);
  ASSERT_EQ(answer, 0);
}
TEST(Test2023day13, vertical_match_bad) {
  vector<string> p = {{
      "#...##..#",
      "#....#..#",
      "..##..###",
      "#####.##.",
      "#####.##.",
      "..##..###",
      "#....#..#",
  }};
  int answer = vertical_split(p);
  ASSERT_EQ(answer, 0);
}

TEST(Test2023day13, user5) {
  vector<string> p = {{
      ".#.##.#...#....",
      ".#.##.#.###..#.",
      "##..#.####..##.",
      "##.##.##..#..#.",
      "##.##.##.#..###",
      ".#.##.#.#...#..",
      "...##........##",
      "#..##..####...#",
      "#..##..#..##.#.",
      "##.##.###.#..##",
      "..#..#....##...",
      "...##.....#####",
      ".#.##.#..##...#",
      ".#....#.....##.",
      ".#....#.....##.",
  }};
  int answer = vertical_split(p);
  ASSERT_EQ(answer, 4);
  answer = horizontal_split(p);
  ASSERT_EQ(answer, 0);
}