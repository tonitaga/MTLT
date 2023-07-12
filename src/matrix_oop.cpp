#include "matrix_oop.h"

/*===============================================================/
/                                                                /
/                        MATRIX++ PROJECT                        /
/                          BY TONITAGA                           /
/                                                                /
/===============================================================*/

/**
 * @brief Стандартный конструктор без входных параметров.
 * Создает матрицу 3 на 3 и заполняет её нулями
 */
Matrix::Matrix() : rows_(3), cols_(3) { Create(); }

/**
 * @brief Конструктор с двумя входными параметрами.
 * Создает матрицу со сторонами rows на cols
 * @param rows количество строк в матрице
 * @param cols количество столбцов в матрице
 */
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::bad_array_new_length();
  }
  Create();
}

/**
 * @brief Конструктор копирования.
 * Копирует все данные матрицы other в текущую матрицу
 * @param other матрица с которой будут браться данные
 */
Matrix::Matrix(const Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  Create();
  Copy(other);
}

/**
 * @brief Конструктор переноса.
 * Переопределяет указатель текущей матрицы на данные матрицы other.
 * Приводит матрицу other к стандартному после этого переопределения состоянию
 * @param other матрица с которой будет совершен перенос
 */
Matrix::Matrix(Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

/**
 * @brief Деструктор класса Matrix
 *
 */
Matrix::~Matrix() {
  if (isCreated) {
    Remove();
  }
}

/**
 * @brief Функция сравнивает текущую матрицу и матрицу other
 * между собой
 * @param other матрица для сравнения с текущей
 * @return true - если матрицы равны, false - если не равны
 */
bool Matrix::EqMatrix(const Matrix &other) {
  bool equal = true;
  if (this == &other) {
    return true;
  }
  if (rows_ != other.GetRow() || cols_ != other.GetCol()) {
    return false;
  } else {
    bool check = true;
    for (int row = 0; row < rows_ && check; row++) {
      for (int col = 0; col < cols_; col++) {
        if (fabs(matrix_[row][col] - other(row, col)) >= 1e-6) {
          equal = false;
          check = false;
        }
      }
    }
  }
  return equal;
}

/**
 * @brief Функция суммирует текущую матрицу и матрицу other.
 * Результат сложения будет записан в текущую матрицу
 * @param other матрица для сложения с текущей
 */
void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.GetRow() || cols_ != other.GetCol()) {
    throw std::out_of_range("SumMatrix: Sizes of matrices are not the same!");
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] += other(row, col);
    }
  }
}

/**
 * @brief Функция находит разницу текущей матрицы и матрицы other.
 * Результат разницы будет записан в текущую матрицу
 * @param other матрица для вычитания с текущей
 */
void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.GetRow() || cols_ != other.GetCol()) {
    throw std::out_of_range("SubMatrix: Sizes of matrices are not the same!");
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] -= other(row, col);
    }
  }
}

/**
 * @brief Функция умножает текущую матрицу на 'num'.
 * Результат умножения будет записан в текущую матрицу
 * @param num число на которое будет умножена матрица
 */
void Matrix::MulNumber(const double num) {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] *= num;
    }
  }
}

/**
 * @brief Функция умножает текущую матрицу на матрицу other.
 * Результат умножения будет записан в текущую матрицу
 * @param other матрица для умножения с текущей
 */
void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.GetRow()) {
    throw std::out_of_range(
        "Columns of first matrix is not equal"
        "to rows of second matrix!");
  }
  Matrix result(this->rows_, other.GetCol());
  for (int i = 0; i < result.GetRow(); i++) {
    for (int j = 0; j < result.GetCol(); j++) {
      for (int k = 0; k < other.GetRow(); k++)
        result(i, j) += matrix_[i][k] * other(k, j);
    }
  }
  this->SetCol(other.GetCol());
  this->Copy(result);
}

/**
 * @brief Функция транспонирует текущую матрицу
 * @return Транспонированную матрицу текущей матрицы
 */
Matrix Matrix::Transpose() {
  Matrix transpose_this(cols_, rows_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      transpose_this(col, row) = matrix_[row][col];
    }
  }
  return transpose_this;
}

/**
 * @brief Функция считает матрицу алгебраических дополнений текущей матрицы
 * @return Матрицу алгебраических дополнений
 */
Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("CalcComplements: Matrix is not a square!");
  }
  Matrix CalcComplementMatrix(rows_, cols_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      CalcComplementMatrix(row, col) = this->CalculateMinorItem(row, col);
    }
  }
  CalcComplementMatrix.MakeAlgebraicAddition();
  return CalcComplementMatrix;
}

/**
 * @brief Функция считает определитель текущей матрицы
 * @return определитель матрицы в типе double
 */
double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("Determinant: Matrix is not a square!");
  }
  double determinant = GetDeterminant(*this);
  return determinant;
}

/**
 * @brief Функция считает обратную матрицу текущей матрицы
 * @return Обратную матрицу текущей матрицы
 */
Matrix Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (fabs(determinant) <= 1e-6) {
    throw std::logic_error("InverseMatrix: Matrix determinant is zero!");
  }
  Matrix InverseMatrix((this->CalcComplements()).Transpose());
  InverseMatrix *= 1.0 / determinant;
  return InverseMatrix;
}

/**
 * @brief Функция изменяет количество столбцов текущей матрицы.
 * Все значения сохраняются. Если количетсво столбцов будет больше
 * то новые столбцы будут заполнены нулями. Если количество столбцов будет
 * меньше то текущая матрица будет просто обрезана
 * @param cols новое количество столбцов в текущей матрице
 */
void Matrix::SetCol(int cols) {
  if (cols <= 0) {
    throw std::out_of_range("setCol: 'cols' element less or equal zero!");
  }
  Matrix tmp_this(*this);
  Remove();
  cols_ = cols;
  rows_ = tmp_this.GetRow();
  Create();
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (col < tmp_this.GetCol()) {
        matrix_[row][col] = tmp_this(row, col);
      }
    }
  }
}

/**
 * @brief Функция изменяет количество строк текущей матрицы.
 * Все значения сохраняются. Если количетсво строк будет больше
 * то новые строки будут заполнены нулями. Если количество строк будет меньше
 * то текущая матрица будет просто обрезана
 * @param rows новое количество строк в текущей матрице
 */
void Matrix::SetRow(int rows) {
  if (rows <= 0) {
    throw std::out_of_range("setRow: 'rows' element less or equal zero!");
  }
  Matrix tmp_this(*this);
  Remove();
  rows_ = rows;
  cols_ = tmp_this.GetCol();
  Create();
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (row < tmp_this.GetRow()) {
        matrix_[row][col] = tmp_this(row, col);
      }
    }
  }
}
