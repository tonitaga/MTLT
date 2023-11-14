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

#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_COL_MATRIX_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_COL_MATRIX_H_

#include <matrix/matrix.h>

namespace mtl {
template<typename T>
class col_matrix : public matrix<T> {
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
  col_matrix() noexcept = default;
  explicit col_matrix(size_type cols, value_type fill = value_type{})
	  : matrix<T>(1, cols, fill) {};

  template<typename Container>
  col_matrix(size_type cols, const Container &container)
	  : matrix<T>(1, cols, container) {};

public:
  reference operator[](size_type col) {
	return this->operator()(0, col);
  }

  const_reference operator[](size_type col) const {
	return this->operator()(0, col);
  }
};
}

#endif //MATRIX_TEMPLATE_LIBRARY_CPP_COL_MATRIX_H_
