#include <mtl/matrix_type_traits.h>

#include <gtest/gtest.h>

using namespace mtl;

TEST(FTTypeTraits, StdAtomic) {
  constexpr bool is_atomic1 = is_atomic<std::atomic<int>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = is_atomic_v<std::atomic<int>>;
  ASSERT_TRUE(is_atomic2 == true);
#endif

  ASSERT_TRUE(is_atomic1 == true);
}

template <typename T>
class AnotherAtomic {
public:
  using value_type = T;
};

namespace mtl {

template <typename T>
struct is_atomic<AnotherAtomic<T>> : std::true_type {};

}

TEST(FTTypeTraits, AnotherAtomic) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = is_atomic<AnotherAtomic<int *>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = is_atomic_v<std::atomic<int *>>;
  ASSERT_TRUE(is_atomic2 == true);
#endif

  ASSERT_TRUE(is_atomic1 == true);
}

TEST(FTTypeTraits, NotAtomic) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = is_atomic<int>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = is_atomic_v<int>;
  ASSERT_TRUE(is_atomic2 == false);
#endif

  ASSERT_TRUE(is_atomic1 == false);
}

TEST(FTTypeTraits, FundamentalStdAtomic) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = is_fundamental_atomic<std::atomic<int *>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = is_fundamental_atomic_v<std::atomic<int *>>;
  ASSERT_TRUE(is_atomic2 == false);
#endif

  ASSERT_TRUE(is_atomic1 == false);


  MATRIX_CXX17_UNUSED constexpr bool is_atomic3 = is_fundamental_atomic<std::atomic<int>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic4 = is_fundamental_atomic_v<std::atomic<int>>;
  ASSERT_TRUE(is_atomic4 == true);
#endif

  ASSERT_TRUE(is_atomic3 == true);
}

TEST(FTTypeTraits, FundamentalAnotherAtomic) {
  MATRIX_CXX17_UNUSED constexpr bool is_atomic1 = is_fundamental_atomic<AnotherAtomic<int *>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic2 = is_fundamental_atomic_v<AnotherAtomic<int *>>;
  ASSERT_TRUE(is_atomic2 == false);
#endif

  ASSERT_TRUE(is_atomic1 == false);

  MATRIX_CXX17_UNUSED constexpr bool is_atomic3 = is_fundamental_atomic<AnotherAtomic<int>>::value;

#if __cplusplus >= 201402L
  constexpr bool is_atomic4 = is_fundamental_atomic_v<AnotherAtomic<int>>;
  ASSERT_TRUE(is_atomic4 == true);
#endif

  ASSERT_TRUE(is_atomic3 == true);
}