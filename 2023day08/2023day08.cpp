#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int64_t str2node(const string s) {
  if (s.size() < 3) {
    cerr << "Invalid conversion of " << s << " at " << __FILE__ << ":"
         << __LINE__ << "\n";
    exit(EXIT_FAILURE);
  }
  int64_t val = 0;
  for (int i = 0; i < 3; i++) {
    val = (val << 8) + static_cast<uint8_t>(s[i]);
  }
  return val;
}

char node2char(int64_t node) {
  char ret = static_cast<char>(node & 0xff);
  return ret;
}

string node2string(int64_t node) {
  stringstream ss;
  for (int i = 2; i >= 0; i--) {
    ss << static_cast<char>((node >> (i * 8)) & 0xff);
  }
  return ss.str();
}

void getData(istream& in,
             string& cycle,
             map<int64_t, vector<int64_t>>& graph,
             vector<int64_t>& anodes,
             vector<int64_t>& bnodes) {
  string s;
  getline(in, cycle);
  getline(in, s);
  int count = 0;
  while (getline(in, s) && s.size()) {
    int64_t node = str2node(s.substr(0, s.find_first_of(" ")));
    if ((0xff & node) == static_cast<uint8_t>('A')) {
      anodes.push_back(node);
    } else if ((0xff & node) == static_cast<uint8_t>('Z')) {
      bnodes.push_back(node);
    }
    int64_t left =
        str2node(s.substr(s.find_first_of("(") + 1, s.find_first_of(",")));
    int64_t right =
        str2node(s.substr(s.find_first_of(",") + 2, s.find_first_of(")")));
    vector<int64_t> val = {left, right};
    graph.insert({node, val});
    count++;
  }
  if (count != graph.size()) {
    cerr << "duplicate nodes\n";
    exit(EXIT_FAILURE);
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  string cycle;
  map<int64_t, vector<int64_t>> graph;
  vector<int64_t> anodes;
  vector<int64_t> bnodes;
  getData(in, cycle, graph, anodes, bnodes);
  int64_t start = str2node("AAA");
  int64_t end = str2node("ZZZ");
  int64_t i = 0;
  int64_t curr = start;
  do {
    int64_t idx = i % cycle.size();
    if (cycle[idx] == 'L') {
      auto c = node2string(curr);
      curr = graph[curr][0];
    } else {
      auto c = node2string(curr);
      curr = graph[curr][1];
    }
    i++;
  } while (curr != end);
  cout << "Part 1 Steps: " << i << "\n";

  vector<int64_t> current = anodes;
  vector<bool> at_z(current.size(), false);
  vector<int64_t> first_end(anodes.size(), 0);
  int done = 0;
  i = 0;
  do {
    int64_t idx = i % cycle.size();
    for (int j = 0; j < current.size(); j++) {
      if (cycle[idx] == 'L') {
        current[j] = graph[current[j]][0];
      } else {
        current[j] = graph[current[j]][1];
      }
      for (auto b : bnodes) {
        if (b == current[j]) {
          if (first_end[j] == 0) {
            done++;
            first_end[j] = i + 1;
          }
          break;
        }
      }
    }
    i++;
  } while (done < current.size());
  int64_t steps = lcm(first_end[0], first_end[1]);
  for (int i = 2; i < first_end.size(); i++) {
    steps = lcm(steps, first_end[i]);
  }

  cout << "Part 2 Steps: " << steps << "\n";
  return 0;
}
#endif