#include <gtest/gtest.h>
#include "template.cpp"

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

TEST(Template, Nothing) {
  ASSERT_EQ(1, 1);
}