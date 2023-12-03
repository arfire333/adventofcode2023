#include <stdint.h>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool isAdjacent(const vector<vector<char>>& schematic,
                int row,
                int col,
                int64_t& gear) {
  int MAX_ROW = schematic.size() - 1;
  int MAX_COL = schematic[0].size() - 1;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int rowi = row + i;
      int colj = col + j;
      if (i == 0 && j == 0)
        continue;  // same as point
      if (rowi < 0 || rowi > MAX_ROW)
        continue;  // out of bounds
      if (colj < 0 || colj > MAX_COL)
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

void getData(istream& in, vector<vector<char>>& schematic) {
  while (in.peek() != EOF) {
    vector<char> line;
    char c;
    while (in.peek() != '\n' && in.peek() != EOF) {
      in.get(c);
      line.push_back(c);
    }
    in.get(c);
    schematic.push_back(line);
    line.clear();
  }
}

void findNumbers(const vector<vector<char>>& schematic,
                 vector<int64_t>& numbers,
                 map<int64_t, set<int64_t>>& gear2part) {
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
          numbers.push_back(num);
          for (auto gear : gears) {
            if (gear2part.find(gear) == gear2part.end()) {
              std::set<int64_t> newset;
              newset.insert(num);
              gear2part.insert({gear, newset});
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
}

int64_t ratioSum(map<int64_t, set<int64_t>>& gear2part) {
  int64_t sum = 0;
  for (auto it : gear2part) {
    if (it.second.size() != 2) {
      continue;
    }
    int64_t first = *it.second.begin();
    int64_t second = *it.second.rbegin();
    sum += first * second;
  }
  return sum;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  vector<vector<char>> schematic;
  getData(cin, schematic);

  vector<int64_t> numbers;
  map<int64_t, set<int64_t>> gear2part;
  findNumbers(schematic, numbers, gear2part);
  int64_t result = ratioSum(gear2part);
  cout << accumulate(numbers.begin(), numbers.end(), 0) << "\n";
  cout << result << "\n";
  return 0;
}
#endif