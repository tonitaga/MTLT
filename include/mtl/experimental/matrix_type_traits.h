#ifndef MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_
#define MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_

#include <atomic>
#include <ostream>
#include <type_traits>

#if __cplusplus > 201703L
#include <concepts>
#endif // __cplusplus > 201703L

namespace mtl::experimental {

template <typename T>
struct is_atomic : std::false_type {};

template <typename T>
struct is_atomic<std::atomic<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_atomic_v = is_atomic<T>::value;

#if __cplusplus > 201703L

template <typename T>
concept atomic = is_atomic_v<T>;

#endif // __cplusplus > 201703L

namespace detail {

template <typename T, typename ValueType = typename T::value_type>
struct is_fundamental_atomic {
  static constexpr bool value =
	  std::is_fundamental<ValueType>::value && is_atomic<T>::value;
};

} // namespace detail end

template <typename T>
struct is_fundamental_atomic : detail::is_fundamental_atomic<T> {};

template <typename T>
inline constexpr bool is_fundamental_atomic_v = is_fundamental_atomic<T>::value;

#if __cplusplus > 201703L

template <typename T>
concept fundamental = std::is_fundamental_v<T>;

template <typename T>
concept fundamental_atomic = is_fundamental_atomic_v<T>;

template <typename T>
concept fundamental_or_fundamental_atomic = fundamental<T> || fundamental_atomic<T>;

#endif // __cplusplus > 201703L

template <std::size_t Rows, std::size_t Cols>
struct is_non_zero_dimension : std::false_type {};

template <>
struct is_non_zero_dimension<0, 0> : std::true_type {};

template <std::size_t Rows, std::size_t Cols>
inline constexpr bool is_non_zero_dimension_v = is_non_zero_dimension<Rows, Cols>::value;

#if __cplusplus > 201703L

template <std::size_t Rows, std::size_t Cols>
concept non_zero_dimension = is_non_zero_dimension_v<Rows, Cols>;

#endif // __cplusplus > 201703L

template <typename T>
struct is_printable {
  template<typename U>
  static auto printable_test(const U& u) -> decltype(u.print(), true) {};

  static int printable_test(...) { return 0; };

  static constexpr bool value = (sizeof(printable_test(T{})) == 1);
};

} // namespace mtl::experimental end

#endif //MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_
