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

#ifndef MTLT_PRINT_H_
#define MTLT_PRINT_H_

#include <iostream>

#include <mtlt/matrix_type_traits.h>

namespace mtlt {

template<typename Head>
void print(Head &&head) {
#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(std::cout);
  } else {
	std::cout << head << std::endl;
  }
#else
  std::cout << head << std::endl;
#endif
}

template<typename Head>
void print(std::ostream &out, Head &&head) {
#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(out);
  } else {
	out << head << std::endl;
  }
#else
  out << head << std::endl;
#endif
}

template<typename Head>
void print(std::ofstream &out, Head &&head) {
#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(out);
  } else {
	out << head << std::endl;
  }
#else
  out << head << std::endl;
#endif
}

template<typename Head>
void print(std::stringstream &out, Head &&head) {
#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(out);
  } else {
	out << head << std::endl;
  }
#else
  out << head << std::endl;
#endif
}

#if __cplusplus > 201703L
template <printable_or_streamable Head, printable_or_streamable ...Tail>
void print(Head &&head, Tail &&...tail) {
#else
template<typename Head, typename ...Tail>
void print(Head &&head, Tail &&...tail) {
  static_assert(is_printable<Head>::value || is_streamable<std::ostream, Head>::value,
				"'Head' template parameter must support << operation with stream, or Head::print(ostream) method");
#endif

#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(std::cout);
  } else {
	std::cout << head << std::endl;
  }
#else
  std::cout << head << std::endl;
#endif

  print(std::forward<Tail>(tail)...);
}

#if __cplusplus > 201703L
template <printable_or_streamable Head, printable_or_streamable ...Tail>
void print(std::ostream &out, Head &&head, Tail &&...tail) {
#else
template<typename Head, typename ...Tail>
void print(std::ostream &out, Head &&head, Tail &&...tail) {
  static_assert(is_printable<Head>::value || is_streamable<std::ostream, Head>::value,
				"'Head' template parameter must support << operation with stream, or Head::print(ostream) method");
#endif

#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(out);
  } else {
	out << head << std::endl;
  }
#else
  out << head << std::endl;
#endif

  print(out, std::forward<Tail>(tail)...);
}

#if __cplusplus > 201703L
template <printable_or_streamable Head, printable_or_streamable ...Tail>
void print(std::ofstream &out, Head &&head, Tail &&...tail) {
#else
template<typename Head, typename ...Tail>
void print(std::ofstream &out, Head &&head, Tail &&...tail) {
  static_assert(is_printable<Head>::value || is_streamable<std::ofstream, Head>::value,
				"'Head' template parameter must support << operation with stream, or Head::print(ofstream) method");
#endif

#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(out);
  } else {
	out << head << std::endl;
  }
#else
  out << head << std::endl;
#endif

  print(out, std::forward<Tail>(tail)...);
}

#if __cplusplus > 201703L
template <printable_or_streamable Head, printable_or_streamable ...Tail>
void print(std::stringstream &out, Head &&head, Tail &&...tail) {
#else
template<typename Head, typename ...Tail>
void print(std::stringstream &out, Head &&head, Tail &&...tail) {
  static_assert(is_printable<Head>::value || is_streamable<std::stringstream, Head>::value,
				"'Head' template parameter must support << operation with stream, or Head::print(stringstream) method");
#endif

#if __cplusplus >= 201703L
  if constexpr (is_printable_v<Head>) {
	head.print(out);
  } else {
	out << head << std::endl;
  }
#else
  out << head << std::endl;
#endif

  print(out, std::forward<Tail>(tail)...);
}

} // namespace mtlt end

#endif // MTLT_PRINT_H_
