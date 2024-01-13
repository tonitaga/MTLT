#include <mtl/experimental/type_traits.h>

#include <gtest/gtest.h>

using namespace mtl;

TEST(TYPE_TRAITS, STD_ATOMIC) {
  constexpr bool is_atomic1 = experimental::is_atomic<std::atomic<std::array<int, 10>>>::value;
  constexpr bool is_atomic2 = experimental::is_atomic_v<std::atomic<std::array<int, 10>>>;

  ASSERT_TRUE(is_atomic1 == true);
  ASSERT_TRUE(is_atomic2 == true);
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
  constexpr bool is_atomic1 = experimental::is_atomic<AnotherAtomic<std::array<int, 10>>>::value;
  constexpr bool is_atomic2 = experimental::is_atomic_v<AnotherAtomic<std::array<int, 10>>>;

  ASSERT_TRUE(is_atomic1 == true);
  ASSERT_TRUE(is_atomic2 == true);
}

TEST(TYPE_TRAITS, NOT_ATOMIC) {
  constexpr bool is_atomic1 = experimental::is_atomic<int>::value;
  constexpr bool is_atomic2 = experimental::is_atomic_v<int>;

  ASSERT_TRUE(is_atomic1 == false);
  ASSERT_TRUE(is_atomic2 == false);
}

TEST(TYPE_TRAITS, FUNDAMENTAL_STD_ATOMIC) {
  constexpr bool is_atomic1 = experimental::is_fundamental_atomic<std::atomic<std::array<int, 10>>>::value;
  constexpr bool is_atomic2 = experimental::is_fundamental_atomic_v<std::atomic<std::array<int, 10>>>;

  ASSERT_TRUE(is_atomic1 == false);
  ASSERT_TRUE(is_atomic2 == false);

  constexpr bool is_atomic3 = experimental::is_fundamental_atomic<std::atomic<int>>::value;
  constexpr bool is_atomic4 = experimental::is_fundamental_atomic_v<std::atomic<int>>;

  ASSERT_TRUE(is_atomic3 == true);
  ASSERT_TRUE(is_atomic4 == true);
}

TEST(TYPE_TRAITS, FUNDAMENTAL_ANOTHER_ATOMIC) {
  constexpr bool is_atomic1 = experimental::is_fundamental_atomic<AnotherAtomic<std::array<int, 10>>>::value;
  constexpr bool is_atomic2 = experimental::is_fundamental_atomic_v<AnotherAtomic<std::array<int, 10>>>;

  ASSERT_TRUE(is_atomic1 == false);
  ASSERT_TRUE(is_atomic2 == false);

  constexpr bool is_atomic3 = experimental::is_fundamental_atomic<AnotherAtomic<int>>::value;
  constexpr bool is_atomic4 = experimental::is_fundamental_atomic_v<AnotherAtomic<int>>;

  ASSERT_TRUE(is_atomic3 == true);
  ASSERT_TRUE(is_atomic4 == true);
}