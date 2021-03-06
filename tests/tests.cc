#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "dbg/dbg.hh"
#include "dbg/dbg_struct.hh"

#if __has_include(<range/v3/all.hpp>)
#  include <range/v3/all.hpp>
#  define DBG_HAVE_RANGES
#endif

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

struct user_defined_range {
  std::vector<int> v;
  auto begin() const noexcept { return v.begin(); }
  auto end() const noexcept { return v.end(); }
};

TEST_CASE("tests") {
  CHECK(to_string(1) == "1");
  CHECK(to_string(4.2) == "4.2");
  int n = 42;
  CHECK(to_string(n) == "42");
  CHECK(to_string(true) == "true");
  CHECK(to_string(false) == "false");
  std::vector v{1, 2, 3};
  CHECK(to_string(v) == "[1, 2, 3]");
  CHECK(to_string(begin(v)) == "1");
  std::vector vv{v, v, v};
  CHECK(to_string(vv) == "[[1, 2, 3], [1, 2, 3], [1, 2, 3]]");
  char c = 'x';
  CHECK(to_string(c) == "'x'");
  std::string s = "foo";
  CHECK(to_string(s) == "\"foo\"");
  std::map<int, int> m{{1, 2}, {3, 4}};
  CHECK(to_string(m) == "[(1, 2), (3, 4)]");
  auto t = std::make_tuple(1, 2., "f");
  CHECK(to_string(t) == "(1, 2, \"f\")");
  std::array a{1, 2, 3};
  CHECK(to_string(a) == "[1, 2, 3]");
  int arr[] = {1, 2, 3};
  CHECK(to_string(arr) == "[1, 2, 3]");
  CHECK(to_string(std::nullopt) == "null");
  std::optional<int> o;
  CHECK(to_string(o) == "null");
  o = 42;
  CHECK(to_string(o) == "42");
  CHECK(to_string(nullptr) == "null");
  int* p = nullptr;
  CHECK(to_string(p) == "null");
  p = &n;
  CHECK(to_string(p) == to_string(n));
  void* vp = &n;
  CHECK(to_string(vp).substr(0, 2) == "0x");
  std::variant<int, double, std::string> var = "bar";
  CHECK(to_string(var) == "\"bar\"");

  auto tt = std::make_tuple(std::make_tuple(1, 2), std::make_tuple(3, 4));
  CHECK(to_string(tt) == "((1, 2), (3, 4))");

  CHECK(to_string(user_defined{}) == "user_defined 42");
  CHECK(to_string(plain_struct{}) == "plain_struct{0, 0}");
  CHECK(to_string(user_defined_range{{1, 2, 3}}) == "[1, 2, 3]");

  auto l = list{1, new list{2}};
  CHECK(to_string(l) == "list{1, list{2, null}}");

  CHECK(to_string(std::make_pair('a', 'b')) == "('a', 'b')");

#ifdef DBG_HAVE_RANGES
  auto rng = ranges::views::iota(1, 4)                                //
             | ranges::views::transform([](auto x) { return x * x; }) //
             | ranges::views::filter([](auto x) { return x % 2 == 1; });
  CHECK(to_string(rng) == "[1, 9]");
#endif
}
