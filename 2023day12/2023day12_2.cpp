#include <assert.h>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "libaoc.h"

using namespace std;

const size_t REPLICAS = 4;

struct record {
  string pattern;
  vector<uint8_t> damaged;
  vector<uint8_t> number =
      {};                     // Bit representation of patterns known values set
  vector<uint8_t> mask = {};  // Bit representation of unknown bits
  int8_t mask_N = 0;          // Number of unkown bits
  record(const string& pattern, const vector<uint8_t>& damaged)
      : pattern(pattern), damaged(damaged) {
    for (const auto& c : pattern) {
      if (c == '#') {
        number.emplace_back(1);
        mask.emplace_back(0);
      } else if (c == '?') {
        mask.emplace_back(1);
        number.emplace_back(0);
        mask_N += 1;
      } else {
        mask.emplace_back(0);
        number.emplace_back(0);
      }
    }
  }
  friend ostream& operator<<(ostream& os, const record& r) {
    for (const auto& val : r.number) {
      os << val;
    }
    os << '|';
    for (const auto& val : r.mask) {
      os << val;
    }
    return os;
  }
  int64_t countHelper(vector<vector<vector<vector<int64_t>>>>& memo,
                      int bit,
                      int word,
                      int wordbitcount) const {
    if (bit >= pattern.size()) {
      if (word == damaged.size() && wordbitcount == 0) {
        return 1;
      }
      if ((word == damaged.size() - 1) && (wordbitcount == damaged[word])) {
        return 1;
      }
      return 0;
    }

    if (word < damaged.size() && wordbitcount > damaged[word]) {
      return 0;
    }

    vector<char> options;

    if (pattern[bit] == '?') {
      options.emplace_back('#');
      options.emplace_back('.');
    } else {
      options.emplace_back(pattern[bit]);
    }
    int64_t total_total = 0;
    for (auto curr : options) {
      int64_t total = 0;
      int curridx = (curr == '.') ? 0 : 1;
      curridx = (curr == '#' ? 1 : curridx);
      if (memo[curridx][bit][word][wordbitcount] >= 0) {
        total += memo[curridx][bit][word][wordbitcount];
      } else if (curr == '.') {
        if (wordbitcount == 0) {
          total += countHelper(memo, bit + 1, word, wordbitcount);
        } else if (word < damaged.size() && wordbitcount == damaged[word]) {
          total += countHelper(memo, bit + 1, word + 1, 0);
        }
      } else if (word < damaged.size() && curr == '#') {
        total += countHelper(memo, bit + 1, word, wordbitcount + 1);
      }
      memo[curridx][bit][word][wordbitcount] = total;
      total_total += total;
    }
    return total_total;
  }

  int64_t count(int bit = 0, int word = 0, int wordbitcount = 0) const {
    int64_t longest_word = 0;
    for (const auto& val : damaged) {
      if (val > longest_word) {
        longest_word = val;
      }
    }
    vector<vector<vector<vector<int64_t>>>> memo(
        2, vector<vector<vector<int64_t>>>(
               pattern.size() + 1,
               vector<vector<int64_t>>(damaged.size() + 1,
                                       vector<int64_t>(longest_word + 1, -1))));
    int64_t total = countHelper(memo, bit, word, wordbitcount);
    return total;
  }
};

vector<record> getData(istream& in) {
  string s;
  vector<record> records;
  stringstream ss;
  while (getline(in, s) && s.size()) {
    ss.str("");

    size_t end = s.find_first_of(" ");
    string pattern = s.substr(0, end);
    size_t saved_end = end;
    vector<uint8_t> damaged;
    for (int i = 0; i < REPLICAS + 1; i++) {
      end = saved_end;
      while (end != string::npos) {
        size_t start = end + 1;
        end = s.find_first_of(",", start);
        damaged.push_back(
            static_cast<uint8_t>(std::stoi(s.substr(start, end))));
      }
    }
    for (int i = 0; i < REPLICAS; i++) {
      ss << pattern << '?';
    }
    ss << pattern;
    pattern = ss.str();
    records.emplace_back(pattern, damaged);
  }
  return records;
}
#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day12", "user.input");
  ifstream in(filename);
  vector<record> records = getData(in);
  int64_t sum = 0;
  int i = 1;
  for (const auto& record : records) {
    int64_t newcount = 0;
    newcount = record.count();
    sum += newcount;
    cout << i << " Total: " << sum << " - " << newcount << " - "
         << record.pattern << " : " << record.pattern.size() << "\n";
    i++;
  }
  return 0;
}
#endif