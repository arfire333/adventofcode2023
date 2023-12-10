#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<string>& grid, pair<int, int>& start) {
  string s;
  int row = 0;
  while (getline(in, s) && s.size()) {
    grid.emplace_back(s);
    if (auto col = s.find_first_of("S"); col != string::npos) {
      start = {row, col};
    }
    row++;
  }
}

bool isValid(size_t R, size_t C, const pair<int, int>& p) {
  if (p.first < 0 || p.first >= R)
    return false;
  if (p.second < 0 || p.second >= C)
    return false;
  return true;
}

vector<pair<int, int>> getNext(const vector<string>& grid,
                               const pair<int, int>& curr) {
  vector<pair<int, int>> ret;
  auto R = grid.size();
  auto C = grid[0].size();
  pair<int, int> left = {curr.first, curr.second - 1};
  pair<int, int> right = {curr.first, curr.second + 1};
  pair<int, int> top = {curr.first - 1, curr.second};
  pair<int, int> bottom = {curr.first + 1, curr.second};
  char c = grid[curr.first][curr.second];
  if ((c == '-' || c == 'J' || c == '7' || c == 'S') && isValid(R, C, left)) {
    char n = grid[left.first][left.second];
    if (n == '-' || n == 'F' || n == 'L') {
      ret.emplace_back(left);
    }
  }
  if ((c == '-' || c == 'F' || c == 'L' || c == 'S') && isValid(R, C, right)) {
    char n = grid[right.first][right.second];
    if (n == '-' || n == 'J' || n == '7') {
      ret.emplace_back(right);
    }
  }
  if ((c == '|' || c == 'J' || c == 'L' || c == 'S') && isValid(R, C, top)) {
    char n = grid[top.first][top.second];
    if (n == '|' || n == 'F' || n == '7') {
      ret.emplace_back(top);
    }
  }
  if ((c == '|' || c == 'F' || c == '7' || c == 'S') && isValid(R, C, bottom)) {
    char n = grid[bottom.first][bottom.second];
    if (n == '|' || n == 'J' || n == 'L') {
      ret.emplace_back(bottom);
    }
  }
  return ret;
}

int64_t furthest(const vector<string>& grid, const pair<int, int>& start) {
  vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), 0));

  int distance = 0;
  queue<pair<int, int>> q;
  q.push(start);
  while (q.size()) {
    auto [r, c] = q.front();
    q.pop();
    for (auto next : getNext(grid, {r, c})) {
      if (!visited[next.first][next.second]) {
        visited[next.first][next.second] = visited[r][c] + 1;
        q.push(next);
      }
    }
    if (visited[r][c] > distance) {
      distance = visited[r][c];
    }
  }
  return distance;
}

void print(const vector<vector<char>>& doubled) {
  for (auto r = 0; r < doubled.size() - 1; r++) {
    for (auto c = 0; c < doubled[0].size() - 1; c++) {
      cout << doubled[r][c];
    }
    cout << "\n";
  }
}
int64_t xloop(const vector<string>& grid, const pair<int, int>& start) {
  vector<vector<char>> visited(grid.size(), vector<char>(grid[0].size(), 0));

  queue<pair<int, int>> q;
  visited[start.first][start.second] = 'S';
  q.push(start);
  while (q.size()) {
    auto [r, c] = q.front();
    q.pop();
    for (auto next : getNext(grid, {r, c})) {
      if (!visited[next.first][next.second]) {
        visited[next.first][next.second] = grid[next.first][next.second];
        q.push(next);
      }
    }
  }
  vector<vector<char>> doubled(grid.size() * 2,
                               vector<char>(grid[0].size() * 2, ' '));
  for (auto r = 0; r < visited.size(); r++) {
    for (auto c = 0; c < visited[0].size(); c++) {
      if (visited[r][c] != ' ' && visited[r][c] != 0) {
        doubled[r * 2][c * 2] = visited[r][c];
      }
    }
  }
  for (auto r = 0; r < doubled.size() - 1; r++) {
    for (auto c = 0; c < doubled[0].size() - 1; c++) {
      if (r % 2 == 1 || c % 2 == 1) {
        char l = ' ';
        if (c > 0)
          l = doubled[r][c - 1];
        char rt = doubled[r][c + 1];
        char t = ' ';
        if (r > 0)
          t = doubled[r - 1][c];
        char b = doubled[r + 1][c];
        if ((l == 'F' || l == 'L' || l == '-' || l == 'S') &&
            (rt == '7' || rt == 'J' || rt == '-' || rt == 'S')) {
          doubled[r][c] = '-';
        }
        if ((t == 'F' || t == '7' || t == '|' || t == 'S') &&
            (b == 'L' || b == 'J' || b == '|' || b == 'S')) {
          doubled[r][c] = '|';
        }
      }
      cout << doubled[r][c];
    }
    cout << "\n";
  }

  // Pick a starting point for fill
  int row = doubled.size() / 2 + 1;  // Pick a line in the middle
  int col = 0;
  for (auto c = 0; c < doubled[0].size() - 1; c++) {
    if (doubled[row][c] == '|' && doubled[row][c + 1] == ' ') {
      col = c + 1;
      break;
    }
  }
  cout << row << " , " << col << " \n";
  q.push({row, col});
  doubled[row][col] = 'I';
  while (q.size()) {
    auto [r, c] = q.front();
    q.pop();
    if (r + 1 < doubled.size() && doubled[r + 1][c] == ' ') {
      doubled[r + 1][c] = 'I';
      q.push({r + 1, c});
    }
    if (r > 0 && doubled[r - 1][c] == ' ') {
      doubled[r - 1][c] = 'I';
      q.push({r - 1, c});
    }
    if (c + 1 < doubled[0].size() && doubled[r][c + 1] == ' ') {
      doubled[r][c + 1] = 'I';
      q.push({r, c + 1});
    }
    if (c > 0 && doubled[r][c - 1] == ' ') {
      doubled[r][c - 1] = 'I';
      q.push({r, c - 1});
    }
  }
  print(doubled);
  int count = 0;
  for (int r = 0; r < doubled.size(); r += 2) {
    for (int c = 0; c < doubled[0].size(); c += 2) {
      if (doubled[r][c] == 'I') {
        count++;
      }
    }
  }
  return count;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day10", "user.input");
  ifstream in(filename);
  pair<int, int> start;
  vector<string> grid;
  getData(in, grid, start);
  auto d = furthest(grid, start);
  cout << "Distance: " << d << "\n";
  auto count = xloop(grid, start);
  cout << "Count: " << count << "\n";
  return 0;
}
#endif