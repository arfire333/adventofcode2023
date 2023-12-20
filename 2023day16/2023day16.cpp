#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<string>& grid) {
  string s;
  while (getline(in, s) && s.size()) {
    grid.emplace_back(s);
  }
}

enum class dir_t { UP, DOWN, LEFT, RIGHT };
struct pos_t {
  int row = 0;
  int col = 0;
  dir_t in_direction = dir_t::RIGHT;
  pos_t(int r, int c, dir_t d) : row(r), col(c), in_direction(d) {}

  friend bool operator<(const pos_t& l, const pos_t& r) {
    return std::tie(l.row, l.col, l.in_direction) <
           std::tie(r.row, r.col, r.in_direction);
  }
};

int64_t simple_count(const vector<vector<int64_t>>& grid_count) {
  int64_t sum = 0;
  for (const auto& row : grid_count) {
    for (auto val : row) {
      sum += (val > 0 ? 1 : 0);
    }
  }

  return sum;
}
void print(const vector<vector<int64_t>>& grid_count) {
  cout << "\n";
  for (const auto& row : grid_count) {
    for (auto val : row) {
      cout << val << " ";
    }
    cout << "\n";
  }
}

pos_t next_pos(dir_t new_direction, pos_t curr) {
  pos_t next(curr);
  switch (new_direction) {
    case dir_t::UP:
      next.row--;
      break;
    case dir_t::DOWN:
      next.row++;
      break;
    case dir_t::LEFT:
      next.col--;
      break;
    case dir_t::RIGHT:
      next.col++;
      break;
    default:
      break;
  }
  next.in_direction = new_direction;
  return next;
}
vector<dir_t> next_dir(char m, dir_t in_direction) {
  vector<dir_t> next_direction;
  switch (m) {
    case '-':
      switch (in_direction) {
        case dir_t::UP:
        case dir_t::DOWN:
          next_direction.push_back(dir_t::LEFT);
          next_direction.push_back(dir_t::RIGHT);
          break;
        case dir_t::LEFT:
        case dir_t::RIGHT:
          next_direction.push_back(in_direction);
          break;
      }
      break;
    case '|':
      switch (in_direction) {
        case dir_t::UP:
        case dir_t::DOWN:
          next_direction.push_back(in_direction);
          break;
        case dir_t::LEFT:
        case dir_t::RIGHT:
          next_direction.push_back(dir_t::UP);
          next_direction.push_back(dir_t::DOWN);
          break;
      }
      break;
    case '/':
      switch (in_direction) {
        case dir_t::UP:
          next_direction.push_back(dir_t::RIGHT);
          break;
        case dir_t::DOWN:
          next_direction.push_back(dir_t::LEFT);
          break;
        case dir_t::LEFT:
          next_direction.push_back(dir_t::DOWN);
          break;
        case dir_t::RIGHT:
          next_direction.push_back(dir_t::UP);
          break;
      }
      break;
    case '\\':
      switch (in_direction) {
        case dir_t::UP:
          next_direction.push_back(dir_t::LEFT);
          break;
        case dir_t::DOWN:
          next_direction.push_back(dir_t::RIGHT);
          break;
        case dir_t::LEFT:
          next_direction.push_back(dir_t::UP);
          break;
        case dir_t::RIGHT:
          next_direction.push_back(dir_t::DOWN);
          break;
      }
      break;
    default:  // '.' Case
      next_direction.push_back(in_direction);
      break;
  }

  return next_direction;
}
void travel(pos_t start,
            const vector<string>& grid,
            vector<vector<int64_t>>& grid_count) {
  set<pos_t> visited;
  queue<pos_t> q;
  q.push(start);
  while (!q.empty()) {
    auto curr = q.front();
    q.pop();
    if (visited.count(curr)) {
      continue;
    }
    visited.insert(curr);
    if (curr.row < 0 || curr.row >= grid.size() || curr.col < 0 ||
        curr.col >= grid[0].size()) {
      continue;
    }
    grid_count[curr.row][curr.col]++;
    for (const auto& next_direction :
         next_dir(grid[curr.row][curr.col], curr.in_direction)) {
      q.push(next_pos(next_direction, curr));
    }
  }

  return;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  vector<string> grid;
  getData(in, grid);
  vector<vector<int64_t>> grid_count(grid.size(),
                                     vector<int64_t>(grid[0].size(), 0));

  pos_t start(0, 0, dir_t::RIGHT);
  for (const auto& it : grid) {
    cout << it << "\n";
  }
  travel(start, grid, grid_count);
  cout << "Part 1 Count: " << simple_count(grid_count) << "\n";

  auto GRID_HEIGHT = static_cast<int>(grid.size());
  auto GRID_WIDTH = static_cast<int>(grid[0].size());

  int64_t max_count = 0;
  // Top row
  for (int c = 0; c < GRID_WIDTH; c++) {
    int64_t current_count = 0;
    vector<vector<int64_t>> grid_count2(GRID_HEIGHT,
                                        vector<int64_t>(GRID_WIDTH, 0));
    travel(pos_t(0, c, dir_t::DOWN), grid, grid_count2);
    current_count = simple_count(grid_count2);
    if (current_count > max_count) {
      max_count = current_count;
    }
  }
  cout << "Top Checked\n";
  // Bottom row
  for (int c = 0; c < GRID_WIDTH; c++) {
    int64_t current_count = 0;
    vector<vector<int64_t>> grid_count2(GRID_HEIGHT,
                                        vector<int64_t>(GRID_WIDTH, 0));
    travel(pos_t(GRID_HEIGHT - 1, c, dir_t::UP), grid, grid_count2);
    current_count = simple_count(grid_count2);
    if (current_count > max_count) {
      max_count = current_count;
    }
  }
  cout << "Bottom Checked\n";
  // left column
  for (int r = 0; r < GRID_HEIGHT; r++) {
    int64_t current_count = 0;
    vector<vector<int64_t>> grid_count2(GRID_HEIGHT,
                                        vector<int64_t>(GRID_WIDTH, 0));
    travel(pos_t(r, 0, dir_t::RIGHT), grid, grid_count2);
    current_count = simple_count(grid_count2);
    if (current_count > max_count) {
      max_count = current_count;
    }
  }
  cout << "Left Checked\n";
  // right column
  for (int r = 0; r < GRID_HEIGHT; r++) {
    int64_t current_count = 0;
    vector<vector<int64_t>> grid_count2(GRID_HEIGHT,
                                        vector<int64_t>(GRID_WIDTH, 0));
    travel(pos_t(r, GRID_WIDTH - 1, dir_t::LEFT), grid, grid_count2);
    current_count = simple_count(grid_count2);
    if (current_count > max_count) {
      max_count = current_count;
    }
  }
  cout << "Right Checked\n";
  cout << "Part 2 Count: " << max_count << "\n";

  return 0;
}
#endif