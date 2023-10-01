#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_H

#include <array>
#include <concepts>
#include <iostream>
#include <type_traits>

#include "matrix_state.h"
#include "matrix_normal_iterator.h"
#include "matrix_reverse_iterator.h"

namespace ng {
    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    class static_matrix {
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
        constexpr static_matrix() noexcept = default;
        constexpr explicit static_matrix(value_type fill) noexcept;

        constexpr explicit static_matrix(const std::array<T, Rows * Cols> &initializer);

        template<typename Container> requires(std::convertible_to<typename Container::value_type, T>)
        constexpr explicit static_matrix(const Container &);

        template<typename Container> requires(std::convertible_to<typename Container::value_type, T>)
        constexpr static_matrix &operator=(const Container &container) {
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
        void transform(const static_matrix &other, BinaryOperation &&op);

        template<typename Operation>
        void generate(Operation &&op);

        static_matrix &fill(const value_type &number);
        static_matrix &fill_random(const value_type &left, const value_type &right);

        static_matrix &to_round();
        static_matrix round() const;

        static_matrix &to_floor();
        static_matrix floor() const;

        static_matrix &to_ceil();
        static_matrix ceil() const;

        static_matrix &to_zero();
        constexpr static_matrix zero() const;

        static_matrix &to_identity() requires(Rows == Cols);
        constexpr static_matrix identity() const requires(Rows == Cols);

        static_matrix &mul(const value_type &value);
        static_matrix &add(const value_type &value);
        static_matrix &sub(const value_type &value);
        static_matrix &div(const value_type &value);

        template<fundamental U, size_type Rows2, size_type Cols2>
        requires(non_zero_dimension<Rows2, Cols2> and std::convertible_to<U, T> and Cols == Rows2)
        constexpr static_matrix<T, Rows, Cols2> mul(const static_matrix<U, Rows2, Cols2> &rhs) const {
            static_matrix<T, Rows, Cols2> multiplied;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols2; ++col)
                    for (size_type k = 0; k != Cols; ++k)
                        multiplied(row, col) += (*this)(row, k) * rhs(k, col);

            return multiplied;
        }

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr static_matrix<T, Rows, Cols> add(const static_matrix<U, Rows, Cols> &rhs) const;

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr static_matrix<T, Rows, Cols> sub(const static_matrix<U, Rows, Cols> &rhs) const;

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr static_matrix<T, Rows, Cols> div_by_element(const static_matrix<U, Rows, Cols> &rhs) const;

        template<fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr static_matrix<T, Rows, Cols> mul_by_element(const static_matrix<U, Rows, Cols> &rhs) const;

        constexpr value_type sum() const;

    public:
        constexpr static_matrix<T, Cols, Rows> transpose() const;
        constexpr static_matrix<T, Rows - 1, Cols - 1> minor(size_type row, size_type col) const requires (non_zero_dimension<Rows - 1, Cols - 1>);
        constexpr value_type minor_item(size_type row, size_type col) const;
        constexpr value_type determinant() const requires(Rows == Cols);
        constexpr static_matrix calc_complements() const requires(Rows == Cols);
        constexpr static_matrix inverse() const requires(Rows == Cols);
        constexpr value_type trace() const requires(Rows == Cols);

    public:
        template <fundamental U = T>
        requires(std::convertible_to<U, T>)
        constexpr std::array<U, Rows * Cols> to_array() const;

        template <fundamental U>
        requires(std::convertible_to<U, T>)
        constexpr static_matrix<U, Rows, Cols> convert_to() const;

    public:
        constexpr bool equal_to(const static_matrix &rhs) const;

    private:
        size_type rows_ = Rows, cols_ = Cols;
        value_type data_[Rows * Cols] {};

    private:
    };

    template <fundamental T, std::size_t Rows, std::size_t Cols>
    std::ostream &operator<<(std::ostream &out, const static_matrix<T, Rows, Cols> &rhs) {
        rhs.print(out);
        return out;
    }

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr static_matrix<T, Rows, Cols> operator+(const static_matrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Rows1 == Rows2 and Cols1 == Cols2)
    [[__nodiscard__]] constexpr static_matrix<T, Rows1, Cols1> operator+(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator+=(static_matrix<T, Rows, Cols>&lhs, const U &value);


    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr static_matrix<T, Rows, Cols> operator-(const static_matrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Rows1 == Rows2 and Cols1 == Cols2)
    [[__nodiscard__]] constexpr static_matrix<T, Rows1, Cols1> operator-(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator-=(static_matrix<T, Rows, Cols>&lhs, const U &value);


    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr static_matrix<T, Rows, Cols> operator*(const static_matrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Cols1 == Rows2)
    [[__nodiscard__]] constexpr static_matrix<T, Rows1, Cols2> operator*(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator*=(static_matrix<T, Rows, Cols>&lhs, const U &value);


    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] constexpr static_matrix<T, Rows, Cols> operator/(const static_matrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator/=(static_matrix<T, Rows, Cols>&lhs, const U &value);

    template <fundamental T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] constexpr bool operator==(const static_matrix<T, Rows, Cols> &lhs, const static_matrix<T, Rows, Cols> &rhs);

    template <fundamental T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] constexpr bool operator!=(const static_matrix<T, Rows, Cols> &lhs, const static_matrix<T, Rows, Cols> &rhs);
}

#include "implementation/static_matrix.tpp"

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
