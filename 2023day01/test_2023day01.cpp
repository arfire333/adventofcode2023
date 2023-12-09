#include <gtest/gtest.h>
#include "2023day01.cpp"

TEST(Test2023Day01, Part1) {
  std::string s = "6threezlljtzcr1sdjkthree4cx";
  int64_t result = get_value_part2(s);
  ASSERT_EQ(result, 64);
}

TEST(Test2023Day01, Part2_83) {
  std::string s = "eightwothree";
  int64_t result = get_value_part2(s);
  ASSERT_EQ(result, 83);
}

TEST(Test2023Day01, Part2_29) {
  std::string s = "xcntwone4633sixmkm1nine";
  int64_t result = get_value_part2(s);
  ASSERT_EQ(result, 29);
}

TEST(Test2023Day01, Part2_45) {
  std::string s = "4two5two9xcpkkjqxcfivessqqvhbbt";
  int64_t result = get_value_part2(s);
  ASSERT_EQ(result, 45);
}
