/*
 *        Copyright 2023, School21 Student Library
 *        All rights reserved
 *
 *        Author:   Gubaydullin Nurislam aka tonitaga
 *        Email:    gubaydullin.nurislam@gmail.com
 *        Telegram: @tonitaga
 *
 *        The Template Matrix Library for fundamental types
 *        contains most of the operations on matrices.
 *
 *        The Template Matrix library is written in the C++20 standard
 *        Supports C++11 C++14 C++17 C++20 C++23 versions
 *
*/

#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_EXPERIMENTAL_ATOMIC_MATRIX_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_EXPERIMENTAL_ATOMIC_MATRIX_H_

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

#include <mtl/matrix_normal_iterator.h>
#include <mtl/matrix_reverse_iterator.h>

#include <mtl/experimental/matrix_config.h>
#include <mtl/experimental/matrix_type_traits.h>

namespace mtl::experimental {

template<typename T, template<typename> class Atomic = std::atomic>
class atomic_matrix {
public:
  static_assert(is_fundamental_atomic<Atomic<T>>::value,
				"\n1) Atomic<T> must be atomic type"
				"\n2) Atomic<T>::value_type must be fundamental type");

public:
  using atomic_type = Atomic<T>;
  using atomic_value_type = typename atomic_type::value_type;
  using value_type = typename std::allocator_traits<std::allocator<atomic_type>>::value_type;
  using pointer = typename std::allocator_traits<std::allocator<atomic_type>>::pointer;
  using const_pointer = typename std::allocator_traits<std::allocator<atomic_type>>::const_pointer;
  using size_type = typename std::allocator_traits<std::allocator<atomic_type>>::size_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = matrix_normal_iterator<pointer>;
  using const_iterator = matrix_normal_iterator<const_pointer>;
  using reverse_iterator = matrix_reverse_iterator<iterator>;
  using const_reverse_iterator = matrix_reverse_iterator<const_iterator>;

public:
  MATRIX_CXX17_CONSTEXPR atomic_matrix() noexcept = default;

  MATRIX_CXX17_CONSTEXPR atomic_matrix(size_type rows, size_type cols, atomic_value_type f = {})
	  : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {
	if (f != value_type{})
	  fill(f);
  }

  MATRIX_CXX17_CONSTEXPR explicit atomic_matrix(size_type square) : atomic_matrix(square, square) {};

  template<typename Container,
	  typename std::enable_if<
		  std::is_convertible<typename Container::value_type, atomic_value_type>::value ||
			  std::is_same<typename Container::value_type, atomic_type>::value, bool>::type = true>
  MATRIX_CXX17_CONSTEXPR atomic_matrix(size_type rows, size_type cols, const Container &container)
	  : atomic_matrix(rows, cols) {
	auto it = begin();
	for (const auto &value : container) {
	  (*it).store(value);
	  ++it;
	}
  }

  MATRIX_CXX17_CONSTEXPR atomic_matrix(size_type rows, size_type cols,
									   const std::initializer_list<atomic_value_type> &initializer)
	  : atomic_matrix(rows, cols) {
	auto it = begin();
	for (const auto &value : initializer) {
	  (*it).store(value);
	  ++it;
	}
  }

  static atomic_matrix identity(size_type rows, size_type cols) {
	atomic_matrix identity(rows, cols);
	identity.to_identity();
	return identity;
  }

  MATRIX_CXX17_CONSTEXPR atomic_matrix(const atomic_matrix &other)
	  : atomic_matrix(other.rows_, other.cols_) {
	auto it = begin();
	for (const auto &value : other) {
	  (*it).store(value);
	  ++it;
	}
  }

  MATRIX_CXX17_CONSTEXPR atomic_matrix(atomic_matrix &&other) noexcept
	  : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
	other.rows_ = other.cols_ = size_type{};
	other.data_ = nullptr;
  }

  MATRIX_CXX17_CONSTEXPR atomic_matrix &operator=(atomic_matrix &&other) noexcept {
	if (&other == this)
	  return *this;

	std::swap(rows_, other.rows_);
	std::swap(cols_, other.cols_);
	std::swap(data_, other.data_);

	return *this;
  }

  MATRIX_CXX17_CONSTEXPR atomic_matrix &operator=(const atomic_matrix &other) {
	if (&other == this)
	  return *this;

	atomic_matrix tmp(other);
	*this = std::move(tmp);

	return *this;
  }

