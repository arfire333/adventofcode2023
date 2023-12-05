#include "libaoc.h"
#include <cstdlib>
#include <filesystem>
#include <sstream>
using namespace std;
namespace aoc {
string dataFilename(const char* argv0, const string dataset) {
  stringstream ss;
  ss << getenv("BASE_DIR") << "/" << filesystem::path(argv0).stem().string()
     << "/" << dataset;
  return ss.str();
}

vector<int64_t> getNumbers(const string s) {
  vector<int64_t> nums;
  int start = 0;
  int end = 0;
  do {
    start = s.find_first_of("0123456789", end);
    end = s.find_first_not_of("0123456789", start);
    if (start >= 0) {
      string num = s.substr(start, end);
      char* p_end{};
      nums.push_back(strtoll(num.c_str(), &p_end, 10));
    }
  } while (end != string::npos);
  return nums;
}
}  // namespace aoc