#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct pos_t {
  int64_t r = 0;
  int64_t c = 0;

  friend bool operator<(const pos_t& l_in, const pos_t& r_in) {
    return std::tie(l_in.r, l_in.c) < std::tie(r_in.r, r_in.c);
  }
};

const set<pos_t> SHIFTS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void getData(istream& in, vector<string>& elfmap, pos_t& start) {
  string s;
  int possible_start_row = 0;
  while (getline(in, s) && s.size()) {
    if (auto possible_start_col = s.find_first_of("S");
        possible_start_col != string::npos) {
      start.c = static_cast<int>(possible_start_col);
      start.r = possible_start_row;
    }
    elfmap.push_back(s);
    possible_start_row++;
  }
}

int64_t part1_steps(const vector<string>& elfmap,
                    pos_t start,
                    int num_steps = 6) {
  set<pos_t> currset = {start};
  set<pos_t> nextset;
  for (auto i = 0; i < num_steps; i++) {
    nextset.clear();
    for (auto p : currset) {
      for (const auto& shift : SHIFTS) {
        pos_t next = {p.r + shift.r, p.c + shift.c};
        if (next.r < 0 || next.r >= elfmap.size() || next.c < 0 ||
            next.c >= elfmap[0].size() || elfmap[next.r][next.c] == '#') {
          continue;
        }
        nextset.insert(next);
      }
    }
    swap(currset, nextset);
  }

  return currset.size();
}
int64_t part2_steps(const vector<string>& elfmap,
                    pos_t start,
                    int num_steps = 6) {
  int64_t height = elfmap.size();
  int64_t width = elfmap[0].size();
  set<pos_t> currset = {start};
  set<pos_t> nextset;
  for (auto i = 0; i < num_steps; i++) {
    nextset.clear();
    for (auto p : currset) {
      for (const auto& shift : SHIFTS) {
        pos_t check = {(p.r + shift.r), (p.c + shift.c)};
        pos_t next = check;
        check.r = check.r % height;
        check.c = check.c % width;
        if (check.r < 0) {
          check.r += height;
        };
        if (check.c < 0) {
          check.c += width;
        };
        if (elfmap[check.r][check.c] == '#') {
          continue;
        }
        nextset.insert(next);
      }
    }
    swap(currset, nextset);
  }

  return currset.size();
}
int64_t pos2idx(const pos_t& position, int64_t width) {
  return position.r * width + position.c;
}
pos_t idx2pos(int64_t idx, int64_t width) {
  return {idx / width, idx % width};
}

vector<vector<int64_t>> part2_prep(const vector<string>& elfmap) {
  int64_t height = elfmap.size();
  int64_t width = elfmap[0].size();
  int64_t N = height * width;
  vector<vector<int64_t>> adj(N, vector<int64_t>(N, 0));
  // row is from
  for (int r = 0; r < elfmap.size(); r++) {
    for (int c = 0; c < elfmap[0].size(); c++) {
      pos_t p = {r, c};
      int64_t p_idx = pos2idx(p, width);
      for (const auto& shift : SHIFTS) {
        pos_t check = {(p.r + shift.r), (p.c + shift.c)};
        auto next = check;
        if (check.r < 0) {
          check.r += height;
        };
        if (check.c < 0) {
          check.c += width;
        };
        if (elfmap[check.r][check.c] != '#') {
          int64_t next_idx = pos2idx(next, width);
          adj[p_idx][next_idx]++;
        }
      }
    }
  }

  return adj;
}
void print(const vector<vector<int64_t>>& adj) {
  for (const auto& row : adj) {
    for (const auto& col : row) {
      cout << setw(2) << col;
    }
    cout << "\n";
  }
}

int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "example.input");
  ifstream in(filename);
  vector<string> elfmap;
  pos_t start = {0, 0};
  getData(in, elfmap, start);
  for (const auto& row : elfmap) {
    cout << row << "\n";
  }
  cout << part1_steps(elfmap, start, 64) << "\n";
  cout << part2_steps(elfmap, start, 6) << "\n";
  cout << part2_steps(elfmap, start, 5) << "\n";
  cout << part2_steps(elfmap, start, 10) << "\n";
  cout << part2_steps(elfmap, start, 50) << "\n";
  cout << part2_steps(elfmap, start, 100) << "\n";
  cout << part2_steps(elfmap, start, 500) << "\n";
  return 0;
}