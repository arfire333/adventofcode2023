#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int64_t EXPANSION = 1000000;  // Change to 2 for part 1.
void print(const vector<vector<int64_t>>& in) {
  for (const auto& row : in) {
    for (const auto& c : row) {
      cout << (c == 1 ? "." : "O");
    }
    cout << "\n";
  }
}

vector<vector<int64_t>> expand(const vector<string>& in) {
  vector<vector<int64_t>> map(in.size(), vector<int64_t>(in[0].size(), 1));

  for (int r = 0; r < in.size(); r++) {
    bool empty = true;
    for (int c = 0; c < in[0].size(); c++) {
      if (in[r][c] == '#') {
        empty = false;
      }
    }
    if (empty) {
      for (int c = 0; c < map[0].size(); c++) {
        map[r][c] = EXPANSION;
      }
    }
  }

  for (auto c = 0; c < in[0].size(); c++) {
    int pound_count = 0;
    int r = 0;
    for (const auto& l : in) {
      if (l[c] == '#') {
        pound_count++;
      }
      r++;
    }
    if (pound_count == 0) {
      for (r = 0; r < in.size(); r++) {
        map[r][c] = EXPANSION;
      }
    }
  }
  return map;
}

vector<vector<int64_t>> getData(istream& in, vector<string>& data) {
  string s;
  while (getline(in, s) && s.size()) {
    data.emplace_back(s);
    cout << s << "\n";
  }
  cout << "========================\n";
  return expand(data);
}

struct point {
  int64_t x;
  int64_t y;

  point(int64_t x, int64_t y) : x(x), y(y) {}

  int64_t distance(const vector<vector<int64_t>>& map,
                   const struct point& other) const {
    int64_t distance = 0;
    if (x > other.x) {
      for (int64_t c = x; c > other.x; c--) {
        distance += map[y][c];
      }
    } else {
      for (int64_t c = x; c < other.x; c++) {
        distance += map[y][c];
      }
    }
    if (y > other.y) {
      for (int64_t r = y; r > other.y; r--) {
        distance += map[r][other.x];
      }
    } else {
      for (int64_t r = y; r < other.y; r++) {
        distance += map[r][other.x];
      }
    }

    return distance;
  }

  friend ostream& operator<<(ostream& os, const point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

vector<struct point> getPoints(const vector<string>& in) {
  vector<struct point> points;
  for (int64_t r = 0; r < in.size(); r++) {
    for (int64_t c = 0; c < in[0].size(); c++) {
      if (in[r][c] == '#') {
        points.emplace_back(point(c, r));
        cout << points.back();
        cout << "\n";
      }
    }
  }
  return points;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  vector<string> data;
  vector<vector<int64_t>> map = getData(in, data);
  vector<point> points = getPoints(data);
  print(map);
  int64_t sum = 0;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      int64_t distance = points[i].distance(map, points[j]);
      cout << points[i] << " - " << points[j] << " : " << distance << "\n";
      sum += distance;
    }
  }
  cout << "total distance: " << sum << "\n";

  return 0;
}
#endif