# DBG

###### A rust-like DBG macro

This library simplifes quick debug printing by providing the `DBG` which can printt any type from the standard library and also user defined ranges. The library requires C++20 since it uses concepts for overload resolution.

## Example

```C++
#include "dbg/dbg.hh"
std::map<std::string> m{{"foo", 1}, {"bar", 2}};
DBG(m);
```

This prints

```
../example/example.cc(8): m = [(bar, 2), (foo, 1)]
```

Apart from the concept of the map, `DBG` prints also the filename, the line and the variable name.