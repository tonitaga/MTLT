#include <gtest/gtest.h>

#include <matrix/col_matrix.h>
#include <matrix/static_col_matrix.h>

using namespace mtl;

TEST(ColMatrix, constructor_cols) {
  col_matrix<int> matrix(10, 2);

  ASSERT_EQ(matrix.cols(), 10);
  ASSERT_EQ(matrix.rows(), 1);
  ASSERT_EQ(matrix[2], 2);
}

TEST(ColMatrix, constructor_vector) {
  std::vector<int> vector {1, 2, 3, 4, 5};
  col_matrix<int> matrix(5, vector);

  ASSERT_EQ(matrix.cols(), 5);
  ASSERT_EQ(matrix[0], 1);
}

TEST(ColMatrix, constructor_matrix) {
  matrix<int> matrix(1, 5, 2);
  col_matrix<int> col_matrix(5, matrix);

  ASSERT_EQ(col_matrix.cols(), 5);
  ASSERT_EQ(col_matrix[0], 2);
}

TEST(StaticColMatrix, constructor_cols) {
  static_col_matrix<int, 10> matrix(2);

  ASSERT_EQ(matrix.cols(), 10);
  ASSERT_EQ(matrix.rows(), 1);
  ASSERT_EQ(matrix[2], 2);
}

TEST(StaticColMatrix, constructor_array) {
  std::array<int, 5> array {1, 2, 3, 4, 5};
  static_col_matrix<int, 5> matrix(array);

  ASSERT_EQ(matrix.cols(), 5);
  ASSERT_EQ(matrix[0], 1);
}

TEST(StaticColMatrix, constructor_matrix) {
  static_matrix<int, 5, 1> matrix(2);
  static_col_matrix<int, 5> col_matrix(matrix);

  ASSERT_EQ(col_matrix.cols(), 5);
  ASSERT_EQ(col_matrix[0], 2);
}