#ifndef DEBUG2_DBG_STRUCT_HH_1587457223874681759_
#define DEBUG2_DBG_STRUCT_HH_1587457223874681759_

#include "dbg.hh"

#include <string_view>
#include <tuple>
#include <type_traits>

namespace dbg {
namespace detail {
template <typename T, typename... Ts>
concept braces_constructible = requires(Ts... xs) {
  T{xs...};
};

// Use this to disable the copy constructor in the one argument case
template <typename T>
struct any_type_except {
  template <typename U>
  requires(!std::is_same_v<T, U>) constexpr operator U(); // non explicit
};

struct any_type {
  template <class T>
  constexpr operator T(); // non explicit
};

template <class T>
auto to_tuple(T&& object) noexcept {
  using type = std::decay_t<T>;

  static_assert(std::is_class_v<type> && std::is_aggregate_v<type>,
                "show::to_tuple can only be used with plain structs");

  // Generated by scripts/to_tuple.py

  if constexpr (braces_constructible<
                    type, any_type, any_type, any_type, any_type, any_type,
                    any_type, any_type, any_type, any_type, any_type, any_type,
                    any_type, any_type, any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,
           _16] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,
                    _15, _16);
  }
  else if constexpr (braces_constructible<
                         type, any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15] =
        object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,
                    _15);
  }
  else if constexpr (braces_constructible<
                         type, any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14] =
        object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,
                    _14);
  }
  else if constexpr (braces_constructible<
                         type, any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11);
  }
  else if constexpr (braces_constructible<
                         type, any_type, any_type, any_type, any_type, any_type,
                         any_type, any_type, any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8, _9] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8, _9);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7, _8] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7, _8);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type, any_type,
                                          any_type>) {
    auto& [_1, _2, _3, _4, _5, _6, _7] = object;
    return std::tie(_1, _2, _3, _4, _5, _6, _7);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5, _6] = object;
    return std::tie(_1, _2, _3, _4, _5, _6);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type, any_type>) {
    auto& [_1, _2, _3, _4, _5] = object;
    return std::tie(_1, _2, _3, _4, _5);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type,
                                          any_type>) {
    auto& [_1, _2, _3, _4] = object;
    return std::tie(_1, _2, _3, _4);
  }
  else if constexpr (braces_constructible<type, any_type, any_type, any_type>) {
    auto& [_1, _2, _3] = object;
    return std::tie(_1, _2, _3);
  }
  else if constexpr (braces_constructible<type, any_type, any_type>) {
    auto& [_1, _2] = object;
    return std::tie(_1, _2);
  }
  else if constexpr (braces_constructible<type, any_type_except<type>>) {
    auto& [_1] = object;
    return std::tie(_1);
  }
  else {
    return std::make_tuple();
  }
}

template <typename T>
constexpr std::string_view typename_test_signature() {
  return __PRETTY_FUNCTION__;
}
constexpr std::pair<std::size_t, std::size_t> typename_excess_prefix_suffix() {
  const auto s = typename_test_signature<double>();
  const auto i = s.find("double");
  const auto l = sizeof("double") - 1;
  return {i, s.size() - i - l};
}
template <typename T>
constexpr std::string_view typename_to_string() {
  const auto [prefix, suffix] = typename_excess_prefix_suffix();
  std::string_view s          = typename_test_signature<T>();
  s.remove_suffix(suffix);
  s.remove_prefix(prefix);
  return s;
}

template <typename T>
concept struct_ =
    std::is_class<T>::value&& std::is_aggregate<T>::value && !range<T>;

} // namespace detail
template <typename T>
requires detail::struct_<T> struct printer<T> {
  static void print(std::ostream& os, const T& x) noexcept {
    auto t = detail::to_tuple(x);
    os << detail::typename_to_string<T>() << '{';
    std::apply(
        [&os](const auto&... xs) mutable noexcept {
          detail::pack_print(os, xs...);
        },
        t);
    os << '}';
  }
};
} // namespace dbg

#endif // DEBUG2_DBG_STRUCT_HH_1587457223874681759_
