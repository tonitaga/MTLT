/*
 *        Copyright 2023, School21 Student Library
 *        All rights reserved
 *
 *        Author:   Gubaydullin Nurislam aka tonitaga
 *        Email:    gubaydullin.nurislam@gmail.com
 *        Telegram: @tonitaga
 *
 *        The Template Matrix Library for fundamental types
 *        contains most of the operations on matrices.
 *
 *        The Template Matrix Library is written in STL style
 *        and supports STL Algorithms Library
 *
 *        The Template Matrix library is written in the C++20 standard
 *        Supports C++11 C++14 C++17 C++20 C++23 versions
 *
*/

#ifndef MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_
#define MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_

#include <atomic>
#include <ostream>
#include <type_traits>

#include <mtl/experimental/matrix_config.h>

#if __cplusplus > 201703L
#include <concepts>
#endif // __cplusplus > 201703L

namespace mtl::experimental {

template<typename T>
struct is_atomic : std::false_type {};

template<typename T>
struct is_atomic<std::atomic<T>> : std::true_type {};

#if __cplusplus >= 201402L
template<typename T>
MATRIX_CXX17_INLINE constexpr bool is_atomic_v = is_atomic<T>::value;
#endif // __cplusplus >= 201402L

#if __cplusplus > 201703L

template <typename T>
concept atomic = is_atomic_v<T>;

#endif // __cplusplus > 201703L

namespace detail {

template<typename T, typename ValueType = typename T::value_type>
struct is_fundamental_atomic {
  static constexpr bool value =
	  std::is_fundamental<ValueType>::value && is_atomic<T>::value;
};

} // namespace detail end

template<typename T>
struct is_fundamental_atomic : detail::is_fundamental_atomic<T> {};

#if __cplusplus >= 201402L
template<typename T>
MATRIX_CXX17_INLINE constexpr bool is_fundamental_atomic_v = is_fundamental_atomic<T>::value;
#endif // __cplusplus >= 201402L


#if __cplusplus > 201703L

template <typename T>
concept fundamental = std::is_fundamental_v<T>;

template <typename T>
concept fundamental_atomic = is_fundamental_atomic_v<T>;

template <typename T>
concept fundamental_or_fundamental_atomic = fundamental<T> || fundamental_atomic<T>;

#endif // __cplusplus > 201703L

template<std::size_t Rows, std::size_t Cols>
struct is_non_zero_dimension : std::true_type {};

template<>
struct is_non_zero_dimension<0, 0> : std::false_type {};

#if __cplusplus >= 201402L
template<std::size_t Rows, std::size_t Cols>
MATRIX_CXX17_INLINE constexpr bool is_non_zero_dimension_v = is_non_zero_dimension<Rows, Cols>::value;
#endif // __cplusplus >= 201402L

#if __cplusplus > 201703L

template <std::size_t Rows, std::size_t Cols>
concept non_zero_dimension = is_non_zero_dimension_v<Rows, Cols>;

#endif // __cplusplus > 201703L

template<typename T>
struct is_printable {
private:
  template<typename U>
  static auto printable_test(const U &u) -> decltype(u.print(), true) {};

  struct non_printable_type {};
  static non_printable_type printable_test(...) { return {}; };

  using result_type = decltype(printable_test(std::declval<T>()));

public:
  static constexpr bool value = !std::is_same<result_type, non_printable_type>::value;
};

#if __cplusplus >= 201402L
template<typename T>
MATRIX_CXX17_INLINE constexpr bool is_printable_v = is_printable<T>::value;
#endif // __cplusplus >= 201402L

template<typename Stream, typename T>
struct is_streamable {
private:
  template<typename S, typename U>
  static auto streamable_test(S &&s, U &&u) -> decltype(std::forward<S>(s) << std::forward<U>(u)) {};

  struct non_streamable_type {};
  static non_streamable_type streamable_test(...) { return {}; };

  using result_type = decltype(streamable_test(std::declval<Stream>(), std::declval<T>()));

public:
  static constexpr bool value =
	  !std::is_same<result_type, non_streamable_type>::value;
};

#if __cplusplus >= 201402L
template<typename Stream, typename T>
MATRIX_CXX17_INLINE constexpr bool is_streamable_v = is_streamable<Stream, T>::value;
#endif // __cplusplus >= 201402L

#if __cplusplus > 201703L

template <typename T>
concept printable = is_printable_v<T>;

template <typename T>
concept streamable = is_streamable_v<std::ostream, T> || is_streamable_v<std::stringstream, T> || is_streamable_v<std::ofstream, T>;

template <typename T>
concept printable_or_streamable = printable<T> || streamable<T>;

#endif // __cplusplus > 201703L

} // namespace mtl::experimental end

#endif //MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_
