/*
 *        Copyright 2023, School21 Student Library
 *        All rights reserved
 *
 *        Author:   Gubaydullin Nurislam aka tonitaga
 *        Email:    gubaydullin.nurislam@gmail.com
 *        Telegram: @tonitaga
 *
 *        The Template Matrix Library for different types
 *        contains most of the operations on matrices.
 *
 *        The Template Matrix library is written in the C++20 standard
 *        Supports C++11 C++14 C++17 C++20 C++23 versions. Also
 *        The Library is  written in STL style and supports
 *        STL Algorithms Library.
*/

#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H_

#include <iterator>

#include <mtl/matrix_config.h>

namespace mtl {
template<typename Iterator>
class matrix_normal_iterator {
protected:
  Iterator current_;

public:
  using iterator_type = Iterator;
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename std::remove_reference<decltype(*current_)>::type;
  using pointer = Iterator;
  using const_pointer = const Iterator;
  using reference = value_type &;
  using const_reference = const value_type &;
  using difference_type = std::ptrdiff_t;

public:
  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator() noexcept: current_(Iterator()) {};

  explicit MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator(const Iterator &it) noexcept: current_(it) {};

public:
  MATRIX_CXX17_CONSTEXPR
  reference operator*() noexcept { return *current_; }

  MATRIX_CXX17_CONSTEXPR
  const_reference operator*() const noexcept { return *current_; }

  MATRIX_CXX17_CONSTEXPR
  pointer operator->() noexcept { return current_; }

  MATRIX_CXX17_CONSTEXPR
  const_pointer operator->() const noexcept { return current_; }

  MATRIX_CXX17_CONSTEXPR
  reference operator[](difference_type n) noexcept {
	return current_[n];
  }

  MATRIX_CXX17_CONSTEXPR
  const_reference operator[](difference_type n) const noexcept {
	return current_[n];
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator &operator++() noexcept {
	++current_;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator operator++(int) noexcept {
	return matrix_normal_iterator(current_++);
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator &operator--() noexcept {
	--current_;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator operator--(int) noexcept {
	return matrix_normal_iterator(current_--);
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator &operator+=(difference_type n) noexcept {
	current_ += n;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator operator+(difference_type n) noexcept {
	return matrix_normal_iterator(current_ + n);
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator &operator-=(difference_type n) noexcept {
	current_ -= n;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_normal_iterator operator-(difference_type n) noexcept {
	return matrix_normal_iterator(current_ - n);
  }

  MATRIX_CXX17_CONSTEXPR
  const Iterator &Base() const noexcept {
	return current_;
  }
};

template<typename Iterator>
MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
bool operator==(const matrix_normal_iterator<Iterator> &lhs,
				const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() == rhs.Base();
}

template<typename Iterator>
MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
bool operator!=(const matrix_normal_iterator<Iterator> &lhs,
				const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() != rhs.Base();
}

template<typename Iterator>
MATRIX_CXX17_NODISCARD
inline bool operator<(const matrix_normal_iterator<Iterator> &lhs,
					  const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() < rhs.Base();
}

template<typename Iterator>
MATRIX_CXX17_NODISCARD
inline bool operator>(const matrix_normal_iterator<Iterator> &lhs,
					  const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() > rhs.Base();
}

template<typename Iterator>
MATRIX_CXX17_NODISCARD
inline bool operator<=(const matrix_normal_iterator<Iterator> &lhs,
					   const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() < rhs.Base();
}

template<typename Iterator>
MATRIX_CXX17_NODISCARD
inline bool operator>=(const matrix_normal_iterator<Iterator> &lhs,
					   const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() > rhs.Base();
}

template<typename Iterator>
MATRIX_CXX17_NODISCARD
inline std::ptrdiff_t operator-(const matrix_normal_iterator<Iterator> &lhs,
								const matrix_normal_iterator<Iterator> &rhs) {
  return lhs.Base() - rhs.Base();
}
}

#endif //MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H_
