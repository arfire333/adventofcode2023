#include <gtest/gtest.h>
#include <libaoc.h>
#include <fstream>

using namespace std;

class TestLibAOC : public testing::Test {
 protected:
  string example_filename;
  string user_filename;
  void SetUp() override {
    user_filename = aoc::dataFilename("libaoc");
    example_filename = aoc::dataFilename("libaoc", "example.input");
  }
};

TEST_F(TestLibAOC, dataFilename_user) {
  ifstream in(user_filename);
  string s;
  in >> s;
  ASSERT_STREQ(s.c_str(), "User");
}

TEST_F(TestLibAOC, dataFilename_example) {
  ifstream in(example_filename);
  string s;
  in >> s;
  ASSERT_STREQ(s.c_str(), "Example");
}