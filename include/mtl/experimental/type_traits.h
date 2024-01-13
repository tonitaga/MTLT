#ifndef MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_
#define MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_

#include <atomic>
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
concept atomic = is_atomic<T>::value;

#endif // __cplusplus > 201703L

namespace detail {

template <typename T, typename ValueType = typename T::value_type>
struct is_fundamental_atomic {
  static constexpr bool value =
	  std::is_fundamental<ValueType>::value && is_atomic<T>::value;
};

} // namespace detail end

template <typename T>
struct is_fundamental_atomic {
  static constexpr bool value = detail::is_fundamental_atomic<T>::value;
};

template <typename T>
inline constexpr bool is_fundamental_atomic_v = is_fundamental_atomic<T>::value;

#if __cplusplus > 201703L

template <typename T>
concept fundamental_atomic = is_fundamental_atomic<T>::value;

#endif // __cplusplus > 201703L

} // namespace mtl::experimental end

#endif //MATRIX_TEMPLATE_LIBRARY_EXPERIMENTAL_TYPE_TRAITS_H_
