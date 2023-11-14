#include <gtest/gtest.h>

#include <matrix/row_matrix.h>
#include <matrix/static_row_matrix.h>

using namespace mtl;

TEST(RowMatrix, constructor_rows) {
  row_matrix<int> matrix(10, 2);

  ASSERT_EQ(matrix.rows(), 10);
  ASSERT_EQ(matrix.cols(), 1);
  ASSERT_EQ(matrix[2], 2);
}

TEST(RowMatrix, constructor_vector) {
  std::vector<int> vector {1, 2, 3, 4, 5};
  row_matrix<int> matrix(5, vector);

  ASSERT_EQ(matrix.rows(), 5);
  ASSERT_EQ(matrix[0], 1);
}

TEST(RowMatrix, constructor_matrix) {
  matrix<int> matrix(5, 1, 2);
  row_matrix<int> row_matrix(5, matrix);

  ASSERT_EQ(row_matrix.rows(), 5);
  ASSERT_EQ(row_matrix[0], 2);
}

TEST(StaticRowMatrix, constructor_rows) {
  static_row_matrix<int, 10> matrix(2);

  ASSERT_EQ(matrix.rows(), 10);
  ASSERT_EQ(matrix.cols(), 1);
  ASSERT_EQ(matrix[2], 2);
}

TEST(StaticRowMatrix, constructor_vector) {
  std::array<int, 5> array {1, 2, 3, 4, 5};
  static_row_matrix<int, 5> matrix(array);

  ASSERT_EQ(matrix.rows(), 5);
  ASSERT_EQ(matrix[0], 1);
}

TEST(StaticRowMatrix, constructor_matrix) {
  static_matrix<int, 5, 1> matrix(2);
  static_row_matrix<int, 5> row_matrix(matrix);

  ASSERT_EQ(row_matrix.rows(), 5);
  ASSERT_EQ(row_matrix[0], 2);
}