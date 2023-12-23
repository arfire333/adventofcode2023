#include <assert.h>
#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using part_t = map<char, int64_t>;

enum class part_state { ACCEPT, REJECT };

class workflow {
  string name;
  string checks;
  vector<char> var;
  vector<char> op;
  vector<int64_t> val;
  vector<string> true_result;
  vector<string> false_result;
  // Construct a new workflow with appropriate checks
  void parseChecks() {
    stringstream ss;
    int8_t count = 0;
    size_t start = 0;
    size_t end = checks.find_first_of(":");
    while (end != string::npos) {
      string check = checks.substr(start, end - start);
      var.push_back(check[0]);
      op.push_back(check[1]);
      val.push_back(atoi(check.substr(2).c_str()));
      start = end + 1;
      end = checks.find_first_of(",", start);
      true_result.push_back(checks.substr(start, end - start));
      start = end + 1;
      end = checks.find_first_of(":}", start);
      if (end == string::npos) {
        false_result.push_back(checks.substr(start));
      } else if (checks[end] == ':') {
        string next(2, '\0');
        count++;
        next[0] = count;
        false_result.push_back(next);
      } else {
        assert(false);
      }
    }
  }

 public:
  workflow(const string& name, const string& checks)
      : name(name), checks(checks) {
    parseChecks();
  }
  // process a part through the workflow
  part_state process(const map<string, workflow, std::less<>>& workflows,
                     const part_t& part,
                     size_t i = 0) const {
    part_state state = part_state::REJECT;
    auto curr_var = var[i];
    auto curr_op = op[i];
    auto curr_val = val[i];
    bool result = part.at(curr_var) < curr_val;
    if (curr_op == '>') {
      result = !result;
    }
    if (result) {
      if (true_result[i].compare("A") == 0) {
        state = part_state::ACCEPT;
      } else if (true_result[i].compare("R") == 0) {
        state = part_state::REJECT;
      } else {
        state = workflows.at(true_result[i]).process(workflows, part);
      }
    } else {
      if (false_result[i].compare("A") == 0) {
        state = part_state::ACCEPT;
      } else if (false_result[i].compare("R") == 0) {
        state = part_state::REJECT;
      } else if (false_result[i][0] < '\010') {
        state = process(workflows, part, i + 1);
      } else {
        state = workflows.at(false_result[i]).process(workflows, part, 0);
      }
    }
    return state;
  };
};

void getData(istream& in,
             vector<part_t>& parts,
             map<string, workflow, std::less<>>& workflows) {
  string s;
  while (getline(in, s) && s.size()) {
    size_t start = 0;
    auto end = s.find_first_of("{");
    string workflow_name = s.substr(start, end);
    start = end + 1;
    end = s.find_last_of("}");
    string checks = s.substr(start, end - start);
    auto&& [it, success] =
        workflows.try_emplace(workflow_name, workflow_name, checks);
    assert(success);
  }
  while (getline(in, s) && s.size()) {
    int64_t x = 0;
    int64_t m = 0;
    int64_t a = 0;
    int64_t s2 = 0;
    sscanf(s.c_str(), "{x=%ld,m=%ld,a=%ld,s=%ld}", &x, &m, &a, &s2);
    part_t new_part = {{'x', x}, {'m', m}, {'a', a}, {'s', s2}};
    parts.emplace_back(new_part);
  }
};

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  vector<part_t> parts;
  map<string, workflow, std::less<>> workflows;
  getData(in, parts, workflows);
  int64_t accept = 0;
  int64_t reject = 0;
  int64_t sum = 0;
  for (const auto& part : parts) {
    auto state = workflows.at("in").process(workflows, part);
    if (state == part_state::ACCEPT) {
      accept++;
      for_each(part.begin(), part.end(), [&sum](auto p) { sum += p.second; });
    } else {
      reject++;
    }
  }
  cout << "Part 1: " << sum << "\n";
  return 0;
}
#endif