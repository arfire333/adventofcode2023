#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<string>& board) {
  string s;
  while (getline(in, s) && s.size()) {
    board.push_back(s);
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day14", "example.input");
  ifstream in(filename);
  vector<string> board;
  getData(in, board);
  for (const auto& line : board) {
    cout << line << "\n";
  }

  return 0;
}
#endif