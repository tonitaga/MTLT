#include <mtl/experimental/matrix_type_traits.h>

#include <gtest/gtest.h>

using namespace mtl;

TEST(TYPE_TRAITS, STD_ATOMIC) {
  constexpr bool is_atomic1 = experimental::is_atomic<std::atomic<int>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = experimental::is_atomic_v<std::atomic<int>>;
  ASSERT_TRUE(is_atomic2 == true);
#endif

  ASSERT_TRUE(is_atomic1 == true);
}

template <typename T>
class AnotherAtomic {
public:
  using value_type = T;
};

namespace mtl::experimental {

template <typename T>
struct is_atomic<AnotherAtomic<T>> : std::true_type {};

}

TEST(TYPE_TRAITS, ANOTHER_ATOMIC) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = experimental::is_atomic<AnotherAtomic<int *>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = experimental::is_atomic_v<std::atomic<int *>>;
  ASSERT_TRUE(is_atomic2 == true);
#endif

  ASSERT_TRUE(is_atomic1 == true);
}

TEST(TYPE_TRAITS, NOT_ATOMIC) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = experimental::is_atomic<int>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = experimental::is_atomic_v<int>;
  ASSERT_TRUE(is_atomic2 == false);
#endif

  ASSERT_TRUE(is_atomic1 == false);
}

TEST(TYPE_TRAITS, FUNDAMENTAL_STD_ATOMIC) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = experimental::is_fundamental_atomic<std::atomic<int *>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = experimental::is_fundamental_atomic_v<std::atomic<int *>>;
  ASSERT_TRUE(is_atomic2 == false);
#endif

  ASSERT_TRUE(is_atomic1 == false);


  MATRIX_CXX17_UNUSED constexpr bool is_atomic3 = experimental::is_fundamental_atomic<std::atomic<int>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic4 = experimental::is_fundamental_atomic_v<std::atomic<int>>;
  ASSERT_TRUE(is_atomic4 == true);
#endif

  ASSERT_TRUE(is_atomic3 == true);
}

TEST(TYPE_TRAITS, FUNDAMENTAL_ANOTHER_ATOMIC) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = experimental::is_fundamental_atomic<AnotherAtomic<int *>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = experimental::is_fundamental_atomic_v<AnotherAtomic<int *>>;
  ASSERT_TRUE(is_atomic2 == false);
#endif

  ASSERT_TRUE(is_atomic1 == false);

  MATRIX_CXX17_UNUSED constexpr bool is_atomic3 = experimental::is_fundamental_atomic<AnotherAtomic<int>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic4 = experimental::is_fundamental_atomic_v<AnotherAtomic<int>>;
  ASSERT_TRUE(is_atomic4 == true);
#endif

  ASSERT_TRUE(is_atomic3 == true);
}