#ifndef MATRIX_LIBRARY_CPP_MATRIX_H_
#define MATRIX_LIBRARY_CPP_MATRIX_H_

#include <type_traits>

#include "matrix_normal_iterator.h"

namespace ng {
    struct MatrixDebugSettings {
        int width = 0, precision = 0;
        char separator = ' ', end = '\n';
        bool is_double_end = false;
    };

    constexpr MatrixDebugSettings default_debug = {
            .width = 3,
            .precision = 3,
            .separator = ' ',
            .end = '\n',
            .is_double_end = true
    };


    template <typename T>
    class Matrix {
        static_assert(std::is_integral_v<T> or std::is_floating_point_v<T>,
                      "Template parameter T must be integral or floating point!");

    public:
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using const_reference = const T &;
        using const_pointer = const pointer;
        using size_type = std::size_t;
        using iterator = __internal::MatrixNormalIterator<pointer>;
        using const_iterator = __internal::MatrixNormalIterator<const_pointer>;

    public:
        constexpr Matrix() noexcept = default;

        constexpr Matrix(size_type rows, size_type cols) : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {};
        constexpr explicit Matrix(size_type square) : Matrix(square, square) {};

        constexpr Matrix(const Matrix &);
        constexpr Matrix(Matrix &&) noexcept;

        constexpr Matrix &operator=(const Matrix &);
        constexpr Matrix &operator=(Matrix &&) noexcept;

        ~Matrix() noexcept;

    public:
        iterator begin() noexcept { return iterator(data_); }
        iterator end() noexcept { return iterator(data_ + rows_ * cols_); }

        const_iterator begin() const noexcept { return const_iterator(data_); }
        const_iterator end() const noexcept { return const_iterator(data_ + rows_ * cols_); }

    public:
        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        reference at(size_type row, size_type col);
        const_reference at(size_type row, size_type col) const;

    public:
        void print(std::ostream &os, MatrixDebugSettings settings = default_debug) const;

    private:
        size_type rows_ {}, cols_ {};
        value_type *data_ = nullptr;
    };

    using IMatrix = Matrix<int>;
    using UMatrix = Matrix<unsigned>;
    using FMatrix = Matrix<float>;
    using DMatrix = Matrix<double>;
}

#include "matrix.tpp"

#endif //MATRIX_LIBRARY_CPP_MATRIX_H_
