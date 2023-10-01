#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_H

#include <array>
#include <concepts>
#include <iostream>
#include <type_traits>

#include <matrix/matrix_state.h>
#include <matrix/matrix_normal_iterator.h>
#include <matrix/matrix_reverse_iterator.h>

namespace ng {
    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    class StaticMatrix {
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
        constexpr StaticMatrix() noexcept = default;
        constexpr explicit StaticMatrix(value_type fill) noexcept;

        constexpr StaticMatrix(const std::array<T, Rows * Cols> &initializer);

        template<typename Container> requires(std::convertible_to<typename Container::value_type, T>)
        constexpr StaticMatrix(const Container &);

        template<typename Container> requires(std::convertible_to<typename Container::value_type, T>)
        constexpr StaticMatrix &operator=(const Container &container) {
            if (Rows * Cols != container.size())
                throw std::logic_error("");

            std::copy(container.begin(), container.end(), begin());
        }

    public:
        constexpr iterator begin() noexcept { return iterator(data_); }
        constexpr iterator end() noexcept { return iterator(data_ + rows_ * cols_); }

        constexpr const_iterator begin() const noexcept { return const_iterator(data_); }
        constexpr const_iterator end() const noexcept { return const_iterator(data_ + rows_ * cols_); }

        constexpr const_iterator cbegin() const noexcept { return const_iterator(data_); }
        constexpr const_iterator cend() const noexcept { return const_iterator(data_ + rows_ * cols_); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(data_ + rows_ * cols_ - 1); }
        constexpr reverse_iterator rend() noexcept { return reverse_iterator(data_ - 1); }

        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(data_ - 1); }

        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(data_ - 1); }

    public:
        constexpr reference operator()(size_type row, size_type col);
        constexpr const_reference operator()(size_type row, size_type col) const;

        constexpr reference at(size_type row, size_type col);
        constexpr const_reference at(size_type row, size_type col) const;

        constexpr size_type rows() const noexcept;
        constexpr size_type cols() const noexcept;
        constexpr size_type size() const noexcept;

    public:
        void print(std::ostream &os = std::cout, MatrixDebugSettings settings = default_debug) const;

    public:
        template<typename UnaryOperation>
        constexpr void transform(UnaryOperation &&op);

        template<typename BinaryOperation>
        void transform(const StaticMatrix &other, BinaryOperation &&op);

        template<typename Operation>
        void generate(Operation &&op);

        StaticMatrix &fill(const value_type &number);
        StaticMatrix &fill_random(const value_type &left, const value_type &right);

        StaticMatrix &to_round();
        StaticMatrix round() const;

        StaticMatrix &to_floor();
        StaticMatrix floor() const;

        StaticMatrix &to_ceil();
        StaticMatrix ceil() const;

        StaticMatrix &to_zero();
        constexpr StaticMatrix zero() const;

        StaticMatrix &to_identity() requires(Rows == Cols);
        constexpr StaticMatrix identity() const requires(Rows == Cols);

        StaticMatrix &mul(const value_type &value);
        StaticMatrix &add(const value_type &value);
        StaticMatrix &sub(const value_type &value);
        StaticMatrix &div(const value_type &value);

        template<fundamental U, size_type Rows2, size_type Cols2>
        requires(non_zero_dimension<Rows2, Cols2> and std::convertible_to<U, T> and Cols == Rows2)
        constexpr StaticMatrix<T, Rows, Cols2> mul(const StaticMatrix<U, Rows2, Cols2> &rhs) const {
            StaticMatrix<T, Rows, Cols2> multiplied;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols2; ++col)
                    for (size_type k = 0; k != Cols; ++k)
                        multiplied(row, col) += (*this)(row, k) * rhs(k, col);

            return multiplied;
        }

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr StaticMatrix<T, Rows, Cols> add(const StaticMatrix<U, Rows, Cols> &rhs) const;

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr StaticMatrix<T, Rows, Cols> sub(const StaticMatrix<U, Rows, Cols> &rhs) const;

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr StaticMatrix<T, Rows, Cols> div_by_element(const StaticMatrix<U, Rows, Cols> &rhs) const;

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr StaticMatrix<T, Rows, Cols> mul_by_element(const StaticMatrix<U, Rows, Cols> &rhs) const;

        constexpr value_type sum() const;

    public:
        constexpr StaticMatrix<T, Cols, Rows> transpose() const;
        constexpr StaticMatrix<T, Rows - 1, Cols - 1> minor(size_type row, size_type col) const requires (non_zero_dimension<Rows - 1, Cols - 1>);
        constexpr value_type minor_item(size_type row, size_type col) const;
        constexpr value_type determinant() const requires(Rows == Cols);
        constexpr StaticMatrix calc_complements() const requires(Rows == Cols);
        constexpr StaticMatrix inverse() const requires(Rows == Cols);
        constexpr value_type trace() const requires(Rows == Cols);

    public:
        template <fundamental U = T>
        requires(std::convertible_to<U, T>)
        constexpr std::array<U, Rows * Cols> to_array() const;

        template <fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr StaticMatrix<U, Rows, Cols> convert_to() const;

    public:
        constexpr bool equal_to(const StaticMatrix &rhs) const;

    private:
        size_type rows_ = Rows, cols_ = Cols;
        value_type data_[Rows * Cols] {};

    private:
    };

    template <fundamental T, std::size_t Square>
    using SquareMatrix = StaticMatrix<T, Square, Square>;

    template <fundamental T>
    using Matrix3x3 = SquareMatrix<T, 3>;

    template <fundamental T, std::size_t Rows, std::size_t Cols>
    std::ostream &operator<<(std::ostream &out, const StaticMatrix<T, Rows, Cols> &rhs) {
        rhs.print(out);
        return out;
    }

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows, Cols> operator+(const StaticMatrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Rows1 == Rows2 and Cols1 == Cols2)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows1, Cols1> operator+(const StaticMatrix<T, Rows1, Cols1> &lhs, const StaticMatrix<U, Rows2, Cols2> &rhs);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    StaticMatrix<T, Rows, Cols> &operator+=(StaticMatrix<T, Rows, Cols>&lhs, const U &value);


    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows, Cols> operator-(const StaticMatrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Rows1 == Rows2 and Cols1 == Cols2)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows1, Cols1> operator-(const StaticMatrix<T, Rows1, Cols1> &lhs, const StaticMatrix<U, Rows2, Cols2> &rhs);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    StaticMatrix<T, Rows, Cols> &operator-=(StaticMatrix<T, Rows, Cols>&lhs, const U &value);


    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows, Cols> operator*(const StaticMatrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Cols1 == Rows2)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows1, Cols2> operator*(const StaticMatrix<T, Rows1, Cols1> &lhs, const StaticMatrix<U, Rows2, Cols2> &rhs);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    StaticMatrix<T, Rows, Cols> &operator*=(StaticMatrix<T, Rows, Cols>&lhs, const U &value);


    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr StaticMatrix<T, Rows, Cols> operator/(const StaticMatrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    StaticMatrix<T, Rows, Cols> &operator/=(StaticMatrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] constexpr bool operator==(const StaticMatrix<T, Rows, Cols> &lhs, const StaticMatrix<T, Rows, Cols> &rhs);

    template <fundamental T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] constexpr bool operator!=(const StaticMatrix<T, Rows, Cols> &lhs, const StaticMatrix<T, Rows, Cols> &rhs);
}

#include "static_matrix.tpp"

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
