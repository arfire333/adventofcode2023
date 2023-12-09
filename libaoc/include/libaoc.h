#pragma once
#include <istream>
#include <streambuf>
#include <string>
#include <vector>
namespace aoc {
std::string dataFilename(const char* argv0,
                         std::string_view dataset = "user.input");

std::vector<int64_t> getNumbers(std::string_view s);

struct imemstream : std::streambuf, std::istream {
  imemstream(char* base, size_t size)
      : std::istream(static_cast<std::streambuf*>(this)) {
    char* p(base);
    this->setg(p, p, p + size);
  }
};
}  // namespace aoc