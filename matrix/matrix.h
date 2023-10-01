#ifndef matrix_LIBRARY_CPP_matrix_H_
#define matrix_LIBRARY_CPP_matrix_H_

#include <vector>
#include <concepts>
#include <iostream>
#include <type_traits>

#include "matrix_state.h"
#include "matrix_normal_iterator.h"
#include "matrix_reverse_iterator.h"

namespace ng {
    template <fundamental T>
    class matrix {
    public:
        using value_type =             typename std::allocator_traits<std::allocator<T>>::value_type;
        using pointer =                typename std::allocator_traits<std::allocator<T>>::pointer;
        using const_pointer =          typename std::allocator_traits<std::allocator<T>>::const_pointer;
        using size_type =              typename std::allocator_traits<std::allocator<T>>::size_type;
        using reference =              value_type &;
        using const_reference =        const value_type &;
        using iterator =               matrix_normal_iterator<pointer>;
        using const_iterator =         matrix_normal_iterator<const_pointer>;
        using reverse_iterator =       matrix_reverse_iterator<iterator>;
        using const_reverse_iterator = matrix_reverse_iterator<const_iterator>;

    public:
        constexpr matrix() noexcept = default;

        constexpr matrix(size_type rows, size_type cols, value_type fill = {});
        constexpr explicit matrix(size_type square) : matrix(square, square) {};

        constexpr explicit matrix(const std::vector<std::vector<value_type>> &);

        constexpr matrix(size_type rows, size_type cols, const std::initializer_list<T> &initializer);

        template<typename Container>
        requires(std::convertible_to<typename Container::value_type, T>)
        constexpr matrix(size_type rows, size_type cols, const Container &container);

        static matrix identity(size_type rows, size_type cols);

        constexpr matrix(const matrix &);
        constexpr matrix(matrix &&) noexcept;

        constexpr matrix &operator=(const matrix &);
        constexpr matrix &operator=(matrix &&) noexcept;

        ~matrix() noexcept;

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
        void print(std::ostream &os = std::cout) const;

    public:
        template<typename UnaryOperation>
        void transform(UnaryOperation &&op);

        template<typename BinaryOperation>
        void transform(const matrix &other, BinaryOperation &&op);

        template<typename Operation>
        void generate(Operation &&op);

        matrix &mul(const value_type &number);

        template<typename U>
        requires(std::convertible_to<U, T>)
        matrix &mul(const matrix<U> &rhs);

        matrix &div(const value_type &number);

        matrix &add(const value_type &number);

        template<typename U>
        requires(std::convertible_to<U, T>)
        matrix &add(const matrix<U> &rhs);

        matrix &sub(const value_type &number);

        template<typename U>
        requires(std::convertible_to<U, T>)
        matrix &sub(const matrix<U> &rhs);

        matrix &fill(const value_type &number);
        matrix &fill_random(const value_type &left, const value_type &right);

        matrix &round();
        matrix &floor();
        matrix &ceil();
        matrix &zero();

        matrix &to_identity();

        value_type sum() const;

    public:
        matrix transpose() const;
        matrix minor(size_type row, size_type col) const;

        value_type minor_item(size_type row, size_type col) const;
        value_type determinant() const;
        value_type trace() const;

        matrix calc_complements() const;
        matrix inverse() const;

    public:
        bool equal_to(const matrix &rhs) const;

    public:
        template<typename ConvertType>
        matrix<ConvertType> convert_to() const;

        std::vector<value_type> convert_to_vector() const;
        std::vector<std::vector<value_type>> convert_to_matrix_vector() const;

    private:
        size_type rows_ {}, cols_ {};
        pointer data_ = nullptr;
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const matrix<T> &rhs);

    template <typename T, typename U>
    matrix<T> inline &operator +=(const matrix<T> &lhs, const matrix<U> &rhs);

    template <typename T, typename U>
    matrix<T> inline &operator -=(const matrix<T> &lhs, const matrix<U> &rhs);

    template <typename T, typename U>
    matrix<T> inline &operator *=(const matrix<T> &lhs, const matrix<U> &rhs);

    template <typename T>
    matrix<T> inline &operator +=(const matrix<T> &lhs, const T &value);

    template <typename T>
    matrix<T> inline &operator -=(const matrix<T> &lhs, const T &value);

    template <typename T>
    matrix<T> inline &operator *=(const matrix<T> &lhs, const T &value);

    template <typename T>
    matrix<T> inline &operator /=(matrix<T> &lhs, const T &value);

    template <typename T, typename U>
    matrix<T> inline operator +(const matrix<T> &lhs, const matrix<U> &rhs);

    template <typename T, typename U>
    matrix<T> inline operator -(const matrix<T> &lhs, const matrix<U> &rhs);

    template <typename T, typename U>
    matrix<T> inline operator *(const matrix<T> &lhs, const matrix<U> &rhs);

    template <typename T>
    matrix<T> inline operator +(const matrix<T> &lhs, const T &value);

    template <typename T>
    matrix<T> inline operator -(const matrix<T> &lhs, const T &value);

    template <typename T>
    matrix<T> inline operator *(const matrix<T> &lhs, const T &value);

    template <typename T>
    matrix<T> inline operator *(const T &value, const matrix<T> &lhs);

    template <typename T>
    matrix<T> inline operator /(const matrix<T> &lhs, const T &value);

    template <typename T>
    bool inline operator ==(const matrix<T> &lhs, const matrix<T> &rhs);
}

#include "implementation/matrix.tpp"

#endif //matrix_LIBRARY_CPP_matrix_H_
