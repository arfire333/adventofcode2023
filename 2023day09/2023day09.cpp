#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<vector<vector<int64_t>>>& data) {
  string s;

  while (getline(in, s) && s.size()) {
    vector<vector<int64_t>> row;
    row.push_back(aoc::getNumbers(s));
    data.push_back(row);
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  vector<vector<vector<int64_t>>> data;
  getData(in, data);
  int64_t sum = 0;
  for (auto& history : data) {
    int64_t max = 1;
    size_t S = history[0].size();
    int row = 0;
    do {
      history.emplace_back(S, 0);
      auto& l = history[history.size() - 2];
      auto& h = history[history.size() - 1];
      max = 0;
      row++;
      for (int i = 1; i < S - row + 1; i++) {
        h[i - 1] = l[i] - l[i - 1];
        if (h[i - 1] != 0) {
          max = h[i - 1];
        }
      }
    } while (max != 0);
    row--;
    while (row > 0) {
      history[row][S - row] =
          history[row][S - row - 1] + history[row + 1][S - row - 1];
      row--;
    }
    cout << history[0][S - 1] + history[1][S - 1] << "\n";
    sum += (history[0][S - 1] + history[1][S - 1]);
  }
  cout << " sum=" << sum << "\n";

  return 0;
}
#endif