#include "dbg.hh"
#include "dbg_struct.hh"

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

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

int main() {
  int n = 42;
  DBG(n);
  std::vector v{1, 2, 3};
  DBG(v);
  std::vector vv{v, v, v};
  DBG(vv);
  char c = 'x';
  DBG(c);
  std::string s = "foo";
  DBG(s);
  std::map<int, int> m{{1, 2}, {3, 4}};
  DBG(m);
  std::tuple t(1, 2., "f");
  DBG(t);
  std::array a{1, 2, 3};
  DBG(a);
  int arr[] = {1, 2, 3};
  DBG(arr);
  std::optional<int> o;
  DBG(o);
  o = 42;
  DBG(o);
  int* p = nullptr;
  DBG(p);
  p = &n;
  DBG(p);
  std::variant<int, double, std::string> var = "bar";
  DBG(var);

  auto sink = [](std::unique_ptr<int> p) { DBG(p); };
  sink(DBG(std::make_unique<int>(42)));

  DBG(user_defined{});
  DBG(plain_struct{});

  auto l = list{1, new list{2}};
  DBG(l);
}
