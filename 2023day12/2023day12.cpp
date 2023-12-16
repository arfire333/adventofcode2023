#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "libaoc.h"

using namespace std;
struct record {
  string pattern;
  vector<int64_t> damaged;
  int64_t number = 0;  // Bit representation of patterns known values set
  int64_t mask = 0;    // Bit representation of unknown bits
  int64_t mask_N = 0;  // Number of unkown bits
  record(const string& pattern, const vector<int64_t>& damaged)
      : pattern(pattern), damaged(damaged) {
    for (const auto& c : pattern) {
      number = number << 1;
      mask = mask << 1;
      if (c == '#') {
        number += 1;
      }
      if (c == '?') {
        mask_N += 1;
        mask += 1;
      }
    }
  }
  friend ostream& operator<<(ostream& os, const record& r) {
    for (int64_t i = 1 << (r.pattern.size() - 1); i > 0; i = i >> 1) {
      os << (r.number & i ? '1' : '0');
    }
    os << '|';
    for (int64_t i = 1LL << (r.pattern.size() - 1); i > 0; i = i >> 1) {
      os << (r.mask & i ? '1' : '0');
    }
    for (const auto& num : r.damaged) {
      os << " " << num;
    }
    return os;
  }
  string print(int64_t num) const {
    stringstream ss;
    for (int64_t i = 1LL << (pattern.size() - 1); i > 0; i = i >> 1) {
      ss << (num & i ? '1' : '0');
    }
    return ss.str();
  }
  int64_t count() const {
    int count = 0;
    for (int64_t j = 0; j < (1 << mask_N); j++) {
      int64_t bits2try = j;
      int64_t newnum = 0;
      for (int64_t i = 1LL << (pattern.size() - 1); i > 0; i = i >> 1) {
        if (i & mask) {
          newnum += (bits2try & 1 ? mask & i : 0);
          bits2try = bits2try >> 1;
        } else {
          newnum += number & i;
        }
      }
      if (valid(newnum)) {
        // cout << print(newnum) << "\n";
        count++;
      }
    }
    return count;
  }
  bool valid(int64_t val = -1) const {
    bool ret = true;
    if (val < 0) {
      val = number;
    }
    size_t didx = 0;
    int64_t count = (didx < damaged.size() ? damaged[didx] : 0);
    bool need_gap = false;
    for (int64_t i = 1LL << (pattern.size() - 1); i > 0; i = i >> 1) {
      bool bit = (val & i ? true : false);
      if (bit && need_gap) {
        return false;
      }
      if (count > 0 && bit) {
        count--;
      } else if (count > 0 && !bit) {
        if (count < damaged[didx]) {
          return false;
        }
        need_gap = false;
      }
      if (count == 0 && didx < damaged.size()) {
        need_gap = true;
        didx++;
        if (didx < damaged.size()) {
          count = damaged[didx];
        }
      }
    }
    if (didx != damaged.size()) {
      return false;
    }
    if (count != 0) {
      return false;
    }

    return ret;
  }
};

vector<record> getData(istream& in) {
  string s;
  vector<record> records;
  while (getline(in, s) && s.size()) {
    size_t end = s.find_first_of(" ");
    string pattern = s.substr(0, end);
    vector<int64_t> damaged;
    while (end != string::npos) {
      size_t start = end + 1;
      end = s.find_first_of(",", start);
      damaged.push_back(std::stoll(s.substr(start, end)));
    }
    records.emplace_back(pattern, damaged);
  }
  return records;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "example.input");
  ifstream in(filename);
  vector<record> records = getData(in);
  int64_t sum = 0;
  for (const auto& record : records) {
    sum += record.count();
    cout << record.pattern.size() << " - " << record.count() << "\n";
  }
  cout << "Total: " << sum << "\n";
  return 0;
}
#endif