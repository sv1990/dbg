#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "dbg/dbg.hh"
#include "dbg/dbg_struct.hh"

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::string to_string(const T& x) {
  std::ostringstream oss;
  dbg::print(oss, x);
  return std::move(oss).str();
}

class user_defined {
  int n = 42;

public:
  int get_n() const noexcept { return n; }
};
template <>
struct dbg::printer<user_defined> {
  static void print(std::ostream& os, user_defined u) noexcept {
    os << "user_defined " << u.get_n();
  }
};

struct plain_struct {
  int a = 0, b = 0;
};

struct list {
  int val;
  list* next = nullptr;
};

TEST_CASE("tests") {
  CHECK(to_string(1) == "1");
  CHECK(to_string(4.2) == "4.2");
  int n = 42;
  CHECK(to_string(n) == "42");
  std::vector v{1, 2, 3};
  CHECK(to_string(v) == "[1, 2, 3]");
  std::vector vv{v, v, v};
  CHECK(to_string(vv) == "[[1, 2, 3], [1, 2, 3], [1, 2, 3]]");
  char c = 'x';
  CHECK(to_string(c) == "'x'");
  std::string s = "foo";
  CHECK(to_string(s) == "\"foo\"");
  std::map<int, int> m{{1, 2}, {3, 4}};
  CHECK(to_string(m) == "[(1, 2), (3, 4)]");
  std::tuple t(1, 2., "f");
  CHECK(to_string(t) == "(1, 2, \"f\")");
  std::array a{1, 2, 3};
  CHECK(to_string(a) == "[1, 2, 3]");
  int arr[] = {1, 2, 3};
  CHECK(to_string(arr) == "[1, 2, 3]");
  std::optional<int> o;
  CHECK(to_string(o) == "null");
  o = 42;
  CHECK(to_string(o) == "42");
  int* p = nullptr;
  CHECK(to_string(p) == "null");
  p = &n;
  CHECK(to_string(p) == to_string(n));
  std::variant<int, double, std::string> var = "bar";
  CHECK(to_string(var) == "\"bar\"");

  CHECK(to_string(user_defined{}) == "user_defined 42");
  CHECK(to_string(plain_struct{}) == "plain_struct{0, 0}");

  auto l = list{1, new list{2}};
  CHECK(to_string(l) == "list{1, list{2, null}}");
}