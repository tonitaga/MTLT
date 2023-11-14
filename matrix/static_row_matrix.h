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

#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_STATIC_ROW_MATRIX_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_STATIC_ROW_MATRIX_H_

#include <matrix/static_matrix.h>

namespace mtl {
template<typename T, std::size_t Rows>
class static_row_matrix : public static_matrix<T, Rows, 1> {
public:
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = matrix_normal_iterator<pointer>;
  using const_iterator = matrix_normal_iterator<const_pointer>;
  using reverse_iterator = matrix_reverse_iterator<iterator>;
  using const_reverse_iterator = matrix_reverse_iterator<const_iterator>;

public:
  explicit MATRIX_CXX17_CONSTEXPR static_row_matrix(value_type fill = value_type{})
	  : static_matrix<T, Rows, 1>(fill) {};

  template<typename Container>
  explicit MATRIX_CXX17_CONSTEXPR static_row_matrix(const Container &container)
	  : static_matrix<T, Rows, 1>(container) {};

public:
  reference operator[](size_type col) {
	return this->operator()(0, col);
  }

  const_reference operator[](size_type col) const {
	return this->operator()(0, col);
  }
};
}

#endif //MATRIX_TEMPLATE_LIBRARY_CPP_STATIC_ROW_MATRIX_H_
