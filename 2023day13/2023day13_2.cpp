#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<vector<string>>& patterns) {
  string s;
  vector<string> pattern;
  while (getline(in, s)) {
    if (s.size() > 0) {
      pattern.emplace_back(s);
    } else {
      patterns.emplace_back(pattern);
      pattern.clear();
    }
  }
  if (!pattern.empty()) {
    patterns.emplace_back(pattern);
  }
}

bool match(const char l, const char r) {
  return l == r;
}

int col_match(const vector<string>& pattern, int left, int right) {
  if (left < 0) {
    return 0;
  }
  if (right > pattern[0].size()) {
    return 0;
  }
  int count = 0;
  for (int i = 0; i < pattern.size(); i++) {
    if (pattern[i][left] != pattern[i][right]) {
      count++;
    }
  }
  return count;
}

int row_match(const vector<string>& pattern, int top, int bot) {
  if (top < 0) {
    return static_cast<int>(pattern[0].size());
  }
  if (bot >= pattern.size()) {
    return static_cast<int>(pattern[0].size());
  }
  int count = 0;
  for (int i = 0; i < pattern[0].size(); i++) {
    if (pattern[top][i] != pattern[bot][i]) {
      count++;
    }
  }
  return count;
}
int horizontal_split(const vector<string>& pattern) {
  int success = 0;
  for (int start = 0; start < pattern.size(); start++) {
    int top = start;
    int bot = top + 1;
    int count = 0;
    while (top >= 0 && bot < pattern.size()) {
      count += row_match(pattern, top, bot);
      top--;
      bot++;
    }
    if (count == 1) {
      success = start + 1;
      break;
    }
  }
  return success;
}
int vertical_split(const vector<string>& pattern) {
  int success = 0;
  for (int start = 0; start < pattern[0].size(); start++) {
    int left = start;
    int right = left + 1;
    int count = 0;
    while (left >= 0 && right < pattern[0].size()) {
      count += col_match(pattern, left, right);
      left--;
      right++;
    }
    if (count == 1) {
      success = start + 1;
      break;
    }
  }
  return success;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day13", "user.input");
  ifstream in(filename);
  vector<vector<string>> patterns;
  getData(in, patterns);
  auto even_count = 0;
  int64_t total = 0;
  for (int i = 0; i < patterns.size(); i++) {
    const auto& pattern = patterns[i];
    const auto& height = pattern.size();
    const auto& width = pattern[0].size();
    if (height % 2 == 0 || width % 2 == 0) {
      even_count++;
    }
    int hsplit = horizontal_split(pattern);
    int vsplit = vertical_split(pattern);
    cout << string(pattern[0].size(), '=') << " " << i << " height=" << height
         << " width=" << width << " hsplit=" << hsplit << " vsplit=" << vsplit
         << "\n";

    total += 100 * hsplit + vsplit;
    for (const auto& line : pattern) {
      cout << line << "\n";
    }
  }
  cout << "Even Count: " << even_count << "\n";
  cout << "Total Count: " << total << "\n";

  return 0;
}
#endif