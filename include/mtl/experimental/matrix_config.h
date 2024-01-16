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

#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_EXPERIMENTAL_CONFIG_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_EXPERIMENTAL_CONFIG_H_

struct matrix_debug_settings {
  int width = 3;
  int precision = 3;
  char separator = ' ';
  char end = '\n';
  bool is_double_end = false;
};

#ifndef MATRIX_CXX17_CONSTEXPR
#  if __cplusplus >= 201703L
#    define MATRIX_CXX17_CONSTEXPR constexpr
#  else
#    define MATRIX_CXX17_CONSTEXPR
#  endif
#endif

#ifndef MATRIX_CXX20_CONSTEXPR
#  if __cplusplus > 201703L
#    define MATRIX_CXX20_CONSTEXPR constexpr
#  else
#    define MATRIX_CXX20_CONSTEXPR
#  endif
#endif

#ifndef MATRIX_CXX23_CONSTEXPR
#  if __cplusplus > 202002L
#    define MATRIX_CXX23_CONSTEXPR constexpr
#  else
#    define MATRIX_CXX23_CONSTEXPR
#  endif
#endif

#ifndef MATRIX_CXX17_NODISCARD
#  if __cplusplus >= 201703L
#    define MATRIX_CXX17_NODISCARD [[nodiscard]]
#  else
#    define MATRIX_CXX17_NODISCARD
#  endif
#endif

#ifndef MATRIX_CXX17_UNUSED
#  if __cplusplus >= 201703L
#    define MATRIX_CXX17_UNUSED [[maybe_unused]]
#  else
#    define MATRIX_CXX17_UNUSED
#  endif
#endif

#ifndef MATRIX_CXX17_INLINE
#  if __cplusplus >= 201703L
#    define MATRIX_CXX17_INLINE inline
#  else
#    define MATRIX_CXX17_INLINE
#  endif
#endif

#endif // MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_EXPERIMENTAL_CONFIG_H_
