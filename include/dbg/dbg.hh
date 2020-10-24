#ifndef DBG_HH_1586859470462304132_
#define DBG_HH_1586859470462304132_

#include <iostream>
#include <optional>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <variant>

#if defined(__cpp_concepts) && __has_include(<concepts>)
#  include <concepts>
namespace dbg::detail {
using std::convertible_to;
} // namespace dbg::detail
#elif defined(__cpp_concepts)
namespace dbg::detail {
// https://en.cppreference.com/w/cpp/concepts/convertible_to
template <typename From, typename To>
concept convertible_to = std::is_convertible_v<From, To>&& requires(
    std::add_rvalue_reference_t<From> (&f)()) {
  static_cast<To>(f());
};
} // namespace dbg::detail
#else
namespace dbg::detail {
template <typename From, typename To>
inline constexpr bool convertible_to = std::is_convertible_v<From, To>;
} // namespace dbg::detail
#endif

#if defined(__cpp_concepts) && __has_include(<ranges>)
#  include <ranges>
namespace dbg::detail {
using std::ranges::range;
using std::ranges::range_value_t;
} // namespace dbg::detail
#elif defined(__cpp_concepts)
#  include <iterator>
namespace dbg::detail {
using std::begin;
using std::end;
template <typename T>
concept range = requires(T& x) {
  begin(x);
  end(x);
};
template <typename T>
using range_value_t = typename std::iterator_traits<decltype(
    begin(std::declval<T&>()))>::value_type;
} // namespace dbg::detail
#else
#  include <iterator>
namespace dbg::detail {
using std::begin;
using std::end;
template <typename T, typename = void>
struct is_range : std::false_type {};

template <typename T>
struct is_range<T, std::void_t<decltype(begin(std::declval<T&>())),
                               decltype(end(std::declval<T&>()))>>
    : std::true_type {};

template <typename T>
inline constexpr bool range = is_range<T>::value;

template <typename T>
using range_value_t = typename std::iterator_traits<decltype(
    begin(std::declval<T&>()))>::value_type;
} // namespace dbg::detail
#endif

