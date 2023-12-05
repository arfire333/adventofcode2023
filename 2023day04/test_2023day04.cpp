#include <gtest/gtest.h>
#include "2023day04.cpp"

class Test2023Day04 : public testing::Test {
 protected:
  vector<vector<int64_t> > winners;
  vector<vector<int64_t> > data;
  vector<int64_t> card_count;
  void SetUp() override {
    string filename = aoc::dataFilename("2023day04", "example.input");
    ifstream in(filename);
    getData(in, winners, data);
    card_count.resize(winners.size(), 1);
  }
};
TEST_F(Test2023Day04, getData) {
  ASSERT_EQ(data.size(), 6);
  ASSERT_EQ(winners.size(), 6);
  ASSERT_EQ(data[0].size(), 8);
  ASSERT_EQ(winners[0].size(), 5);
}

TEST_F(Test2023Day04, score) {
  vector<int64_t> winner = {1, 2, 3, 4, 6};
  vector<int64_t> nums = {1, 3, 5, 7, 8};
  auto score = scoreGame(winner, nums);
  ASSERT_EQ(score, 2);
}
TEST_F(Test2023Day04, example) {
  int64_t score = 0;
  for (int i = 0; i < winners.size() && i < data.size(); i++) {
    int gamescore = scoreGame(winners[i], data[i]);
    score += gamescore;
    int wincount = log2(gamescore) + 1;
    for (int k = 0; k < card_count[i]; k++) {
      for (int j = 1; j <= wincount; j++) {
        card_count[i + j] = card_count[i + j] + 1;
      }
    }
  }
  ASSERT_EQ(score, 13);
  int64_t total_cards = 0;
  for (int i = 0; i < card_count.size(); i++) {
    total_cards += card_count[i];
  }
  ASSERT_EQ(total_cards, 30);
}