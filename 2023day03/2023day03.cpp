#include <stdint.h>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

bool isAdjacent(const vector<string>& schematic,
                int row,
                int col,
                int64_t& gear) {
  size_t MAX_ROW = schematic.size() - 1;
  size_t MAX_COL = schematic[0].size() - 1;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int rowi = row + i;
      int colj = col + j;
      if (i == 0 && j == 0)
        continue;  // same as point
      if (rowi < 0 || rowi > MAX_ROW || colj < 0 || colj > MAX_COL)
        continue;  // out of bounds
      if (!isdigit(schematic[rowi][colj]) && schematic[rowi][colj] != '.') {
        if (schematic[rowi][colj] == '*') {
          gear = rowi * (MAX_COL + 1) + colj;  // The gear id
        } else {
          gear = -1;
        }
        return true;
      }
    }
  }
  return false;
}

void getData(istream& in, vector<string>& schematic) {
  string s;
  while (getline(in, s) && s.size()) {
    schematic.push_back(s);
  }
}

int64_t findNumbers(const vector<string>& schematic,
                    map<int64_t, set<int64_t>>& gear2part) {
  int64_t sum = 0;
  int64_t num = 0;
  bool is_adjacent = false;
  vector<int64_t> gears;
  for (int i = 0; i < schematic.size(); i++) {
    for (int j = 0; j < schematic[0].size(); j++) {
      if (isdigit(schematic[i][j])) {
        num = num * 10 + schematic[i][j] - '0';
        int64_t gear;
        if (isAdjacent(schematic, i, j, gear)) {
          is_adjacent = true;
          gears.push_back(gear);
        }
      } else {
        if (is_adjacent) {
          sum += num;
          for (auto gear : gears) {
            if (gear2part.find(gear) == gear2part.end()) {
              std::set<int64_t> newset;
              newset.insert(num);
              gear2part.try_emplace(gear, newset);
            } else {
              gear2part.at(gear).insert(num);
            }
          }
          gears.clear();
          num = 0;
          is_adjacent = false;
        } else {
          num = 0;
        }
      }
    }
  }
  return sum;
}

int64_t ratioSum(const map<int64_t, set<int64_t>>& gear2part) {
  int64_t sum = 0;
  for (const auto& [key, value] : gear2part) {
    if (value.size() != 2) {
      continue;
    }
    int64_t first = *value.begin();
    int64_t second = *value.rbegin();
    sum += first * second;
  }
  return sum;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  vector<string> schematic;
  getData(cin, schematic);

  map<int64_t, set<int64_t>> gear2part;
  cout << findNumbers(schematic, gear2part) << "\n"
       << ratioSum(gear2part) << "\n";
  return 0;
}
#endif