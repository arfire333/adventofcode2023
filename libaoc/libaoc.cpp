#include "libaoc.h"
#include <cstdlib>
#include <filesystem>
#include <sstream>
using namespace std;
namespace aoc {
string dataFilename(const char* argv0, string_view dataset) {
  stringstream ss;
  ss << getenv("BASE_DIR") << "/" << filesystem::path(argv0).stem().string()
     << "/" << dataset;
  return ss.str();
}

vector<int64_t> getNumbers(string_view s) {
  vector<int64_t> nums;
  int64_t start = 0;
  int64_t end = 0;
  do {
    start = s.find_first_of("0123456789", end);
    end = s.find_first_not_of("0123456789", start);
    int sign = 1;
    if (start > 0 && s[start - 1] == '-') {
      sign = -1;
    }
    if (start >= 0 && start != string::npos) {
      string num(s.substr(start, end));
      nums.push_back(sign * strtoll(num.c_str(), nullptr, 10));
    }
  } while (end != string::npos);
  return nums;
}
}  // namespace aoc