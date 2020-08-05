#include "dbg/dbg.hh"

#include <map>
#include <string>

int main() {
  std::map<std::string, int> m{{"foo", 1}, {"bar", 2}};
  DBG(m);
}
