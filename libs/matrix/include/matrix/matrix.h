#ifndef MATRIX_LIBRARY_CPP_MATRIX_H_
#define MATRIX_LIBRARY_CPP_MATRIX_H_

#include <vector>
#include <concepts>
#include <iostream>
#include <type_traits>

#include <matrix/matrix_state.h>
#include <matrix/matrix_normal_iterator.h>
#include <matrix/matrix_reverse_iterator.h>

namespace ng {
    template <fundamental T>
    class Matrix {
    public:
        using value_type = typename std::allocator_traits<std::allocator<T>>::value_type;
        using pointer = typename std::allocator_traits<std::allocator<T>>::pointer;
        using const_pointer = typename std::allocator_traits<std::allocator<T>>::const_pointer;
        using size_type = typename std::allocator_traits<std::allocator<T>>::size_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = __internal::MatrixNormalIterator<pointer>;
        using const_iterator = __internal::MatrixNormalIterator<const_pointer>;
        using reverse_iterator = __internal::MatrixReverseInterator<iterator>;
        using const_reverse_iterator = __internal::MatrixReverseInterator<const_iterator>;

    public:
        constexpr Matrix() noexcept = default;

        constexpr Matrix(size_type rows, size_type cols, value_type fill = {});
        constexpr explicit Matrix(size_type square) : Matrix(square, square) {};

        constexpr explicit Matrix(const std::vector<std::vector<value_type>> &);

        constexpr Matrix(size_type rows, size_type cols, const std::initializer_list<T> &initializer);

        template<typename Container>
        requires(std::convertible_to<typename Container::value_type, T>)
        constexpr Matrix(size_type rows, size_type cols, const Container &container);

        static Matrix identity(size_type rows, size_type cols);

        constexpr Matrix(const Matrix &);
        constexpr Matrix(Matrix &&) noexcept;

        constexpr Matrix &operator=(const Matrix &);
        constexpr Matrix &operator=(Matrix &&) noexcept;

        ~Matrix() noexcept;

    public:
        constexpr iterator begin() noexcept { return iterator(data_); }
        constexpr iterator end() noexcept { return iterator(data_ + rows_ * cols_); }

        constexpr const_iterator begin() const noexcept { return const_iterator(data_); }
        constexpr const_iterator end() const noexcept { return const_iterator(data_ + rows_ * cols_); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(data_ + rows_ * cols_ - 1); }
        constexpr reverse_iterator rend() noexcept { return reverse_iterator(data_ - 1); }

        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(data_ - 1); }

        constexpr const_iterator cbegin() const noexcept { return begin(); }
        constexpr const_iterator cend() const noexcept { return end(); }

        constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        constexpr const_reverse_iterator crend() const noexcept { return rend(); }

    public:
        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        reference at(size_type row, size_type col);
        const_reference at(size_type row, size_type col) const;

        size_type rows() const noexcept { return rows_; }
        size_type cols() const noexcept { return cols_; }
        size_type size() const noexcept { return rows_ * cols_; }

        void rows(size_type rows);
        void cols(size_type cols);
        void resize(size_type rows, size_type cols);
        void clear() noexcept;

    public:
        void print(std::ostream &os = std::cout, MatrixDebugSettings settings = default_debug) const;

    public:
        template<typename UnaryOperation>
        void transform(UnaryOperation &&op);

        template<typename BinaryOperation>
        void transform(const Matrix &other, BinaryOperation &&op);

        template<typename Operation>
        void generate(Operation &&op);

        Matrix &mul(const value_type &number);

        template<typename U>
        requires(std::convertible_to<U, T>)
        Matrix &mul(const Matrix<U> &rhs);

        Matrix &div(const value_type &number);

        Matrix &add(const value_type &number);

        template<typename U>
        requires(std::convertible_to<U, T>)
        Matrix &add(const Matrix<U> &rhs);

        Matrix &sub(const value_type &number);

        template<typename U>
        requires(std::convertible_to<U, T>)
        Matrix &sub(const Matrix<U> &rhs);

        Matrix &fill(const value_type &number);
        Matrix &fill_random(const value_type &left, const value_type &right);

        Matrix &round();
        Matrix &floor();
        Matrix &ceil();
        Matrix &zero();

        Matrix &to_identity();

        value_type sum() const;

    public:
        Matrix transpose() const;
        Matrix minor(size_type row, size_type col) const;

        value_type minor_item(size_type row, size_type col) const;
        value_type determinant() const;
        value_type trace() const;

        Matrix calc_complements() const;
        Matrix inverse() const;

    public:
        bool equal_to(const Matrix &rhs) const;

    public:
        template<typename ConvertType>
        Matrix<ConvertType> convert_to() const;

        std::vector<value_type> convert_to_vector() const;
        std::vector<std::vector<value_type>> convert_to_matrix_vector() const;

    private:
        size_type rows_ {}, cols_ {};
        pointer data_ = nullptr;
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs);

    template <typename T, typename U>
    Matrix<T> inline &operator +=(const Matrix<T> &lhs, const Matrix<U> &rhs);

    template <typename T, typename U>
    Matrix<T> inline &operator -=(const Matrix<T> &lhs, const Matrix<U> &rhs);

    template <typename T, typename U>
    Matrix<T> inline &operator *=(const Matrix<T> &lhs, const Matrix<U> &rhs);

    template <typename T>
    Matrix<T> inline &operator +=(const Matrix<T> &lhs, const T &value);

    template <typename T>
    Matrix<T> inline &operator -=(const Matrix<T> &lhs, const T &value);

    template <typename T>
    Matrix<T> inline &operator *=(const Matrix<T> &lhs, const T &value);

    template <typename T>
    Matrix<T> inline &operator /=(Matrix<T> &lhs, const T &value);

    template <typename T, typename U>
    Matrix<T> inline operator +(const Matrix<T> &lhs, const Matrix<U> &rhs);

    template <typename T, typename U>
    Matrix<T> inline operator -(const Matrix<T> &lhs, const Matrix<U> &rhs);

    template <typename T, typename U>
    Matrix<T> inline operator *(const Matrix<T> &lhs, const Matrix<U> &rhs);

    template <typename T>
    Matrix<T> inline operator +(const Matrix<T> &lhs, const T &value);

    template <typename T>
    Matrix<T> inline operator -(const Matrix<T> &lhs, const T &value);

    template <typename T>
    Matrix<T> inline operator *(const Matrix<T> &lhs, const T &value);

    template <typename T>
    Matrix<T> inline operator *(const T &value, const Matrix<T> &lhs);

    template <typename T>
    Matrix<T> inline operator /(const Matrix<T> &lhs, const T &value);

    template <typename T>
    bool inline operator ==(const Matrix<T> &lhs, const Matrix<T> &rhs);

    using IMatrix = Matrix<int>;
    using BMatrix = Matrix<bool>;
    using CMatrix = Matrix<char>;
    using UMatrix = Matrix<unsigned>;
    using FMatrix = Matrix<float>;
    using DMatrix = Matrix<double>;
}

#include "matrix.tpp"

#endif //MATRIX_LIBRARY_CPP_MATRIX_H_
