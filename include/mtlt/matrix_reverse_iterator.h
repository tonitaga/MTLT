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
 *        The Template Matrix library is written in the C++20 standard
 *        Supports C++11 C++14 C++17 C++20 C++23 versions. Also
 *        The Library is  written in STL style and supports
 *        STL Algorithms Library.
*/

#ifndef MTLT_MATRIX_REVERSE_ITERATOR_H_
#define MTLT_MATRIX_REVERSE_ITERATOR_H_

#include <iterator>

#include <mtlt/matrix_config.h>

namespace mtlt {
template<typename NormalIterator>
class matrix_reverse_iterator {
protected:
  NormalIterator current_;

public:
  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator() noexcept: current_(NormalIterator()) {};

  explicit MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator(const typename NormalIterator::iterator_type &it) noexcept
	  : current_(it) {};

public:
  using iterator_type = typename NormalIterator::iterator_type;
  using pointer = typename NormalIterator::pointer;
  using const_pointer = typename NormalIterator::const_pointer;
  using reference = typename NormalIterator::reference;
  using const_reference = typename NormalIterator::const_reference;
  using value_type = typename NormalIterator::value_type;
  using difference_type = typename NormalIterator::difference_type;
  using iterator_category = typename NormalIterator::iterator_category;

public:
  MATRIX_CXX17_CONSTEXPR
  reference operator*() noexcept { return *current_; }

  MATRIX_CXX17_CONSTEXPR
  const_reference operator*() const noexcept { return *current_; }

  MATRIX_CXX17_CONSTEXPR
  pointer operator->() noexcept { return current_.Base(); }

  MATRIX_CXX17_CONSTEXPR
  const_pointer operator->() const noexcept { return current_.Base(); }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator &operator++() noexcept {
	--current_;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  reference operator[](difference_type n) noexcept {
	return current_[-n];
  }

  MATRIX_CXX17_CONSTEXPR
  const_reference operator[](difference_type n) const noexcept {
	return current_[-n];
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator operator++(int) noexcept {
	return matrix_reverse_iterator(current_--);
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator &operator--() noexcept {
	++current_;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator operator--(int) noexcept {
	return matrix_reverse_iterator(current_++);
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator &operator+=(difference_type n) noexcept {
	current_ -= n;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator operator+(difference_type n) noexcept {
	return matrix_reverse_iterator((current_ - n).Base());
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator &operator-=(difference_type n) noexcept {
	current_ += n;
	return *this;
  }

  MATRIX_CXX17_CONSTEXPR
  matrix_reverse_iterator operator-(difference_type n) noexcept {
	return matrix_reverse_iterator((current_ + n).Base());
  }

  const iterator_type &Base() const noexcept {
	return current_.Base();
  }
};

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
bool operator==(const matrix_reverse_iterator<NormalIterator> &lhs,
				const matrix_reverse_iterator<NormalIterator> &rhs) {
  return lhs.Base() == rhs.Base();
}

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD MATRIX_CXX17_CONSTEXPR
bool operator!=(const matrix_reverse_iterator<NormalIterator> &lhs,
				const matrix_reverse_iterator<NormalIterator> &rhs) {
  return lhs.Base() != rhs.Base();
}

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD
inline bool operator<(const matrix_reverse_iterator<NormalIterator> &lhs,
					  const matrix_reverse_iterator<NormalIterator> &rhs) {
  return lhs.Base() < rhs.Base();
}

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD
inline bool operator>(const matrix_reverse_iterator<NormalIterator> &lhs,
					  const matrix_reverse_iterator<NormalIterator> &rhs) {
  return lhs.Base() > rhs.Base();
}

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD
inline bool operator<=(const matrix_reverse_iterator<NormalIterator> &lhs,
					   const matrix_reverse_iterator<NormalIterator> &rhs) {
  return lhs.Base() < rhs.Base();
}

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD
inline bool operator>=(const matrix_reverse_iterator<NormalIterator> &lhs,
					   const matrix_reverse_iterator<NormalIterator> &rhs) {
  return lhs.Base() > rhs.Base();
}

template<typename NormalIterator>
MATRIX_CXX17_NODISCARD
inline std::ptrdiff_t operator-(const matrix_reverse_iterator<NormalIterator> &lhs,
								const matrix_reverse_iterator<NormalIterator> &rhs) {
  return rhs.Base() - lhs.Base();
}

} // namespace mtlt end

#endif // MTLT_MATRIX_REVERSE_ITERATOR_H_
