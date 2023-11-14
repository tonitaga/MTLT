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

#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_ROW_MATRIX_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_ROW_MATRIX_H_

#include <matrix/matrix.h>

namespace mtl {
template<typename T>
class row_matrix : public matrix<T> {
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
  row_matrix() = default;
  explicit row_matrix(size_type rows, value_type fill = value_type{})
	  : matrix<T>(rows, 1, fill) {};

  template<typename Container>
  row_matrix(size_type rows, const Container &container)
	  : matrix<T>(rows, 1, container) {};

public:
  reference operator[](size_type row) {
	return this->operator()(row, 0);
  }

  const_reference operator[](size_type row) const {
	return this->operator()(row, 0);
  }
};
}

#endif //MATRIX_TEMPLATE_LIBRARY_CPP_ROW_MATRIX_H_
