#ifndef SRC_MATRIX_OOP_H
#define SRC_MATRIX_OOP_H

/*===============================================================/
/                                                                /
/                        MATRIX++ PROJECT                        /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

#include <cmath>
#include <iostream>

class Matrix {
 public:
  /*
      Конструкторы и деструктор класса Matrix
  */

  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);
  ~Matrix();

  /*
      Блок доступа к приватным значениям
      количества строк и столбцов с возможностью
      их изменения
  */

  int GetCol() const { return cols_; }
  int GetRow() const { return rows_; }
  void SetCol(int cols);
  void SetRow(int rows);

  /*
      Блок методов класса Matrix занимающихся
      стандартными оцерациями над матрицами
  */

  bool EqMatrix(const Matrix &other);
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  /*
      Блок операторов класса Matrix занимающиеся
      стандартными операциями над матрицами
  */

  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(double num) const;
  bool operator==(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(double num);
  double &operator()(int row, int col);
  double operator()(int row, int col) const;

 private:
  /*
      Основные приватные поля класса Matrix
  */

  int rows_;
  int cols_;
  double **matrix_;

  /*
      Приватные-support поля класса Matrix
  */

  bool isCreated;

  /*
      Блок приватных-support методов класса Matrix
  */

  void Create();
  void Remove();
  void Copy(const Matrix &other);
  double GetDeterminant(Matrix &other);
  void MakeSmallerOrderMatrix(int row, int col, Matrix &minor);
  double CalculateMinorItem(int row, int col);
  void MakeAlgebraicAddition();
};

#endif  // !SRC_MATRIX_OOP_H
