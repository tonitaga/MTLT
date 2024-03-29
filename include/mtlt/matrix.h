/*
 *        Copyright 2024, School21 (Sberbank) Student Library
 *        All rights reserved
 *
 *        MTLT - Matrix Template Library Tonitaga (STL Like)
 *
 *        Author:   Gubaydullin Nurislam aka tonitaga
 *        Email:    gubaydullin.nurislam@gmail.com
 *        Telegram: @tonitaga
 *
 *        The Template Matrix Library for different types
 *        contains most of the operations on matrices.
 *
 *        The matrix container class is a wrapper over a dynamic array,
 * 		  it allows you to do all basic calculations and operations on matrices
 *
 *        The Template Matrix library is written in the C++20 standard
 *        Supports C++11 C++14 C++17 C++20 C++23 versions. Also
 *        The Library is  written in STL style and supports
 *        STL Algorithms Library.
*/

#ifndef MTLT_MATRIX_H_
#define MTLT_MATRIX_H_

#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <iomanip>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>

#if __cplusplus > 201703L
#include <concepts>
#endif

#include <mtlt/matrix_normal_iterator.h>
#include <mtlt/matrix_reverse_iterator.h>

#include <mtlt/matrix_config.h>
#include <mtlt/matrix_type_traits.h>

namespace mtlt {

/**
 * @class matrix
 *
 * The matrix container class is a wrapper over a dynamic array,
 * it allows you to do all basic calculations and operations on matrices
 *
 * @code
 *
 * mtlt::matrix<std::string> matrix; // OK
 * mtlt::matrix<std::string> matrix(3, 3, "MTLT"); // OK
 *
 * mtlt::matrix<int> matrix(3, 3, {
 * 		1, 2, 3,
 * 		4, 5, 6,
 * 		7, 8, 9
 * }); // OK
 *
 * std::vector<int> vector {...};
 * mtlt::matrix<int> matrix(3, 3, vector); // OK
 *
 * mtlt::static_matrix<int, 3, 3> static_matrix({...});
 * mtlt::matrix<int> matrix(3, 3, static_matrix); // OK
 *
 * @endcode
 *
 */
template<typename T>
class matrix;

/**
 * @using fundamental_matrix
 *
 * This using is intended to control that the
 * template parameter T is a fundamental type,
 * otherwise a compilation error will be generated
 * that you are creating an object from an incomplete type
 *
 * @code
 *
 * mtlt::fundamental_matrix<double> matrix(3, 3, 1.5); // OK
 * mtlt::fundamental_matrix<std::string> matrix(3, 3, "MTLT"); // CE
 *
 * @endcode
 */
template<typename T>
using fundamental_matrix = typename std::conditional<!std::is_fundamental<T>::value,
													 detail::incomplete_compile_error_generation_type,
													 matrix<T>>::type;

template<typename T>
class matrix final {
public:
  using value_type = typename std::allocator_traits<std::allocator<T>>::value_type;
  using pointer = typename std::allocator_traits<std::allocator<T>>::pointer;
  using const_pointer = typename std::allocator_traits<std::allocator<T>>::const_pointer;
  using size_type = typename std::allocator_traits<std::allocator<T>>::size_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = matrix_normal_iterator<pointer>;
  using const_iterator = matrix_normal_iterator<const_pointer>;
  using reverse_iterator = matrix_reverse_iterator<iterator>;
  using const_reverse_iterator = matrix_reverse_iterator<const_iterator>;

public:
  MATRIX_CXX17_CONSTEXPR matrix() noexcept = default;

  MATRIX_CXX17_CONSTEXPR matrix(size_type rows, size_type cols, value_type f = {})
	  : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {
	if (f != value_type{})
	  fill(f);
  }

  MATRIX_CXX17_CONSTEXPR explicit matrix(size_type square) : matrix(square, square) {};

  MATRIX_CXX17_CONSTEXPR explicit matrix(const std::vector<std::vector<value_type>> &matrix_vector)
	  : matrix(matrix_vector.size(), matrix_vector[0].size()) {
	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		(*this)(row, col) = matrix_vector[row][col];
  }

