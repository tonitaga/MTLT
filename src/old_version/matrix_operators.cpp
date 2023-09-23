#include "matrix_oop.h"

/*===============================================================/
/                                                                /
/                        MATRIX++ PROJECT                        /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

Matrix Matrix::operator+(const Matrix &other) {
  Matrix result(*this); /* Coping this matrix to result */
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix &other) {
  Matrix result(*this); /* Coping this matrix to result */
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix &other) {
  Matrix result(*this); /* Coping this matrix to result */
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) const {
  Matrix result(*this); /* Coping this matrix to result */
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix &other) {
  return this->EqMatrix(other);
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (*this == other) {
    return *this;
  }
  Remove(); /* Removed this matrix to create a new one */
  rows_ = other.GetRow(), cols_ = other.GetCol();
  Create();
  Copy(other); /* Coping other matrix to this one */
  return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}

double &Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Row or Col number out of size of matrix!");
  }
  return matrix_[row][col];
}

/* Operator() overload for "const Matrix" */
double Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Row or Col number out of size of matrix!");
  }
  return matrix_[row][col];
}