  ~atomic_matrix() noexcept {
	delete[] data_;
  }

public:
  MATRIX_CXX17_CONSTEXPR
  iterator begin() noexcept {
	return iterator(data_);
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_iterator begin() const noexcept {
	return const_iterator(data_);
  }

  MATRIX_CXX17_CONSTEXPR
  reverse_iterator rbegin() noexcept {
	return reverse_iterator(data_ + rows_ * cols_ - 1);
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator rbegin() const noexcept {
	return const_reverse_iterator(data_ + rows_ * cols_ - 1);
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_iterator cbegin() const noexcept {
	return begin();
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator crbegin() const noexcept {
	return rbegin();
  }

  MATRIX_CXX17_CONSTEXPR
  iterator end() noexcept {
	return iterator(data_ + rows_ * cols_);
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_iterator end() const noexcept {
	return const_iterator(data_ + rows_ * cols_);
  }

  MATRIX_CXX17_CONSTEXPR
  reverse_iterator rend() noexcept {
	return reverse_iterator(data_ - 1);
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_reverse_iterator rend() const noexcept {
	return const_reverse_iterator(data_ - 1);
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
  const_iterator cend() const noexcept {
	return end();
  }

  MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
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

  MATRIX_CXX17_NODISCARD const_reference at(size_type row, size_type col) const {
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

	atomic_matrix tmp(rows, cols_);
	const size_type min_rows = std::min(rows, rows_);

	for (size_type row = 0; row != min_rows; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		tmp(row, col).store((*this)(row, col));

	*this = std::move(tmp);
  }

  void cols(size_type cols) {
	if (cols_ == cols)
	  return;

	atomic_matrix tmp(rows_, cols);
	const size_type min_cols = std::min(cols, cols_);

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != min_cols; ++col)
		tmp(row, col).store((*this)(row, col));

	*this = std::move(tmp);
  }

  void resize(size_type rows, size_type cols) {
	if (cols_ == cols && rows_ == rows)
	  return;

	atomic_matrix tmp(rows, cols);
	const size_type min_cols = std::min(cols, cols_);
	const size_type min_rows = std::min(rows, rows_);

	for (size_type row = 0; row != min_rows; ++row)
	  for (size_type col = 0; col != min_cols; ++col)
		tmp(row, col).store((*this)(row, col));

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
	for (auto it = begin(); it != end(); ++it)
	  (*it).store(op(*it));
  }

  template<typename BinaryOperation>
  void transform(const atomic_matrix &other, BinaryOperation &&op) {
	auto this_it = begin();
	for (auto it = other.begin(); it != other.end(); ++it, ++this_it)
	  (*this_it).store(op(*it, *this_it));
  }

  template<typename Operation>
  void generate(Operation &&op) {
	for (auto it = begin(); it != end(); ++it)
	  (*it).store(op());
  }

  atomic_matrix &mul(const atomic_value_type &number) {
	transform([&number](const value_type &item) { return item * number; });
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  atomic_matrix &mul(const atomic_matrix<U> &rhs) {
#else
	template<typename U>
	atomic_matrix &mul(const atomic_matrix<U> &rhs) {
	  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (cols_ != rhs.rows())
	  throw std::logic_error("Can't multiply two matrices because lhs.cols() != rhs.rows()");

	const size_type cols = rhs.cols();
	const size_type rows = rows_;

	atomic_matrix multiplied(rows, cols);
	for (size_type row = 0; row != rows; ++row)
	  for (size_type col = 0; col != cols; ++col)
		for (size_type k = 0; k != cols_; ++k)
		  multiplied(row, col).fetch_add((*this)(row, k) * rhs(k, col));

	*this = std::move(multiplied);
	return *this;
  }

  atomic_matrix &div(const atomic_value_type &number) {
	if (std::is_integral<atomic_value_type>::value && number == 0)
	  throw std::logic_error("Dividing by zero");

	transform([&number](const value_type &item) { return item / number; });
	return *this;
  }

  atomic_matrix &add(const atomic_value_type &number) {
	transform([&number](const value_type &item) { return item + number; });
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  atomic_matrix &add(const atomic_matrix<U> &rhs) {
#else
	template<typename U>
	atomic_matrix &add(const atomic_matrix<U> &rhs) {
	  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (rhs.rows() != rows_ || rhs.cols() != cols_)
	  throw std::logic_error("Can't add different sized matrices");

	transform(rhs, [](const T &lhs, const U &rhs) { return lhs + rhs; });
	return *this;
  }

  atomic_matrix &sub(const atomic_value_type &number) {
	transform([&number](const value_type &item) { return item - number; });
	return *this;
  }

#if __cplusplus > 201703L
  template<typename U> requires(std::convertible_to<U, T>)
  atomic_matrix &sub(const atomic_matrix<U> &rhs) {
#else
	template<typename U>
	atomic_matrix &sub(const atomic_matrix<U> &rhs) {
	  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	if (rhs.rows() != rows_ || rhs.cols() != cols_)
	  throw std::logic_error("Can't add different sized matrices");

	transform(rhs, [](const T &lhs, const U &rhs) { return lhs - rhs; });
	return *this;
  }

  atomic_matrix &fill(const atomic_value_type &number) {
	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		(*this)(row, col).store(number);

	return *this;
  }

  atomic_matrix &fill_random(const atomic_value_type &left, const atomic_value_type &right) {
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

  atomic_matrix &to_round() {
	transform([](const atomic_value_type &item) { return std::round(item); });
	return *this;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix round() const {
	atomic_matrix rounded(*this);
	rounded.transform([](const atomic_value_type &item) { return std::round(item); });
	return rounded;
  }

  atomic_matrix &to_floor() {
	transform([](const atomic_value_type &item) { return std::floor(item); });
	return *this;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix floor() const {
	atomic_matrix floored(*this);
	floored.transform([](const atomic_value_type &item) { return std::floor(item); });
	return floored;
  }

  atomic_matrix &to_ceil() {
	transform([](const atomic_value_type &item) { return std::ceil(item); });
	return *this;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix ceil() const {
	atomic_matrix ceiled(*this);
	ceiled.transform([](const atomic_value_type &item) { return std::ceil(item); });
	return ceiled;
  }

  atomic_matrix &to_zero() {
	generate([]() { return atomic_value_type{}; });
	return *this;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix zero() const {
	return atomic_matrix(rows_, cols_);
  }

  atomic_matrix &to_identity() {
	if (rows_ != cols_)
	  throw std::logic_error("Only square matrices can be identity");

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		(*this)(row, col).store(row == col ? value_type{1} : value_type{});

	return *this;
  }

  MATRIX_CXX17_NODISCARD atomic_value_type sum() const {
	atomic_value_type sum{};
	for (const auto &value : *this)
	  sum += value;

	return sum;
  }

public:
  void to_join_left(const atomic_matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join left rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	*this = join_left(rhs);
  }

  MATRIX_CXX17_NODISCARD atomic_matrix join_left(const atomic_matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join left rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	atomic_matrix join_matrix(rows_, cols_ + rhs.cols());

	size_type cols2 = rhs.cols();

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (col < cols2)
		  join_matrix(row, col).store(rhs(row, col));
		else
		  join_matrix(row, col).store((*this)(row, col - cols_));
	  }

	return join_matrix;
  }

  void to_join_right(const atomic_matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join left rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	size_type old_cols = cols_;
	size_type cols2 = rhs.cols();

	this->cols(cols_ + rhs.cols());

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		if (col >= old_cols)
		  (*this)(row, col).store(rhs(row, col - cols2));
  }

  MATRIX_CXX17_NODISCARD atomic_matrix join_right(const atomic_matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join right rhs matrix to lhs, because lhs.rows() != rhs.rows()");

	atomic_matrix join_matrix(rows_, cols_ + rhs.cols());
	size_type cols2 = rhs.cols();

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (col < cols_)
		  join_matrix(row, col).store((*this)(row, col));
		else
		  join_matrix(row, col).store(rhs(row, col - cols2));
	  }

	return join_matrix;
  }

  void to_join_top(const atomic_matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join top rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	*this = join_top(rhs);
  }

  MATRIX_CXX17_NODISCARD atomic_matrix join_top(const atomic_matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join top rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	size_type old_rows = rows_;
	size_type rows2 = rhs.rows();
	atomic_matrix join_matrix(rows_ + rhs.rows(), cols_);

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (row < rows2)
		  join_matrix(row, col).store(rhs(row, col));
		else
		  join_matrix(row, col).store((*this)(row - old_rows, col));
	  }

	return join_matrix;
  }

  void to_join_bottom(const atomic_matrix &rhs) {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join bottom rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	size_type old_rows = rows_;
	size_type rows2 = rhs.rows();
	this->rows(rows_ + rhs.rows());

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col) {
		if (row >= old_rows)
		  (*this)(row, col).store(rhs(row - rows2, col));
	  }
  }

  MATRIX_CXX17_NODISCARD atomic_matrix join_bottom(const atomic_matrix &rhs) const {
	if (rhs.rows() != rows_)
	  throw std::logic_error("Can't join bottom rhs matrix to lhs, because lhs.cols() != rhs.cols()");

	atomic_matrix join_matrix(rows_ + rhs.rows(), cols_);
	size_type rows2 = rhs.rows();

	for (size_type row = 0; row != join_matrix.rows(); ++row)
	  for (size_type col = 0; col != join_matrix.cols(); ++col) {
		if (row < rows_)
		  join_matrix(row, col).store((*this)(row, col));
		else
		  join_matrix(row, col).store(rhs(row - rows2, col));
	  }

	return join_matrix;
  }

public:
  MATRIX_CXX17_NODISCARD atomic_matrix transpose() const {
	atomic_matrix transposed(cols_, rows_);

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		transposed(col, row).store((*this)(row, col));

	return transposed;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix minor(size_type row, size_type col) const {
	atomic_matrix minor(rows() - 1, cols() - 1);

	size_type skip_row = 0, skip_col = 0;
	for (size_type r = 0; r != minor.rows_; ++r) {
	  if (row == r)
		skip_row = 1;

	  skip_col = 0;
	  for (size_type c = 0; c != minor.cols_; ++c) {
		if (col == c)
		  skip_col = 1;

		minor(r, c).store((*this)(r + skip_row, c + skip_col));
	  }
	}

	return minor;
  }

  MATRIX_CXX17_NODISCARD double minor_item(size_type row, size_type col) const {
	return minor(row, col).determinant_gaussian();
  }

  MATRIX_CXX17_NODISCARD double determinant_gaussian() const {
	if (rows_ != cols_)
	  throw std::logic_error("determinant_gaussian can be found only for square matrices");

	double determinant_value = 1;

	atomic_matrix<double> matrix(rows_, cols_, *this);
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
		  matrix(row, col).fetch_sub(matrix(row, i) * matrix(i, col) / pivot);
		}
	  }
	}

	return determinant_value;
  }

  MATRIX_CXX17_NODISCARD double determinant_laplacian() const {
	if (rows_ != cols_)
	  throw std::logic_error("determinant_gaussian can be found only for square matrices");

	int sign = 1;
	double determinant_value{};

	if (rows_ == 1 && cols_ == 1)
	  determinant_value = (*this)(0, 0);
	else if (rows_ == 2 && cols_ == 2)
	  determinant_value = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
	else {
	  for (size_type col = 0; col != cols_; ++col) {
		atomic_matrix minored = minor(0, col);
		determinant_value += sign * (*this)(0, col) * minored.determinant_laplacian();
		sign = -sign;
	  }
	}

	return determinant_value;
  }

  MATRIX_CXX17_NODISCARD atomic_value_type trace() const {
	if (rows_ != cols_)
	  throw std::logic_error("Can't find trace for non square matrices");

	atomic_value_type tr{};
	for (size_type i = 0; i != rows_; ++i)
	  tr += (*this)(i, i);
	return tr;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix calc_complements() const {
	if (rows_ != cols_)
	  throw std::logic_error("Complements matrix can be found only for square matrices");

	atomic_matrix complements(rows_, cols_);

	for (size_type row = 0; row != rows_; ++row) {
	  for (size_type col = 0; col != cols_; ++col) {
		complements(row, col).store(minor_item(row, col));

		if ((row + col) % 2 != 0)
		  complements(row, col).store(-complements(row, col));
	  }
	}

	return complements;
  }

  MATRIX_CXX17_NODISCARD atomic_matrix inverse() const {
	double det = determinant_gaussian();

	if (det <= 1e-6)
	  throw std::logic_error("Can't found inverse matrix because determinant is zero");

	return calc_complements().transpose().mul(1 / det);
  }

  void swap_rows(size_type row1, size_type row2) {
	if (row1 >= rows_ || row2 >= rows_)
	  throw std::logic_error("row1 or row2 is bigger that this->rows()");

	auto begin1 = begin() + row1 * cols_, end = begin() + row1 * cols_ + cols_;
	auto begin2 = begin() + row2 * cols_;

	for (auto it = begin1; it != end; ++it) {
	  atomic_value_type tmp = *it;
	  (*it).store(*begin2);
	  (*begin2).store(tmp);
	  ++begin2;
	}
  }

  void swap_cols(size_type col1, size_type col2) {
	if (col1 >= cols_ || col2 >= cols_)
	  throw std::logic_error("col1 or col2 is bigger that this->cols()");

	for (size_type row = 0; row != rows_; ++row) {
	  atomic_value_type tmp = (*this)(row, col1);
	  (*this)(row, col1).store((*this)(row, col2));
	  (*this)(row, col2).store(tmp);
	}
  }

public:
  MATRIX_CXX17_NODISCARD bool equal_to(const atomic_matrix &rhs) const {
	std::not_equal_to<value_type> compare;

	for (size_type row = 0; row != rows_; ++row)
	  for (size_type col = 0; col != cols_; ++col)
		if (compare((*this)(row, col), rhs(row, col)))
		  return false;

	return true;
  }

public:
#if __cplusplus > 201703L
  template<fundamental U> requires (std::convertible_to<U, T>)
  atomic_matrix<U> convert_to() const {
#else
	template<typename U>
	atomic_matrix<U> convert_to() const {
	  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	atomic_matrix<U> convert(rows_, cols_);

	auto begin = convert.begin();
	for (const auto &value : *this) {
	  (*begin).store(value);
	  ++begin;
	}

	return convert;
  }

#if __cplusplus > 201703L
  template<fundamental U = T> requires (std::convertible_to<U, T>)
  std::vector<Atomic<U>> to_vector() const {
#else
	template<typename U = T>
	std::vector<Atomic<U>> to_vector() const {
	  static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
	std::vector<Atomic<U>> v(rows_ *cols_);
	auto begin = v.begin();
	for (const auto &value : *this) {
	  (*begin).store(value);
	  ++begin;
	}
	return v;
  }

private:
  size_type rows_ {}, cols_ {};
  pointer data_ = nullptr;
};

template<typename T, template<typename> class Atomic>
std::ostream &operator<<(std::ostream &out, const atomic_matrix<T, Atomic> &rhs) {
  rhs.print(out);
  return out;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator+=(atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix <T, Atomic> inline &operator+=(atomic_matrix <T, Atomic> &lhs, const atomic_matrix <U, Atomic> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.add(rhs);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator-=(atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline &operator-=(atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.sub(rhs);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator*=(atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline &operator*=(atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.mul(rhs);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator+=(atomic_matrix<T, Atomic> &lhs, const U &value) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline &operator+=(atomic_matrix<T, Atomic> &lhs, const U &value) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.add(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator-=(atomic_matrix<T, Atomic> &lhs, const U &value) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline &operator-=(atomic_matrix<T, Atomic> &lhs, const U &value) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.sub(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator*=(atomic_matrix<T, Atomic> &lhs, const U &value) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline &operator*=(atomic_matrix<T, Atomic> &lhs, const U &value) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.mul(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline &operator/=(atomic_matrix<T, Atomic> &lhs, const U &value) {
#else
template<typename T, typename U, template<typename> class Atomic>
  atomic_matrix<T, Atomic> inline &operator/=(atomic_matrix<T, Atomic> &lhs, const U &value) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  lhs.div(value);
  return lhs;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator+(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline operator+(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.add(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator-(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline operator-(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.sub(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator*(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
  atomic_matrix<T, Atomic> inline operator*(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<U, Atomic> &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.mul(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator+(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
#else
template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline operator+(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.add(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator-(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline operator-(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.sub(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator*(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline operator*(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.mul(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<U, Atomic> inline operator*(const U &rhs, const atomic_matrix<T, Atomic> &lhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<U, Atomic> inline operator*(const U &rhs, const atomic_matrix<T, Atomic> &lhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.mul(rhs);
  return result;
}

#if __cplusplus > 201703L
template<typename T, typename U, template<typename> class Atomic> requires (std::convertible_to<U, T>)
atomic_matrix<T, Atomic> inline operator/(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
#else
  template<typename T, typename U, template<typename> class Atomic>
atomic_matrix<T, Atomic> inline operator/(const atomic_matrix<T, Atomic> &lhs, const U &rhs) {
	static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif
  atomic_matrix<T, Atomic> result(lhs);
  result.div(rhs);
  return result;
}

template<typename T, template<typename> class Atomic>
bool inline operator==(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<T, Atomic> &rhs) {
  return lhs.equal_to(rhs);
}

template<typename T, template<typename> class Atomic>
bool inline operator!=(const atomic_matrix<T, Atomic> &lhs, const atomic_matrix<T, Atomic> &rhs) {
  return !(lhs == rhs);
}

}

#endif // MATRIX_TEMPLATE_LIBRARY_CPP_EXPERIMENTAL_ATOMIC_MATRIX_H_