  MATRIX_CXX20_CONSTEXPR matrix(size_type rows, size_type cols, const std::initializer_list<T> &initializer)
	  : matrix(rows, cols) {
	std::copy(initializer.begin(), initializer.end(), begin());
  }

#if __cplusplus > 201703L
  template<typename Container> requires(std::convertible_to<typename Container::value_type, T>)
  MATRIX_CXX17_CONSTEXPR matrix(size_type rows, size_type cols, const Container &container)
	  : matrix(rows, cols) {
#else
  template<typename Container,
	  typename std::enable_if<
		  std::is_convertible<typename Container::value_type, value_type>::value, bool>::type = true>
  MATRIX_CXX20_CONSTEXPR matrix(size_type rows, size_type cols, const Container &container)
	  : matrix(rows, cols) {
#endif // C++ <= 201703L
	std::copy(container.begin(), container.end(), begin());
  }

  static matrix identity(size_type rows, size_type cols) {
	matrix identity(rows, cols);
	identity.to_identity();
	return identity;
  }

  MATRIX_CXX17_CONSTEXPR matrix(const matrix &other)
	  : matrix(other.rows_, other.cols_) {
	std::copy(other.begin(), other.end(), begin());
  }

  MATRIX_CXX17_CONSTEXPR matrix(matrix &&other) noexcept
	  : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
	other.rows_ = other.cols_ = size_type{};
	other.data_ = nullptr;
  }

  MATRIX_CXX17_CONSTEXPR matrix &operator=(const matrix &other) {
	if (&other == this)
	  return *this;

	matrix tmp(other);
	*this = std::move(tmp);

	return *this;
  }

  MATRIX_CXX17_CONSTEXPR matrix &operator=(matrix &&other) noexcept {
	if (&other == this)
	  return *this;

	std::swap(rows_, other.rows_);
	std::swap(cols_, other.cols_);
	std::swap(data_, other.data_);

	return *this;
  }

  ~matrix() noexcept {
	delete[] data_;
  }

public:
  MATRIX_CXX17_CONSTEXPR
  iterator begin() noexcept {
	return iterator(data_);
  }

  MATRIX_CXX17_CONSTEXPR
  const_iterator begin() const noexcept {
	return const_iterator(data_);
  }

  MATRIX_CXX17_CONSTEXPR
  reverse_iterator rbegin() noexcept {
	return reverse_iterator(data_ + rows_ * cols_ - 1);
  }

  MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator rbegin() const noexcept {
	return const_reverse_iterator(data_ + rows_ * cols_ - 1);
  }

  MATRIX_CXX17_CONSTEXPR
  const_iterator cbegin() const noexcept {
	return begin();
  }

  MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator crbegin() const noexcept {
	return rbegin();
  }

  MATRIX_CXX17_CONSTEXPR
  iterator end() noexcept {
	return iterator(data_ + rows_ * cols_);
  }

  MATRIX_CXX17_CONSTEXPR
  const_iterator end() const noexcept {
	return const_iterator(data_ + rows_ * cols_);
  }

  MATRIX_CXX17_CONSTEXPR
  reverse_iterator rend() noexcept {
	return reverse_iterator(data_ - 1);
  }

  MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator rend() const noexcept {
	return const_reverse_iterator(data_ - 1);
  }

  MATRIX_CXX17_CONSTEXPR
  const_iterator cend() const noexcept {
	return end();
  }

  MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator crend() const noexcept {
	return rend();
  }

public:
  reference operator()(size_type row, size_type col) {
	return data_[row * cols_ + col];
  }

  const_reference operator()(size_type row, size_type col) const {
	return data_[row * cols_ + col];
  }

  reference at(size_type row, size_type col) {
	if (row >= rows_ || col >= cols_)
	  throw std::out_of_range("row or col is out of range of matrix");

	return (*this)(row, col);
  }

  const_reference at(size_type row, size_type col) const {
	if (row >= rows_ || col >= cols_)
	  throw std::out_of_range("row or col is out of range of matrix");

	return (*this)(row, col);
  }

  MATRIX_CXX17_NODISCARD
  size_type rows() const noexcept { return rows_; }

  MATRIX_CXX17_NODISCARD
  size_type cols() const noexcept { return cols_; }

  MATRIX_CXX17_NODISCARD
  size_type size() const noexcept { return rows_ * cols_; }