namespace dbg {
namespace detail {
template <typename>
inline constexpr bool dependent_false = false;
}
#ifdef __cpp_concepts
template <typename T>
#else
template <typename T, typename = void>
#endif
struct printer {
  static_assert(detail::dependent_false<T>,
                "Cannot print user defined types. Please provide a "
                "specialization for struct dbg::printer<T>.");
  static void print(std::ostream& os, const T& x) noexcept;
};

namespace detail {
#ifdef __cpp_concepts
template <typename T>
concept output_streamable = requires(std::ostream& os, const T& x) {
  os << x;
};

template <typename T>
concept dereferencable = requires(const T& x) {
  *x;
};

template <typename T>
concept nullable = requires(const T& x) {
  static_cast<bool>(x);
};

template <typename T>
concept pointer_like = dereferencable<T>&& nullable<T>;

#else
template <typename T, typename = void>
struct is_output_streamable : std::false_type {};

template <typename T>
struct is_output_streamable<T,
                            std::void_t<decltype(std::declval<std::ostream&>()
                                                 << std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
inline constexpr bool output_streamable = is_output_streamable<T>::value;

template <typename T, typename = void>
struct is_dereferencable : std::false_type {};

template <typename T>
struct is_dereferencable<T, std::void_t<decltype(*std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
inline constexpr bool dereferencable = is_dereferencable<T>::value;

template <typename T, typename = void>
struct is_nullable : std::false_type {};

template <typename T>
struct is_nullable<
    T, std::void_t<decltype(static_cast<bool>(std::declval<const T&>()))>>
    : std::true_type {};

template <typename T>
inline constexpr bool nullable = is_nullable<T>::value;

template <typename T>
inline constexpr bool pointer_like = dereferencable<T>&& nullable<T>;
#endif
} // namespace detail

#ifdef __cpp_concepts
#  define DBG_STRUCT_REQUIRES(name, type, requirements)                        \
    requires(requirements) struct name<type>
#else
#  define DBG_STRUCT_REQUIRES(name, type, requirements)                        \
    struct name<type, std::enable_if_t<requirements>>
#endif

template <typename T>
DBG_STRUCT_REQUIRES(printer, T,
                    (detail::output_streamable<T>                        //
                     and not detail::convertible_to<T, std::string_view> //
                     and not detail::range<T>                            //
                     and not detail::dereferencable<T>)){
    static void print(std::ostream & os, const T& x) noexcept {os << x;
} // namespace dbg
}
;

template <>
struct printer<bool> {
  static void print(std::ostream& os, bool b) noexcept {
    os << (b ? "true" : "false");
  }
};

template <typename T>
DBG_STRUCT_REQUIRES(printer, T,
                    (detail::range<T> //
                     and not detail::convertible_to<T, std::string_view>)){
    static void print(std::ostream & os, const T& x) noexcept {using std::begin,
                                                               std::end;
using U = detail::range_value_t<T>;

// ranges::filter_view has only non-const begin/end functions
auto it   = begin(const_cast<T&>(x));
auto last = end(const_cast<T&>(x));

os << '[';
if (it != last) {
  while (true) {
    printer<U>::print(os, *it);
    if (++it == last) {
      break;
    }
    os << ", ";
  }
}
os << ']';
}
}
;

template <typename T>
DBG_STRUCT_REQUIRES(printer, T, (detail::convertible_to<T, std::string_view>)){
    static void print(std::ostream & os,
                      std::string_view x) noexcept {os << "\"" << x << "\"";
}
}
;

template <>
struct printer<char> {
  static void print(std::ostream& os, char x) noexcept {
    os << '\'' << x << '\'';
  }
};

template <typename T, typename U>
struct printer<std::pair<T, U>> {
  static void print(std::ostream& os, const std::pair<T, U>& x) noexcept {
    os << '(' << x.first << ", " << x.second << ')';
  }
};

namespace detail {
inline void pack_print([[maybe_unused]] std::ostream& os) {
}
template <typename T, typename... Ts>
void pack_print(std::ostream& os, const T& x, const Ts&... xs) noexcept {
  printer<T>::print(os, x);
  auto comma_and_print = [&os]<typename U>(const U& u) mutable noexcept {
    os << ", ";
    printer<U>::print(os, u);
  };
  (comma_and_print(xs), ...);
}
} // namespace detail

template <typename... Ts>
struct printer<std::tuple<Ts...>> {
  static void print(std::ostream& os, const std::tuple<Ts...>& x) noexcept {
    os << '(';
    std::apply(
        [&os](const auto&... xs) mutable noexcept {
          detail::pack_print(os, xs...);
        },
        x);
    os << ')';
  }
};

template <>
struct printer<std::nullptr_t> {
  static void print(std::ostream& os, std::nullptr_t) noexcept { os << "null"; }
};

template <>
struct printer<std::nullopt_t> {
  static void print(std::ostream& os, std::nullopt_t) noexcept { os << "null"; }
};

template <typename T>
DBG_STRUCT_REQUIRES(printer, T,
                    (detail::dereferencable<T>   //
                     and not detail::nullable<T> //
                     and not detail::range<T>    //
                     and not detail::convertible_to<T, std::string_view>)){
    static void print(std::ostream & os, const T& x) noexcept {
        using U = std::remove_cv_t<std::remove_reference_t<decltype(*x)>>;
printer<U>::print(os, *x);
}
}
;

template <typename T>
DBG_STRUCT_REQUIRES(printer, T,
                    (detail::pointer_like<T>  //
                     and not detail::range<T> //
                     and not detail::convertible_to<T, std::string_view>)){
    static void print(std::ostream & os, const T& x) noexcept {
        using U = std::remove_cv_t<std::remove_reference_t<decltype(*x)>>;
if (x) {
  printer<U>::print(os, *x);
}
else {
  os << "null";
}
}
}
;

template <>
struct printer<void*> {
  static void print(std::ostream& os, void* p) noexcept { os << p; }
};

template <typename... Ts>
struct printer<std::variant<Ts...>> {
  static void print(std::ostream& os, const std::variant<Ts...>& v) noexcept {
    std::visit(
        [&os]<typename T>(const T& x) mutable { printer<T>::print(os, x); }, v);
  }
};

template <typename T>
void print(std::ostream& os, const T& x) noexcept {
  printer<T>::print(os, x);
}

template <typename T>
T&& dbg(const char* file, int line, const char* rep, T&& x) noexcept {
  std::clog << file << '(' << line << "): " << rep << " = ";
  print(std::clog, x);
  std::clog << '\n';
  return std::forward<T>(x);
}
} // namespace dbg

#define DBG(x) dbg::dbg(__FILE__, __LINE__, #x, x)

#endif // DBG_HH_1586859470462304132_
