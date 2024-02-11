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

#ifndef MTLT_ADAPTERS_H_
#define MTLT_ADAPTERS_H_

#include <utility>

namespace mtlt {

template <typename Iterable>
class reverse_adapter {
public:
  explicit reverse_adapter(Iterable &iterable)
  	: iterable(iterable) {};

public:
  auto begin() -> decltype(std::declval<Iterable>().rbegin()) {
	return iterable.rbegin();
  }

  auto begin() const -> decltype(std::declval<const Iterable>().rbegin()) {
	return iterable.rbegin();
  }

  auto end() -> decltype(std::declval<Iterable>().rend()) {
	return iterable.rend();
  }

  auto end() const -> decltype(std::declval<const Iterable>().rend()) {
	return iterable.rend();
  }

private:
  Iterable &iterable;
};

template <typename Iterable>
reverse_adapter<Iterable> reverse(Iterable &iterable) {
  return reverse_adapter<Iterable>(iterable);
}

} // namespace mtlt end

#endif // MTLT_ADAPTERS_H_
