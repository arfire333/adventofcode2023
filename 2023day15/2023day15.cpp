#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int64_t SEED = 0;

vector<string> getData(istream& in) {
  vector<string> steps;
  string s;
  while (getline(in, s) && s.size()) {
    size_t start = 0;
    size_t stop = 0;
    while (stop != string::npos) {
      stop = s.find_first_of(',', start);
      steps.emplace_back(s.substr(start, stop - start));
      start = stop + 1;
    }
  }
  return steps;
}

int64_t init_hash(const string& step, const int64_t seed = SEED) {
  int64_t current_value = seed;
  for (const auto& c : step) {
    current_value += static_cast<int64_t>(c);
    current_value *= 17;
    current_value = current_value % 256;
  }
  return current_value;
}

struct step_t {
  string label = "";
  char operation = '\0';
  int8_t focal_length;
  int64_t hash = 0;
  step_t(const string& s, char c, int8_t fl)
      : label(s), operation(c), focal_length(fl), hash(init_hash(s)) {}
};

void dash(vector<step_t>& lenses, const step_t& step) {
  lenses.erase(remove_if(lenses.begin(), lenses.end(),
                         [&step](const step_t& lense) {
                           return lense.label.compare(step.label) == 0;
                         }),
               lenses.end());
}

void focus(vector<step_t>& lenses, const step_t& step) {
  bool replaced = false;
  for (auto& lense : lenses) {
    if (lense.label.compare(step.label) == 0) {
      lense.focal_length = step.focal_length;
      replaced = true;
      break;
    }
  }
  if (!replaced) {
    lenses.emplace_back(step);
  }
}

int64_t power(const vector<vector<step_t>>& boxes) {
  int64_t focusing_power = 0;
  for (size_t i = 0; i < boxes.size(); i++) {
    for (size_t j = 0; j < boxes[i].size(); j++) {
      int64_t lense_power = (i + 1) * (j + 1) * (boxes[i][j].focal_length);
      focusing_power += lense_power;
    }
  }
  return focusing_power;
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day15", "example.input");
  ifstream in(filename);
  vector<string> input = getData(in);
  vector<struct step_t> steps;
  int64_t sum = 0;
  // Populate steps for part 2
  for (const auto& step_string : input) {
    int64_t val = init_hash(step_string);
    auto operation_index = step_string.find_first_of("=-");
    steps.emplace_back(step_string.substr(0, operation_index),
                       step_string[operation_index],
                       atoi(step_string.substr(operation_index + 1).c_str()));
    sum += val;
  }
  cout << "Part 1 Sum: " << sum << "\n";
  vector<vector<step_t>> boxes(256, vector<step_t>());
  for (const auto& step : steps) {
    switch (step.operation) {
      case '-':
        dash(boxes[step.hash], step);
        break;
      case '=':
        focus(boxes[step.hash], step);
        break;
      default:
        break;
    }
  }
  cout << "Part 2 Total Focusing Power: " << power(boxes) << "\n";
  return 0;
}
#endif