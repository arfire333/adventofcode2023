#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class SparseMap {
  string map_name;
  vector<vector<int64_t>> entries;
  vector<bool> visited;

 public:
  void name(string name) { map_name = name; }
  string name() { return map_name; }
  /**
   * Return the destination for a given source.
   */
  int64_t at(int64_t source) {
    int l = 0;
    int r = entries.size() - 1;
    while (l <= r) {
      int delta = (r - l) / 2;
      int i = l + delta;
      auto entry = entries[i];
      if (source >= entry[1] + entry[2]) {
        l = i + 1;
      } else if (source < entry[1]) {
        r = i - 1;
      } else {
        return entry[0] + (source - entry[1]);
      }
    }
    return source;
  }

  void add(const vector<int64_t>& mapping) {
    entries.push_back(mapping);
    visited.push_back(false);
  }

  void sort_entries() {
    sort(entries.begin(), entries.end(),
         [](const vector<int64_t> lhs, const vector<int64_t> rhs) {
           return lhs[1] < rhs[1];
         });
  }
};

void getData(istream& in, vector<int64_t>& seeds, vector<SparseMap>& maps) {
  string s;
  getline(in, s);
  int colon = s.find_first_of(':');
  seeds = aoc::getNumbers(s.substr(colon + 1));
  getline(in, s);
  while (getline(in, s) && s.size()) {
    SparseMap current;
    current.name(s);
    while (getline(in, s) && s.size() > 1) {
      current.add(aoc::getNumbers(s));
    }
    maps.push_back(current);
    maps.back().sort_entries();
  }
}

void part1(const vector<int64_t> seeds, const vector<SparseMap> maps) {
  int64_t min_location = INT64_MAX;
  int64_t recommended_seed = 0;
  for (auto seed : seeds) {
    int64_t next = seed;
    cout << next << ",";
    for (auto map : maps) {
      next = map.at(next);
      cout << next << ",";
    }
    cout << "\n";
    if (next < min_location) {
      min_location = next;
      recommended_seed = seed;
    }
  }
  cout << "Part 1 : Min Location is " << min_location << " from seed "
       << recommended_seed << "\n";
}

void part2(const vector<int64_t> seeds, const vector<SparseMap> maps) {
  int64_t min_location = INT64_MAX;
  int64_t recommended_seed = 0;
  for (int i = 0; i < seeds.size(); i += 2) {
    for (int64_t seed = seeds[i]; seed < seeds[i] + seeds[i + 1]; seed++) {
      if (seed % 1000000 == 0) {
        cout << "Seed #: " << seed << "\n";
      }
      int64_t next = seed;
      for (int i = 0; i < maps.size(); i++) {
        auto map = maps[i];
        next = map.at(next);
      }
      if (next >= 0 && next < min_location) {
        min_location = next;
        recommended_seed = seed;
      }
    }
  }
  cout << "Part 2 : Min Location is " << min_location << " from seed "
       << recommended_seed << "\n";
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  // string filename = aoc::dataFilename(argv[0], "example.input");
  ifstream in(filename);
  vector<int64_t> seeds;
  vector<SparseMap> maps;
  getData(in, seeds, maps);
  part1(seeds, maps);
  vector<vector<int64_t>> seed_ranges;
  int64_t total_seeds = 0;
  for (int i = 0; i < seeds.size(); i += 2) {
    total_seeds += seeds[i + 1];
    seed_ranges.push_back({seeds[i], seeds[i] + seeds[i + 1]});
  }
  cout << "total seeds: " << total_seeds << "\n";
  sort(seed_ranges.begin(), seed_ranges.end());
  for (auto range : seed_ranges) {
    cout << range[0] << " - " << range[1] << "\n";
  }
  part2(seeds, maps);
}
#endif