#ifndef MATRIX_LIBRARY_CPP_MATRIX_H_
#define MATRIX_LIBRARY_CPP_MATRIX_H_

#include <vector>
#include <type_traits>

#include "matrix_state.h"
#include "matrix_normal_iterator.h"
#include "matrix_reverse_iterator.h"

namespace ng {
    template <typename T>
    class Matrix {
        static_assert(std::is_fundamental_v<T>,
                      "Template parameter T must be fundamental!");

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

        template<typename U>
        constexpr Matrix(const Matrix<U> &);

        static Matrix identity(size_type rows, size_type cols);

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

        reverse_iterator rbegin() noexcept { return reverse_iterator(data_ + rows_ * cols_ - 1); }
        reverse_iterator rend() noexcept { return reverse_iterator(data_ - 1); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(data_ - 1); }

        const_iterator cbegin() const noexcept { return begin(); }
        const_iterator cend() const noexcept { return end(); }

        const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        const_reverse_iterator crend() const noexcept { return rend(); }

    public:
        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        reference at(size_type row, size_type col);
        const_reference at(size_type row, size_type col) const;

        size_type rows() const noexcept { return rows_; }
        size_type cols() const noexcept { return cols_; }

        void rows(size_type rows);
        void cols(size_type cols);
        void resize(size_type rows, size_type cols);
        void clear() noexcept;

    public:
        void print(std::ostream &os, MatrixDebugSettings settings = default_debug) const;

    public:
        template<typename UnaryOperation>
        void transform(UnaryOperation &&op);

        template<typename BinaryOperation>
        void transform(const Matrix &other, BinaryOperation &&op);

        template<typename Operation>
        void generate(Operation &&op);

        void mul(const value_type &number);
        void mul(const Matrix &);

        template<typename U>
        void mul(const Matrix<U> &rhs);

        void div(const value_type &number);

        void add(const value_type &number);
        void add(const Matrix &rhs);

        template<typename U>
        void add(const Matrix<U> &rhs);

        void sub(const value_type &number);
        void sub(const Matrix &rhs);

        template<typename U>
        void sub(const Matrix<U> &rhs);

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
