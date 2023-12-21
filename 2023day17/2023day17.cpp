#include <libaoc.h>
#include <stdint.h>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
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
  int64_t heatloss = 0;
  string history;

  pos_t(int r, int c, int t, dir_t d) : row(r), col(c), time(t), direction(d) {}

  friend bool operator<(const pos_t& l, const pos_t r) {
    return std::tie(l.row, l.col, l.time, l.direction) <
           std::tie(r.row, r.col, r.time, r.direction);
  }
  friend ostream& operator<<(ostream& os, const pos_t& p) {
    os << "(" << p.row << ", " << p.col << ", " << p.time << ", "
       << dir2char.at(p.direction) << ", " << p.heatloss << ")";

    return os;
  }
};

int64_t plan(const vector<string>& city) {
  stringstream ss;
  int64_t min_heatloss = INT_MAX;
  vector<dir_t> pos_dir = {dir_t::N, dir_t::E, dir_t::S, dir_t::W};
  queue<pos_t> q;
  map<pos_t, int64_t> visited;

  pos_t start(0, 0, 0, dir_t::E);
  q.push(start);
  while (!q.empty()) {
    auto curr = q.front();
    q.pop();
    ss.str("");

    // Check if at end
    if (curr.row == city.size() - 1 && curr.col == city[0].size() - 1) {
      if (curr.heatloss < min_heatloss) {
        cout << "End: " << curr.heatloss << " : " << curr.history << "\n";
        min_heatloss = curr.heatloss;
      }
    }
    for (auto direction : pos_dir) {
      ss.str("");
      auto next = curr;
      next.time++;
      ss << curr.history;
      if (curr.direction != direction) {
        next.time = 1;
      }
      // Can't reverse
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
      if (next.time > 3) {
        continue;  // Only here if same direction and had 3 moves in same
                   // direction
      }
      next.direction = direction;
      if (next.direction == dir_t::N) {
        next.row--;
      }
      if (next.direction == dir_t::E) {
        next.col++;
      }
      if (next.direction == dir_t::W) {
        next.col--;
      }
      if (next.direction == dir_t::S) {
        next.row++;
      }
      if (next.row < 0 || next.row >= city.size() || next.col < 0 ||
          next.col >= city[0].size()) {
        continue;
      }
      next.heatloss += city[next.row][next.col];
      if (visited.count(next)) {
        auto existing = visited.at(next);
        if (existing < next.heatloss) {
          continue;  // Already been there after that many hops so nothing to
                     // learn
        } else {
          visited.erase(next);
        }
      }
      ss << next;

      next.history = ss.str();
      q.emplace(next);
      visited.emplace(next, next.heatloss);
    }
  }
  return min_heatloss;
}
#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  vector<string> city;
  getData(in, city);
  int64_t heatloss = plan(city);
  cout << "Minimum Heatloss: " << heatloss << "\n";
  return 0;
}
#endif