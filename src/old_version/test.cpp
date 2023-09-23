#include <gtest/gtest.h>

#include "matrix_oop.h"

/*
    Информация о классе:

    Стандартный конструктор без входных параметров создает матрицу 3 на 3 в
   matrix также записывает обратную матрицу данной в i_matrix, также с матрицей
    алгебраических дополнений и записывает в alg_matrix.

    Конструктор с одним входным параметром status
      При status = 0 матрица из стандартного конструктора (matrix)
    обрезается с сохранением значений до размера 2 на 2
      При status = 1 matrix будет иметь размер 3 на 3 с нулевыми значениями
      При status = 2 matrix будет иметь размер 4 на 4 с другими значениями
      При status = 3 в matrix будет лежать матрица 3 на 3 но ее значения будут
    значениями квадрата матрицы (matrix) из стандартного конструктора
      При status = 4 в matrix будет лежать матрица 3 на 3 но ее значения будут
    значениями матрица (matrix) умноженной на 2 из стандартного конструктора
      При status = 5 в matrix будет лежать матрица 2 на 3 и будет записан ее
    трансонированный вариант в t_matrix

    Важно! Там где НЕ упомянуто что значения i_matrix, t_matrix и
    alg_matrix НАЙДЕНЫ их НЕ ИСПОЛЬЗОВАТЬ! Они будут иметь нулевые значения!
*/
class TestMatrix {
 public:
  TestMatrix() {
    matrix(0, 0) = 7, matrix(0, 1) = 8, matrix(0, 2) = 3;
    matrix(1, 0) = 5, matrix(1, 1) = 9, matrix(1, 2) = 1;
    matrix(2, 0) = 9, matrix(2, 1) = 4, matrix(2, 2) = 2;

    i_matrix(0, 0) = -0.150538, i_matrix(0, 1) = 0.0430108;
    i_matrix(0, 2) = 0.204301, i_matrix(1, 0) = 0.0107527;
    i_matrix(1, 1) = 0.139785, i_matrix(1, 2) = -0.0860215;
    i_matrix(2, 0) = 0.655914, i_matrix(2, 1) = -0.473118;
    i_matrix(2, 2) = -0.247312;

    alg_matrix(0, 0) = 14, alg_matrix(0, 1) = -1, alg_matrix(0, 2) = -61;
    alg_matrix(1, 0) = -4, alg_matrix(1, 1) = -13, alg_matrix(1, 2) = 44;
    alg_matrix(2, 0) = -19, alg_matrix(2, 1) = 8, alg_matrix(2, 2) = 23;
  }
  TestMatrix(int status) {
    if (status == 0) {
      matrix.SetCol(2);
      matrix.SetRow(2);
      matrix(0, 0) = 7, matrix(0, 1) = 8;
      matrix(1, 0) = 5, matrix(1, 1) = 9;
    }
    if (status == 1) {
    }
    if (status == 2) {
      matrix.SetRow(4);
      matrix.SetCol(4);
      matrix(0, 0) = 1.2, matrix(1, 0) = 10.2, matrix(2, 0) = 5.8,
                matrix(3, 0) = 2.6, matrix(0, 1) = 4.8, matrix(1, 1) = -6.7;
      matrix(2, 1) = 3.45, matrix(3, 1) = -8.9, matrix(0, 2) = -3.2;
      matrix(1, 2) = 1.9, matrix(2, 2) = -7.8, matrix(3, 2) = 2.2;
      matrix(0, 3) = 9.08, matrix(1, 3) = 9.1, matrix(2, 3) = 0.34,
                matrix(3, 3) = -1.5;
    }
    if (status == 3) {
      matrix(0, 0) = 116, matrix(0, 1) = 140, matrix(0, 2) = 35;
      matrix(1, 0) = 89, matrix(1, 1) = 125, matrix(1, 2) = 26;
      matrix(2, 0) = 101, matrix(2, 1) = 116, matrix(2, 2) = 35;
    }
    if (status == 4) {
      matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
      matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
      matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;
    }
    if (status == 5) {
      matrix.SetRow(2);
      matrix(0, 0) = 0, matrix(0, 1) = 1, matrix(0, 2) = 2;
      matrix(1, 0) = 3, matrix(1, 1) = 4, matrix(1, 2) = 5;

      t_matrix.SetCol(2);
      t_matrix.SetRow(3);
      t_matrix(0, 0) = 0, t_matrix(0, 1) = 3;
      t_matrix(1, 0) = 1, t_matrix(1, 1) = 4;
      t_matrix(2, 0) = 2, t_matrix(2, 1) = 5;
    }
  }
  Matrix matrix;
  Matrix t_matrix;
  Matrix i_matrix;
  Matrix alg_matrix;
};

