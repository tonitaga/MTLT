#ifndef MATRIX_LIBRARY_CPP_MATRIX_H_
#define MATRIX_LIBRARY_CPP_MATRIX_H_

#include <type_traits>

#include "matrix_normal_iterator.h"

namespace ng {
    template <typename T>
    class Matrix {
        static_assert(std::is_integral_v<T> or std::is_floating_point_v<T>,
                "Template parameter T must be integral or floating point!");

    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const pointer;
        using size_type = std::size_t;
        using iterator = __internal::MatrixNormalIterator<pointer>;
        using const_iterator = __internal::MatrixNormalIterator<const_pointer>;

    public:
        Matrix() noexcept = default;

        Matrix(size_type rows, size_type cols) : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {};
        explicit Matrix(size_type square) : Matrix(square, square) {};


    public:
        iterator begin() noexcept { return iterator(data_); }
        iterator end() noexcept { return iterator(data_ + rows_ * cols_); }

        const_iterator begin() const noexcept { return const_iterator(data_); }
        const_iterator end() const noexcept { return const_iterator(data_ + rows_ * cols_); }

    private:
        size_type rows_ {}, cols_ {};
        value_type *data_ = nullptr;
    };
}

#include "matrix.tpp"

#endif //MATRIX_LIBRARY_CPP_MATRIX_H_
