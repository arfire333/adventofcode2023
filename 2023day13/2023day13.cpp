#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<int64_t>& data) {
  string s;
  while (getline(in, s) && s.size()) {
    data.push_back(atoi(s.c_str()));
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0]);
  ifstream in(filename);
  vector<int64_t> data;
  getData(in, data);
  for (auto it : data) {
    cout << it << "\n";
  }

  return 0;
}
#endif