  void rows(size_type rows) {
	if (rows_ == rows)
	  return;

	matrix tmp(rows, cols_);
	const size_type min_rows = std::min(rows, rows_);

	for (size_type row = 0; row != min_rows; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		tmp(row, col) = (*this)(row, col);

	*this = std::move(tmp);
  }

  void cols(size_type cols) {
	if (cols_ == cols)
	  return;

	matrix tmp(rows_, cols);
	const size_type min_cols = std::min(cols, cols_);

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != min_cols; ++col)
		tmp(row, col) = (*this)(row, col);

	*this = std::move(tmp);
  }
  void resize(size_type rows, size_type cols) {
	if (cols_ == cols && rows_ == rows)
	  return;

	matrix tmp(rows, cols);
	const size_type min_cols = std::min(cols, cols_);
	const size_type min_rows = std::min(rows, rows_);

	for (size_type row = 0; row != min_rows; ++row)
	  for (size_type col = 0; col != min_cols; ++col)
		tmp(row, col) = (*this)(row, col);

	*this = std::move(tmp);
  }

  void clear() noexcept {
	rows_ = cols_ = size_type{};
	delete[] data_;
	data_ = nullptr;
  }

public:
  void print(std::ostream &os = std::cout, matrix_debug_settings s = matrix_debug_settings{}) const {
	int width = s.width, precision = s.precision;
	char separator = s.separator, end = s.end;
	bool is_double_end = s.is_double_end;

	for (size_type row = 0; row != rows_; ++row) {
	  for (size_type col = 0; col != cols_; ++col) {
		os << std::setw(width)
		   << std::setprecision(precision)
		   << (*this)(row, col)
		   << separator;
	  }
	  os << end;
	}

	if (is_double_end)
	  os << end;
  }

public:
  template<typename UnaryOperation>
  void transform(UnaryOperation &&op) {
	std::transform(begin(), end(), begin(), std::forward<UnaryOperation>(op));
  }

  template<typename BinaryOperation>
  void transform(const matrix &other, BinaryOperation &&op) {
	std::transform(begin(), end(), other.begin(), begin(), std::forward<BinaryOperation>(op));
  }

  template<typename Operation>
  void generate(Operation &&op) {
	std::generate(begin(), end(), std::forward<Operation>(op));
  }

