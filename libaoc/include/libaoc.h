#pragma once
#include <istream>
#include <streambuf>
#include <string>
#include <vector>
namespace aoc {
std::string dataFilename(const char* argv0,
                         const std::string dataset = "user.input");

std::vector<int64_t> getNumbers(const std::string s);

struct membuf : std::streambuf {
  membuf(char const* base, size_t size) {
    char* p(const_cast<char*>(base));
    this->setg(p, p, p + size);
  }
};

struct imemstream : virtual membuf, std::istream {
  imemstream(char const* base, size_t size)
      : membuf(base, size), std::istream(static_cast<std::streambuf*>(this)) {}
};
}  // namespace aoc