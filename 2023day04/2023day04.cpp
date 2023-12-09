#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int64_t> getNumbers(string_view s) {
  vector<int64_t> nums;
  size_t start = 0;
  size_t end = 0;
  do {
    start = s.find_first_of("0123456789", end);
    end = s.find_first_not_of("0123456789", start);
    if (start != string::npos) {
      nums.push_back(atoi(string(s.substr(start, end)).c_str()));
    }
  } while (end != string::npos);
  return nums;
}

void getData(istream& in,
             vector<vector<int64_t>>& winners,
             vector<vector<int64_t>>& data) {
  string s;
  while (getline(in, s) && s.size()) {
    size_t colon = s.find_first_of(':') + 1;
    size_t bar = s.find_first_of('|') + 1;
    string win = s.substr(colon + 1, bar - colon - 3);
    string tic = s.substr(bar + 1);
    auto winning = getNumbers(win);
    sort(winning.begin(), winning.end());
    winners.push_back(winning);
    auto elf_nums = getNumbers(tic);
    sort(elf_nums.begin(), elf_nums.end());
    data.push_back(elf_nums);
  }
}

int64_t scoreGame(const vector<int64_t>& winner, const vector<int64_t>& nums) {
  int score = 1;
  int j = 0;
  for (auto i = 0; i < winner.size() && j < nums.size();) {
    if (winner[i] < nums[j]) {
      i++;
      continue;
    } else if (winner[i] == nums[j]) {
      score = score << 1;
      i++;
      j++;
    } else {
      j++;
    }
  }
  return score >> 1;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0]);
  ifstream in(filename);
  vector<vector<int64_t>> winners;
  vector<vector<int64_t>> data;
  try {
    getData(in, winners, data);
  } catch (std::ios_base::failure& e) {
    cout << e.what() << "\n";
    return -1;
  }
  in.close();

  vector<int64_t> card_count(winners.size(), 1);
  int64_t score = 0;
  for (int i = 0; i < winners.size() && i < data.size(); i++) {
    int64_t gamescore = scoreGame(winners[i], data[i]);
    score += gamescore;
    int wincount = static_cast<int>(log2(gamescore)) + 1;
    for (int k = 0; k < card_count[i]; k++) {
      for (int j = 1; j <= wincount; j++) {
        card_count[i + j] = card_count[i + j] + 1;
      }
    }
  }
  int64_t total_cards = 0;
  total_cards = std::accumulate(card_count.begin(), card_count.end(), 0);

  cout << "Total Points: " << score << "\n";
  cout << "Total Cards: " << total_cards << "\n";
  return 0;
}
#endif