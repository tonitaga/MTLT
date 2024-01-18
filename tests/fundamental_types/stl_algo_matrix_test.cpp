#include <mtlt/matrix.h>
#include <mtlt/static_matrix.h>

#include <gtest/gtest.h>

using namespace mtlt;

TEST(FTSTLAlgo, MatrixSortLess) {
  matrix<int> m(3, 3, {
	  9, 8, 7,
	  6, 5, 4,
	  3, 2, 1
  });

  matrix<int> correct(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  std::sort(m.begin(), m.end());
  ASSERT_TRUE(m == correct);
}

TEST(FTSTLAlgo, StaticMatrixSortLess) {
  static_matrix<int, 3, 3> m({
								 9, 8, 7,
								 6, 5, 4,
								 3, 2, 1
							 });

  static_matrix<int, 3, 3> correct({
									   1, 2, 3,
									   4, 5, 6,
									   7, 8, 9
								   });

  std::sort(m.begin(), m.end());
  ASSERT_TRUE(m == correct);
}

TEST(FTSTLAlgo, MatrixSortGreater_1) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  matrix<int> correct(3, 3, {
	  9, 8, 7,
	  6, 5, 4,
	  3, 2, 1
  });

  std::sort(m.begin(), m.end(), std::greater<int>{});
  ASSERT_TRUE(m == correct);
}

TEST(FTSTLAlgo, StaticMatrixSortGreater_1) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  static_matrix<int, 3, 3> correct({
									   9, 8, 7,
									   6, 5, 4,
									   3, 2, 1
								   });

  std::sort(m.begin(), m.end(), std::greater<int>{});
  ASSERT_TRUE(m == correct);
}

TEST(FTSTLAlgo, MatrixSortGreater_2) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  matrix<int> correct(3, 3, {
	  9, 8, 7,
	  6, 5, 4,
	  3, 2, 1
  });

  std::sort(m.rbegin(), m.rend());
  ASSERT_TRUE(m == correct);
}

TEST(FTSTLAlgo, StaticMatrixSortGreater_2) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  static_matrix<int, 3, 3> correct({
									   9, 8, 7,
									   6, 5, 4,
									   3, 2, 1
								   });

  std::sort(m.rbegin(), m.rend());
  ASSERT_TRUE(m == correct);
}

TEST(FTSTLAlgo, MatrixFind) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  auto it = std::find(m.begin(), m.end(), 5);
  ASSERT_TRUE(it != m.end());

  it = std::find(m.begin(), m.end(), 10);
  ASSERT_TRUE(it == m.end());
}

TEST(FTSTLAlgo, StaticMatrixFind) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  auto it = std::find(m.begin(), m.end(), 5);
  ASSERT_TRUE(it != m.end());

  it = std::find(m.begin(), m.end(), 10);
  ASSERT_TRUE(it == m.end());
}

TEST(FTSTLAlgo, MatrixFindIf) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  auto it = std::find_if(m.begin(), m.end(), [](int value) {
	return value % 2 == 0;
  });

  ASSERT_TRUE(it != m.end());

  it = std::find_if(m.begin(), m.end(), [](int value) {
	return value % 10 == 0;
  });
  ASSERT_TRUE(it == m.end());
}

TEST(FTSTLAlgo, StaticMatrixFindIf) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  auto it = std::find_if(m.begin(), m.end(), [](int value) {
	return value % 2 == 0;
  });

  ASSERT_TRUE(it != m.end());

  it = std::find_if(m.begin(), m.end(), [](int value) {
	return value % 10 == 0;
  });
  ASSERT_TRUE(it == m.end());
}

TEST(FTSTLAlgo, MatrixCopy) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  matrix<int> copy(3, 3);

  std::copy(m.begin(), m.end(), copy.begin());

  ASSERT_TRUE(copy == m);
}

TEST(FTSTLAlgo, StaticMatrixCopy) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  static_matrix<int, 3, 3> copy;

  std::copy(m.begin(), m.end(), copy.begin());

  ASSERT_TRUE(copy == m);
}

TEST(FTSTLAlgo, MatrixCount) {
  matrix<int> m(3, 3, {
	  1, 1, 1,
	  0, 0, 0,
	  0, 0, 1
  });

  constexpr int count = 5;
  constexpr int target = 0;

  int real_count = std::count(m.begin(), m.end(), target);

  ASSERT_TRUE(real_count == count);
}

TEST(FTSTLAlgo, StaticMatrixCount) {
  static_matrix<int, 3, 3> m({
								 1, 1, 1,
								 0, 0, 0,
								 0, 0, 1
							 });

  constexpr int count = 5;
  constexpr int target = 0;

  int real_count = std::count(m.begin(), m.end(), target);

  ASSERT_TRUE(real_count == count);
}

TEST(FTSTLAlgo, MatrixCountIf) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  auto is_even = [](int value) {
	return value % 2 == 0;
  };

  constexpr int count = 4;

  int real_count = std::count_if(m.begin(), m.end(), is_even);

  ASSERT_TRUE(real_count == count);
}

TEST(FTSTLAlgo, StaticMatrixCountIf) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  auto is_even = [](int value) {
	return value % 2 == 0;
  };

  constexpr int count = 4;

  int real_count = std::count_if(m.begin(), m.end(), is_even);

  ASSERT_TRUE(real_count == count);
}

TEST(FTSTLAlgo, MatrixPartition) {
  matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  auto is_even = [](int value) {
	return value % 2 == 0;
  };

  constexpr int even_count = 4;

  auto even_end = std::partition(m.begin(), m.end(), is_even);

  int count = 0;
  for (auto it = m.begin(); it != even_end; ++it) {
	ASSERT_TRUE(is_even(*it));
	count++;
  }

  ASSERT_TRUE(count == even_count);
}

TEST(FTSTLAlgo, StaticMatrixPartition) {
  static_matrix<int, 3, 3> m({
								 1, 2, 3,
								 4, 5, 6,
								 7, 8, 9
							 });

  auto is_even = [](int value) {
	return value % 2 == 0;
  };

  constexpr int even_count = 4;

  auto even_end = std::partition(m.begin(), m.end(), is_even);

  int count = 0;
  for (auto it = m.begin(); it != even_end; ++it) {
	ASSERT_TRUE(is_even(*it));
	count++;
  }

  ASSERT_TRUE(count == even_count);
}