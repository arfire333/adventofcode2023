#include <gtest/gtest.h>
#include <istream>
#include <streambuf>
#include "2023day03.cpp"

std::string somedata =
    "467..114..\n"
    "...*......\n"
    "..35..633.\n"
    "......#...\n"
    "617*......\n"
    ".....+.58.\n"
    "..592.....\n"
    "......755.\n"
    "...$.*....\n"
    ".664.598..\n";

struct membuf : std::streambuf {
  membuf(char const* base, size_t size) {
    char* p(const_cast<char*>(base));
    this->setg(p, p, p + size);
  }
};
struct imemstream : virtual membuf, std::istream {
  imemstream(char const* base, size_t size)
      : membuf(base, size), std::istream(static_cast<std::streambuf*>(this)) {}
};

TEST(Test2023Day03, getData) {
  std::vector<std::vector<char>> schematic;
  imemstream in(somedata.c_str(), somedata.size());

  getData(in, schematic);
  ASSERT_EQ(schematic.size(), 10);
  ASSERT_EQ(schematic[0].size(), 10);
}

TEST(Test2023Day03, adjacent) {
  std::vector<std::vector<char>> schematic;
  imemstream in(somedata.c_str(), somedata.size());
  getData(in, schematic);

  int64_t gear;
  ASSERT_TRUE(isAdjacent(schematic, 0, 2, gear));
  ASSERT_EQ(gear, 13);
  ASSERT_TRUE(isAdjacent(schematic, 9, 3, gear));
  ASSERT_EQ(gear, -1);
  ASSERT_TRUE(isAdjacent(schematic, 9, 5, gear));
  ASSERT_EQ(gear, 85);
  ASSERT_FALSE(isAdjacent(schematic, 0, 5, gear));
  ASSERT_FALSE(isAdjacent(schematic, 0, 0, gear));
  ASSERT_FALSE(isAdjacent(schematic, 0, 9, gear));
  ASSERT_FALSE(isAdjacent(schematic, 9, 9, gear));
  ASSERT_FALSE(isAdjacent(schematic, 9, 0, gear));

  std::vector<int64_t> numbers;
  map<int64_t, set<int64_t>> gear2part;
  findNumbers(schematic, numbers, gear2part);
  int64_t result = ratioSum(gear2part);
  ASSERT_EQ(result, 467835);
  ASSERT_TRUE(numbers.size() > 0);
}