TEST(EqMatrixTest, HanglesInitedEqualMatrices) {
  TestMatrix A, B;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(EqMatrixTest, HanglesInitedUnEqualMatrices) {
  TestMatrix A, B;
  B.matrix(0, 0) = A.matrix(0, 0) - 1;
  ASSERT_EQ(false, A.matrix.EqMatrix(B.matrix));
}

TEST(SumMatrixTest, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(4);
  A.matrix.SumMatrix(A.matrix);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(SubMatrixTest, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(1);
  A.matrix.SubMatrix(A.matrix);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(MulMatrixTest, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(3);
  A.matrix.MulMatrix(A.matrix);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(MulNumberTest, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(4);
  A.matrix.MulNumber(2);
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(TransposeTest, HanglesInitedMatrices) {
  TestMatrix A(5);
  Matrix B = A.matrix.Transpose();
  ASSERT_EQ(true, B.EqMatrix(A.t_matrix));
}

TEST(CalcComplementsTest, HanglesInitedMatrices) {
  TestMatrix A;
  Matrix B = A.matrix.CalcComplements();
  ASSERT_EQ(true, B.EqMatrix(A.alg_matrix));
}

TEST(DeterminantTest, HanglesInitedMatrices3x3) {
  TestMatrix A(3);
  double determinant = A.matrix.Determinant();
  ASSERT_DOUBLE_EQ(determinant, 8649.0);
}

TEST(MoveConstructor, HanglesInitedMatrices) {
  Matrix A;
  A(0, 0) = 7;
  Matrix B(std::move(A));
  ASSERT_EQ(true, B(0, 0) == 7);
}

TEST(DeterminantTest, HanglesInitedMatrices4x4) {
  TestMatrix A(2);
  double determinant = A.matrix.Determinant();
  ASSERT_DOUBLE_EQ(determinant, 3976.58848);
}

TEST(InverseMatrixTest, HanglesInitedMatrices3x3) {
  TestMatrix A;
  Matrix C = A.matrix.InverseMatrix();
  for (int i = 0; i < C.GetRow(); i++) {
    for (int j = 0; j < C.GetCol(); j++) {
      std::cout << C(i, j) << "\t";
    }
    std::cout << std::endl;
  }
  ASSERT_EQ(true, C.EqMatrix(A.i_matrix));
}

TEST(OperatorEqual, HanglesInitedMatrices) {
  TestMatrix A, B;
  bool status = false;
  if (A.matrix == B.matrix) {
    status = true;
  }
  ASSERT_EQ(true, status);
}

TEST(OpetatorCopy, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(1);
  B.matrix = A.matrix;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorSum, HanglesInitedMatrices) {
  TestMatrix A, B;
  A.matrix += B.matrix;
  B.matrix *= 2;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorSub, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(1);
  A.matrix -= A.matrix;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorPlus, HanglesInitedMatrices) {
  TestMatrix A, B;
  A.matrix = A.matrix + A.matrix;
  B.matrix *= 2;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorMinus, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(1);
  A.matrix = A.matrix - A.matrix;
  ASSERT_EQ(true, B.matrix.EqMatrix(A.matrix));
}

TEST(OpetatorMulMatrices, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(3);
  A.matrix *= A.matrix;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(OpetatorStar, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(3);
  A.matrix = A.matrix * A.matrix;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(OperatorStar2, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(4);
  A.matrix = A.matrix * 2;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(OpetatorMulNum, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(4);
  A.matrix *= 2;
  ASSERT_EQ(true, A.matrix.EqMatrix(B.matrix));
}

TEST(SetColRow, HanglesInitedMatrices) {
  TestMatrix A;
  TestMatrix B(0);
  A.matrix.SetCol(2);
  A.matrix.SetRow(2);
  ASSERT_EQ(true, A.matrix == B.matrix);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