  matrix &mul(const value_type &number) {
	transform([&number](const value_type &item) { return item * number; });
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  matrix &mul(const matrix<U> &rhs) {
#else
  template<typename U>
  matrix &mul(const matrix<U> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (cols_ != rhs.rows())
	  throw std::logic_error("Can't multiply two matrices because lhs.cols() != rhs.rows()");

	const size_type cols = rhs.cols();
	const size_type rows = rows_;

	matrix multiplied(rows, cols);
	for (size_type row = 0; row != rows; ++row)
	  for (size_type col = 0; col != cols; ++col)
		for (size_type k = 0; k != cols_; ++k)
		  multiplied(row, col) += (*this)(row, k) * rhs(k, col);

	*this = std::move(multiplied);
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  matrix &mul_by_element(const matrix<U> &rhs) {
#else
  template<typename U>
  matrix &mul_by_element(const matrix<U> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (rows_ != rhs.rows() or cols_ != rhs.cols())
	  throw std::logic_error("Can't multiply by element two matrices because rows != rhs.rows() or cols != rhs.cols()");

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		(*this)(row, col) *= rhs(row, col);

	return *this;
  }

  matrix &div(const value_type &number) {
	if (std::is_integral<T>::value && number == 0)
	  throw std::logic_error("Dividing by zero");

	transform([&number](const value_type &item) { return item / number; });
	return *this;
  }

  matrix &add(const value_type &number) {
	transform([&number](const value_type &item) { return item + number; });
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  matrix &add(const matrix<U> &rhs) {
#else
  template<typename U>
  matrix &add(const matrix<U> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (rhs.rows() != rows_ || rhs.cols() != cols_)
	  throw std::logic_error("Can't add different sized matrices");

	transform(rhs, [](const T &lhs, const U &rhs) { return lhs + rhs; });
	return *this;
  }

  matrix &sub(const value_type &number) {
	transform([&number](const value_type &item) { return item - number; });
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  matrix &sub(const matrix<U> &rhs) {
#else
  template<typename U>
  matrix &sub(const matrix<U> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (rhs.rows() != rows_ || rhs.cols() != cols_)
	  throw std::logic_error("Can't add different sized matrices");

	transform(rhs, [](const T &lhs, const U &rhs) { return lhs - rhs; });
	return *this;
  }

  matrix &fill(const value_type &number) {
	generate([&number]() { return number; });

	return *this;
  }

  matrix &fill_random(const value_type &left, const value_type &right) {
	using namespace std::chrono;

	std::default_random_engine re(system_clock::now().time_since_epoch().count());
	auto distribution = typename std::conditional<std::is_integral<T>::value,
												  std::uniform_int_distribution<T>,
												  std::uniform_real_distribution<T>>::type(left, right);

	generate([&]() {
	  return distribution(re);
	});

	return *this;
  }

  matrix &to_round() {
	transform([](const value_type &item) { return std::round(item); });
	return *this;
  }

  matrix round() const {
	matrix<T> rounded(*this);
	rounded.transform([](const value_type &item) { return std::round(item); });
	return rounded;
  }

  matrix &to_floor() {
	transform([](const value_type &item) { return std::floor(item); });
	return *this;
  }

  matrix floor() const {
	matrix<T> floored(*this);
	floored.transform([](const value_type &item) { return std::floor(item); });
	return floored;
  }

  matrix &to_ceil() {
	transform([](const value_type &item) { return std::ceil(item); });
	return *this;
  }

  matrix ceil() const {
	matrix<T> ceiled(*this);
	ceiled.transform([](const value_type &item) { return std::ceil(item); });
	return ceiled;
  }

  matrix &to_zero() {
	generate([]() { return value_type{}; });
	return *this;
  }

  matrix zero() const {
	return matrix<T>(rows_, cols_);
  }

  matrix &to_identity() {
	if (rows_ != cols_)
	  throw std::logic_error("Only square matrices can be identity");

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		(*this)(row, col) = row == col ? value_type{1} : value_type{};

	return *this;
  }

  value_type sum() const {
	return std::accumulate(begin(), end(), value_type{});
  }

public:
  void to_join_left(const matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join left rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	*this = join_left(rhs);
  }

  matrix join_left(const matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join left rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	matrix<T> join_matrix(rows_, cols_ + rhs.cols());

	size_type cols2 = rhs.cols();

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (col < cols2)
		  join_matrix(row, col) = rhs(row, col);
		else
		  join_matrix(row, col) = (*this)(row, col - cols_);
	  }

	return join_matrix;
  }

  void to_join_right(const matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join left rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	size_type old_cols = cols_;
	size_type cols2 = rhs.cols();

	this->cols(cols_ + rhs.cols());

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		if (col >= old_cols)
		  (*this)(row, col) = rhs(row, col - cols2);
  }

  matrix join_right(const matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join right rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	matrix<T> join_matrix(rows_, cols_ + rhs.cols());
	size_type cols2 = rhs.cols();

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (col < cols_)
		  join_matrix(row, col) = (*this)(row, col);
		else
		  join_matrix(row, col) = rhs(row, col - cols2);
	  }

	return join_matrix;
  }

  void to_join_top(const matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join top rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	*this = join_top(rhs);
  }

  matrix join_top(const matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join top rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	size_type old_rows = rows_;
	size_type rows2 = rhs.rows();
	matrix<T> join_matrix(rows_ + rhs.rows(), cols_);

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (row < rows2)
		  join_matrix(row, col) = rhs(row, col);
		else
		  join_matrix(row, col) = (*this)(row - old_rows, col);
	  }

	return join_matrix;
  }

  void to_join_bottom(const matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join bottom rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	size_type old_rows = rows_;
	size_type rows2 = rhs.rows();
	this->rows(rows_ + rhs.rows());

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col) {
		if (row >= old_rows)
		  (*this)(row, col) = rhs(row - rows2, col);
	  }
  }

  matrix join_bottom(const matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join bottom rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	matrix<T> join_matrix(rows_ + rhs.rows(), cols_);
	size_type rows2 = rhs.rows();

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (row < rows_)
		  join_matrix(row, col) = (*this)(row, col);
		else
		  join_matrix(row, col) = rhs(row - rows2, col);
	  }

	return join_matrix;
  }

public:
  matrix transpose() const {
	matrix transposed(cols_, rows_);

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		transposed(col, row) = (*this)(row, col);

	return transposed;
  }

  matrix minor(size_type row, size_type col) const {
	matrix minor(rows() - 1, cols() - 1);

	size_type skip_row = 0, skip_col = 0;
	for (size_type r = 0; r != minor.rows_; ++r) {
	  if (row == r)
		skip_row = 1;

	  skip_col = 0;
	  for (size_type c = 0; c != minor.cols_; ++c) {
		if (col == c)
		  skip_col = 1;

		minor(r, c) = (*this)(r + skip_row, c + skip_col);
	  }
	}

	return minor;
  }

  double minor_item(size_type row, size_type col) const {
	return minor(row, col).determinant_gaussian();
  }

  double determinant_gaussian() const {
	if (rows_ != cols_)
	  throw std::logic_error("determinant_gaussian can be found only for square matrices");

	double determinant_value = 1;

	matrix<double> matrix(rows_, cols_, *this);
	const size_type kN = matrix.rows();

	for (size_type i = 0; i != kN; ++i) {
	  double pivot = matrix(i, i);
	  size_type pivot_row = i;
	  for (size_type row = i + 1; row != kN; ++row) {
		double row_i_item = matrix(row, i);
		row_i_item = row_i_item < 0 ? -row_i_item : row_i_item;
		double temp_pivot = pivot < 0 ? -pivot : pivot;

		if (row_i_item > temp_pivot) {
		  pivot = matrix(row, i);
		  pivot_row = row;
		}
	  }

	  if (pivot == value_type{}) {
		return value_type{};
	  }

	  if (pivot_row != i) {
		matrix.swap_rows(i, pivot_row);
		determinant_value = -determinant_value;
	  }

	  determinant_value *= pivot;

	  for (size_type row = i + 1; row != kN; ++row) {
		for (size_type col = i + 1; col != kN; ++col) {
		  matrix(row, col) -= matrix(row, i) * matrix(i, col) / pivot;
		}
	  }
	}

	return determinant_value;
  }

  double determinant_laplacian() const {
	if (rows_ != cols_)
	  throw std::logic_error("determinant_laplacian can be found only for square matrices");

	int sign = 1;
	double determinant_value{};

	if (rows_ == 1 && cols_ == 1)
	  determinant_value = (*this)(0, 0);
	else if (rows_ == 2 && cols_ == 2)
	  determinant_value = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
	else {
	  for (size_type col = 0; col != cols_; ++col) {
		matrix minored = minor(0, col);
		determinant_value += sign * (*this)(0, col) * minored.determinant_laplacian();
		sign = -sign;
	  }
	}

	return determinant_value;
  }

  value_type trace() const {
	if (rows_ != cols_)
	  throw std::logic_error("Can't find trace for non square matrices");

	value_type tr{};
	for (size_type i = 0; i != rows_; ++i)
	  tr += (*this)(i, i);
	return tr;
  }

  matrix calc_complements() const {
	if (rows_ != cols_)
	  throw std::logic_error("Complements matrix can be found only for square matrices");

	matrix<T> complements(rows_, cols_);

	for (size_type row = 0; row != rows_; ++row) {
	  for (size_type col = 0; col != cols_; ++col) {
		complements(row, col) = minor_item(row, col);

		if ((row + col) % 2 != 0)
		  complements(row, col) = -complements(row, col);
	  }
	}

	return complements;
  }

  matrix inverse() const {
	double determinant = determinant_gaussian();

	if (std::fabs(determinant) <= 1e-6)
	  throw std::logic_error("Can't found inverse matrix because determinant is zero");

	return calc_complements().transpose().mul(1 / determinant);
  }

  matrix inverse(double determinant) const {
	if (std::fabs(determinant) <= 1e-6)
	  throw std::logic_error("Can't found inverse matrix because determinant is zero");

	return calc_complements().transpose().mul(1 / determinant);
  }

  void swap_rows(size_type row1, size_type row2) {
	if (row1 >= rows_ || row2 >= rows_)
	  throw std::logic_error("row1 or row2 is bigger that this->rows()");

	std::swap_ranges(begin() + row1 * cols_, begin() + row1 * cols_ + cols_, begin() + row2 * cols_);
  }

  void swap_cols(size_type col1, size_type col2) {
	if (col1 >= cols_ || col2 >= cols_)
	  throw std::logic_error("col1 or col2 is bigger that this->cols()");

	for (size_type row = 0; row != rows_; ++row)
	  std::swap((*this)(row, col1), (*this)(row, col2));
  }

public:
  template<typename EqualCompare = std::equal_to<value_type>>
  bool equal_to(const matrix &rhs) const {
	if (rows_ != rhs.rows() || cols_ != rhs.cols())
	  return false;

	EqualCompare compare;
	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		if (!compare((*this)(row, col), rhs(row, col)))
		  return false;

	return true;
  }

public:

#if __cplusplus > 201703L
  template<typename U> requires (std::convertible_to<U, T>)
  matrix<U> convert_to() const {
#else
  template<typename U>
  matrix<U> convert_to() const {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	matrix<U> convert(rows_, cols_);
	std::copy(begin(), end(), convert.begin());
	return convert;
  }

#if __cplusplus > 201703L
  template<typename U = T> requires (std::convertible_to<U, T>)
  std::vector<U> to_vector() const {
#else
  template<typename U = T>
  std::vector<U> to_vector() const {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	std::vector<U> v(rows_ *cols_);
	std::copy(begin(), end(), v.begin());
	return v;
  }

#if __cplusplus > 201703L
  template<typename U = T> requires (std::convertible_to<U, T>)
  std::vector<std::vector<U>> to_matrix_vector() const {
#else
  template<typename U = T>
  std::vector<std::vector<U>> to_matrix_vector() const {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	std::vector<std::vector<U>> v(rows_, std::vector<U>(cols_));

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		v[row][col] = (*this)(row, col);

	return v;
  }

private:
  size_type rows_{}, cols_{};
  pointer data_ = nullptr;
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &rhs) {
  rhs.print(out);
  return out;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator+=(matrix<T> &lhs, const matrix<U> &rhs) {
#else
template<typename T, typename U>
matrix<T> inline &operator+=(matrix<T> &lhs, const matrix<U> &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.add(rhs);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator-=(matrix<T> &lhs, const matrix<U> &rhs) {
#else
template<typename T, typename U>
matrix<T> inline &operator-=(matrix<T> &lhs, const matrix<U> &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.sub(rhs);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator*=(matrix<T> &lhs, const matrix<U> &rhs) {
#else
template<typename T, typename U>
matrix<T> inline &operator*=(matrix<T> &lhs, const matrix<U> &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.mul(rhs);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator+=(matrix<T> &lhs, const U &value) {
#else
template<typename T, typename U>
matrix<T> inline &operator+=(matrix<T> &lhs, const U &value) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.add(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator-=(matrix<T> &lhs, const U &value) {
#else
template<typename T, typename U>
matrix<T> inline &operator-=(matrix<T> &lhs, const U &value) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.sub(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator*=(matrix<T> &lhs, const U &value) {
#else
template<typename T, typename U>
matrix<T> inline &operator*=(matrix<T> &lhs, const U &value) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.mul(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline &operator/=(matrix<T> &lhs, const U &value) {
#else
template<typename T, typename U>
matrix<T> inline &operator/=(matrix<T> &lhs, const U &value) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.div(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator+(const matrix<T> &lhs, const matrix<U> &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator+(const matrix<T> &lhs, const matrix<U> &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.add(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator-(const matrix<T> &lhs, const matrix<U> &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator-(const matrix<T> &lhs, const matrix<U> &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.sub(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator*(const matrix<T> &lhs, const matrix<U> &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator*(const matrix<T> &lhs, const matrix<U> &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.mul(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator+(const matrix<T> &lhs, const U &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator+(const matrix<T> &lhs, const U &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.add(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator-(const matrix<T> &lhs, const U &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator-(const matrix<T> &lhs, const U &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.sub(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator*(const matrix<T> &lhs, const U &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator*(const matrix<T> &lhs, const U &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.mul(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<U> inline operator*(const U &rhs, const matrix<T> &lhs) {
#else
template<typename T, typename U>
matrix<U> inline operator*(const U &rhs, const matrix<T> &lhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<U> result(lhs);
  result.mul(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U> requires (std::convertible_to<U, T>)
matrix<T> inline operator/(const matrix<T> &lhs, const U &rhs) {
#else
template<typename T, typename U>
matrix<T> inline operator/(const matrix<T> &lhs, const U &rhs) {
  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  matrix<T> result(lhs);
  result.div(rhs);
  return result;
}

template<typename T>
bool inline operator==(const matrix<T> &lhs, const matrix<T> &rhs) {
  return lhs.equal_to(rhs);
}

template<typename T>
bool inline operator!=(const matrix<T> &lhs, const matrix<T> &rhs) {
  return !(lhs == rhs);
}

} // namespace mtlt end

#endif //MTLT_MATRIX_H_
