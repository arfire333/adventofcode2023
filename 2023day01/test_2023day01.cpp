#include "2023day01.cpp"
#include <gtest/gtest.h>

TEST( Test2023Day01, Part1 ){
  std::string s="6threezlljtzcr1sdjkthree4cx";
  int16_t result = get_value_part2(s);
  ASSERT_EQ(result, 64);
}

TEST( Test2023Day01, Part2 ){
  std::string s="eightwothree";
  int16_t result = get_value_part2(s);
  ASSERT_EQ(result, 83);

  s="xcntwone4633sixmkm1nine";
  result=get_value_part2(s);
  ASSERT_EQ(result,29);

  s="4two5two9xcpkkjqxcfivessqqvhbbt";
  result=get_value_part2(s);
  ASSERT_EQ(result,45);
}
