#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<int64_t>& data) {
  string s;
  while (getline(cin, s) && s.size()) {
    data.push_back(atoi(s.c_str()));
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  vector<int64_t> data;
  getData(cin, data);
  for (auto it : data) {
    cout << it << "\n";
  }

  return 0;
}
#endif