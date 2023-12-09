#include <stdint.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int64_t return1() {
  return 1;
}

const map<string, int8_t, std::less<>> word2int = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

size_t firstDigit(string_view s) {
  for (auto i = 0; i < s.size(); i++) {
    auto c = s[i];
    if (c >= '0' && c <= '9') {
      return i;
    }
  }
  return string::npos;
}

size_t lastDigit(string_view s) {
  for (auto i = s.size(); i != string::npos; i--) {
    auto c = s[i];
    if (c >= '0' && c <= '9') {
      return i;
    }
  }
  return string::npos;
}

int16_t get_value_part1(string_view s) {
  size_t f = firstDigit(s);
  size_t l = lastDigit(s);
  if (f == string::npos || l == string::npos)
    return 0;
  int16_t result = (s[f] - '0') * 10 + s[l] - '0';
  return result;
}

int64_t get_value_part2(string_view s) {
  size_t min_idx = firstDigit(s);
  size_t min_idx_val = (min_idx != string::npos ? s[min_idx] - '0' : 0);
  if (min_idx == string::npos)
    min_idx = INT16_MAX;
  size_t max_idx = lastDigit(s);
  size_t max_idx_val = (max_idx != string::npos ? s[max_idx] - '0' : 0);
  if (max_idx == string::npos) {
    max_idx = 0;
  }
  for (const auto& [first, second] : word2int) {
    size_t fpos = s.find(first);
    size_t lpos = s.rfind(first);
    if (fpos != string::npos && fpos <= min_idx) {
      min_idx = fpos;
      min_idx_val = second;
    }
    if (lpos != string::npos && lpos >= max_idx) {
      max_idx = lpos;
      max_idx_val = second;
    }
  }
  return min_idx_val * 10 + max_idx_val;
}

void getData(vector<int64_t>& d1, vector<int64_t>& d2) {
  string s;

  while (getline(cin, s)) {
    if (s.size() != 0) {
      d1.push_back(get_value_part1(s));
      d2.push_back(get_value_part2(s));
    }
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  vector<int64_t> d1;
  vector<int64_t> d2;
  getData(d1, d2);
  int64_t sum1 = 0;
  int64_t sum2 = 0;

  for (auto i = 0; i < d1.size(); i++) {
    sum1 += d1[i];
    sum2 += d2[i];
  }
  cout << sum1 << "\n";
  cout << sum2 << "\n";

  return 0;
}
#endif