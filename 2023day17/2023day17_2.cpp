#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void getData(istream& in, vector<string>& city) {
  string s;
  while (getline(in, s) && s.size()) {
    for (auto& block : s) {
      block = block - '0';
    }
    city.push_back(s);
  }
}
enum class dir_t { N, E, S, W };
static const map<dir_t, char> dir2char = {
    {dir_t::N, 'N'},
    {dir_t::E, 'E'},
    {dir_t::S, 'S'},
    {dir_t::W, 'W'},
};

struct pos_t {
  int row = 0;
  int col = 0;
  int time = 0;
  dir_t direction = dir_t::E;
  int64_t heatloss = INT_MAX;

  pos_t(int r, int c, int t, dir_t d) : row(r), col(c), time(t), direction(d) {}

  friend bool operator<(const pos_t& l, const pos_t& r) {
    return std::tie(l.row, l.col, l.time, l.direction) <
           std::tie(r.row, r.col, r.time, r.direction);
  }
  friend bool operator==(const pos_t& l, const pos_t& r) {
    return std::tie(l.row, l.col, l.time, l.direction) ==
           std::tie(r.row, r.col, r.time, r.direction);
  }
  friend ostream& operator<<(ostream& os, const pos_t& p) {
    os << "(" << p.row << ", " << p.col << ", " << p.time << ", "
       << dir2char.at(p.direction) << ", " << p.heatloss << ")";

    return os;
  }
};

class PosCompare {
 public:
  bool operator()(const pos_t& l, const pos_t& r) const {
    return l.heatloss > r.heatloss;
  }
};
bool priority_sort(const pos_t& l, const pos_t& r) {
  return l.heatloss < r.heatloss;
}

int64_t plan(const vector<string>& city) {
  const size_t CITY_LENGTH = city.size();
  const size_t CITY_WIDTH = city[0].size();
  int64_t min_heatloss = INT_MAX;
  vector<dir_t> pos_dir = {dir_t::N, dir_t::E, dir_t::S, dir_t::W};
  vector<pos_t> grid;
  map<pos_t, int64_t> dist;
  map<pos_t, pos_t> prev;
  set<pos_t> visited;
  vector<pos_t> q;
  const size_t MIN_MOVE = 4;
  const size_t MAX_MOVE = 10;
  pos_t INVALID(-1, -1, 0, dir_t::N);
  for (auto r = 0; r < CITY_LENGTH; r++) {
    for (auto c = 0; c < CITY_WIDTH; c++) {
      for (auto t = 1; t <= MAX_MOVE; t++) {
        for (auto d : pos_dir) {
          q.emplace_back(r, c, t, d);
        }
      }
    }
  }
  pos_t start(0, 0, 0, dir_t::E);
  start.heatloss = 0;
  q.emplace_back(start);
  while (!q.empty()) {
    sort(q.begin(), q.end(), priority_sort);
    auto curr = *q.begin();
    q.erase(q.begin());
    if (curr.heatloss == INT_MAX) {
      continue;
    }
    vector<pos_t> q_update;
    for (auto direction : pos_dir) {
      if (curr.time > 0 && curr.time < MIN_MOVE &&
          curr.direction != direction) {
        continue;
      }
      int next_time = curr.time + 1;
      if (curr.direction != direction) {
        next_time = 1;
      }
      if (curr.direction == dir_t::N && direction == dir_t::S) {
        continue;
      }
      if (curr.direction == dir_t::S && direction == dir_t::N) {
        continue;
      }
      if (curr.direction == dir_t::W && direction == dir_t::E) {
        continue;
      }
      if (curr.direction == dir_t::E && direction == dir_t::W) {
        continue;
      }
      if (next_time > MAX_MOVE) {
        continue;  // Only here if same direction and had 3 moves in same
                   // direction
      }
      int next_row = curr.row;
      int next_col = curr.col;
      if (direction == dir_t::N) {
        next_row--;
      }
      if (direction == dir_t::E) {
        next_col++;
      }
      if (direction == dir_t::W) {
        next_col--;
      }
      if (direction == dir_t::S) {
        next_row++;
      }
      if (next_row < 0 || next_row >= CITY_LENGTH || next_col < 0 ||
          next_col >= CITY_WIDTH) {
        continue;
      }

      int64_t next_heatloss = curr.heatloss + city[next_row][next_col];
      pos_t next(next_row, next_col, next_time, direction);
      next.heatloss = next_heatloss;

      if (visited.find(next) != visited.end()) {
        // already visited so don't do antyhing with it
        continue;
      }
      auto it = dist.find(next);
      bool update = false;
      if (it == dist.end()) {
        dist[next] = next.heatloss;
        update = true;
      } else {
        auto current_next_heatloss = dist.at(next);
        if (next.heatloss < current_next_heatloss) {
          dist[next] = next.heatloss;
          update = true;
        }
      }
      if (update) {
        q_update.push_back(next);
      }
    }
    visited.insert(curr);
    for (auto i = 0; i < q.size(); i++) {
      for (const auto& update : q_update) {
        if (q[i] == update) {
          q[i].heatloss = update.heatloss;
        }
      }
    }
  }

  for (auto&& [f, s] : dist) {
    if (f.row == CITY_LENGTH - 1 && f.col == CITY_WIDTH - 1 &&
        s < min_heatloss) {
      min_heatloss = s;
      cout << f << " = " << f.heatloss << "\n";
    }
  }

  return min_heatloss;
}
#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day17", "user.input");
  ifstream in(filename);
  vector<string> city;
  getData(in, city);
  int64_t heatloss = plan(city);
  cout << "Minimum Heatloss: " << heatloss << "\n";
  return 0;
}
#endif