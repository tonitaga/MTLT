#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP

#include "static_matrix.h"

#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <algorithm>

namespace ng {
    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(value_type fill) noexcept {
        if (fill != value_type{})
            for (size_type i = 0; i != Rows * Cols; ++i)
                data_[i] = fill;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(const std::array<T, Rows * Cols> &initializer) {
        constexpr std::size_t kSize = Rows * Cols;
        for (std::size_t i = 0; i != kSize; ++i)
            data_[i] = initializer[i];
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <typename Container> requires(std::convertible_to<typename Container::value_type, T>)
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(const Container &container) {
        if (Rows * Cols != container.size())
            throw std::logic_error("container has more/less items than in matrix");

        std::copy(container.begin(), container.end(), begin());
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::reference StaticMatrix<T, Rows, Cols>::operator()(size_type row, size_type col) {
        return data_[row * cols_ + col];
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::const_reference StaticMatrix<T, Rows, Cols>::operator()(size_type row, size_type col) const {
        return data_[row * cols_ + col];
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::reference StaticMatrix<T, Rows, Cols>::at(size_type row, size_type col) {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of matrix bounds");
        return (*this)(row, col);
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::const_reference StaticMatrix<T, Rows, Cols>::at(size_type row, size_type col) const {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of matrix bounds");
        return (*this)(row, col);
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::size_type StaticMatrix<T, Rows, Cols>::rows() const noexcept {
        return rows_;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::size_type StaticMatrix<T, Rows, Cols>::cols() const noexcept {
        return cols_;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::size_type StaticMatrix<T, Rows, Cols>::size() const noexcept {
        return rows_ * cols_;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    void StaticMatrix<T, Rows, Cols>::print(std::ostream &os, MatrixDebugSettings settings) const {
        auto [width, precision, separator, end, is_double_end] = settings;

        for (size_type row = 0; row != rows_; ++row) {
            for (size_type col = 0; col != cols_; ++col) {
                os << std::setw(width)
                   << std::setprecision(precision)
                   << (*this)(row, col)
                   << separator;
            }
            os << end;
        }

        if (is_double_end)
            os << end;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <typename UnaryOperation>
    constexpr void StaticMatrix<T, Rows, Cols>::transform(UnaryOperation &&op) {
        std::transform(begin(), end(), begin(), std::forward<UnaryOperation>(op));
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <typename BinaryOperation>
    void StaticMatrix<T, Rows, Cols>::transform(const StaticMatrix &other, BinaryOperation &&op) {
        std::transform(begin(), end(), other.begin(), begin(), std::forward<BinaryOperation>(op));
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <typename Operation>
    void StaticMatrix<T, Rows, Cols>::generate(Operation &&op) {
        std::generate(begin(), end(), std::forward<Operation>(op));
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::fill(const value_type &number) {
        std::fill(begin(), end(), number);
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::fill_random(const value_type &left, const value_type &right) {
        using namespace std::chrono;

        std::default_random_engine re(system_clock::now().time_since_epoch().count());
        auto distribution = std::conditional_t<std::is_integral_v<T>,
                std::uniform_int_distribution<T>,
                std::uniform_real_distribution<T>>(left, right);

        generate([&distribution, &re]() {
            return distribution(re);
        });

        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::to_round() {
        transform([](const value_type &item) { return std::round(item); });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    _GLIBCXX23_CONSTEXPR StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::round() const {
        StaticMatrix<T, Rows, Cols> m(*this);
        std::transform(m.begin(), m.end(), m.begin(), [](const auto &item) { return std::round(item); });
        return m;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::to_floor() {
        transform([](const value_type &item) { return std::floor(item); });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    _GLIBCXX23_CONSTEXPR StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::floor() const {
        StaticMatrix<T, Rows, Cols> m(*this);
        std::transform(m.begin(), m.end(),  m.begin(), [](const auto &item) { return std::floor(item); });
        return m;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::to_ceil() {
        transform([](const value_type &item) { return std::ceil(item); });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    _GLIBCXX23_CONSTEXPR StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::ceil() const {
        StaticMatrix<T, Rows, Cols> m(*this);
        std::transform(m.begin(), m.end(), m.begin(), [](const auto &item) { return std::ceil(item); });
        return m;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::to_zero() {
        generate([]() { return value_type{}; });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::zero() const {
        return StaticMatrix<T, Rows, Cols>();
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::to_identity() requires(Rows == Cols) {
        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                (*this)(row, col) = row == col ? value_type{1} : value_type{};

        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::identity() const requires(Rows == Cols) {
        StaticMatrix<T, Rows, Cols> identity;

        constexpr value_type one = value_type{1};

        for (size_type row = 0; row != Rows; ++row)
            for (size_type col = 0; col != Cols; ++col)
                if (row == col)
                    identity(row, col) = one;

        return identity;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::mul(const value_type &value) {
        transform([&value](const auto &item) { return item * value; });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::add(const value_type &value) {
        transform([&value](const auto &item) { return item + value; });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::sub(const value_type &value) {
        transform([&value](const auto &item) { return item - value; });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::div(const value_type &value) {
        transform([&value](const auto &item) { return item / value; });
        return *this;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr typename StaticMatrix<T, Rows, Cols>::value_type StaticMatrix<T, Rows, Cols>::sum() const {
        return std::accumulate(begin(), end(), value_type{});
    }


    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <fundamental U> requires(std::convertible_to<U, T>)
    constexpr StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::mul_by_element(const StaticMatrix<U, Rows, Cols> &rhs) const {
        StaticMatrix<T, Rows, Cols> multpipled;

        for (size_type row = 0; row != Rows; ++row)
            for (size_type col = 0; col != Cols; ++col)
                multpipled(row, col) = (*this)(row, col) * rhs(row, col);

        return multpipled;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <fundamental U> requires(std::convertible_to<U, T>)
    constexpr StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::div_by_element(const StaticMatrix<U, Rows, Cols> &rhs) const {
        StaticMatrix<T, Rows, Cols> division;

        for (size_type row = 0; row != Rows; ++row)
            for (size_type col = 0; col != Cols; ++col)
                division(row, col) = (*this)(row, col) / rhs(row, col);

        return division;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <fundamental U> requires(std::convertible_to<U, T>)
    constexpr StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::add(const StaticMatrix<U, Rows, Cols> &rhs) const {
        StaticMatrix<T, Rows, Cols> addition;

        for (size_type row = 0; row != Rows; ++row)
            for (size_type col = 0; col != Cols; ++col)
                addition(row, col) = (*this)(row, col) + rhs(row, col);

        return addition;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <fundamental U> requires(std::convertible_to<U, T>)
    constexpr StaticMatrix<T, Rows, Cols> StaticMatrix<T, Rows, Cols>::sub(const StaticMatrix<U, Rows, Cols> &rhs) const {
        StaticMatrix<T, Rows, Cols> substraction;

        for (size_type row = 0; row != Rows; ++row)
            for (size_type col = 0; col != Cols; ++col)
                substraction(row, col) = (*this)(row, col) - rhs(row, col);

        return substraction;
    }


    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr StaticMatrix<T, Cols, Rows> StaticMatrix<T, Rows, Cols>::transpose() const {
        StaticMatrix<T, Cols, Rows> transposed;

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                transposed(col, row) = (*this)(row, col);

        return transposed;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    constexpr StaticMatrix<T, Rows - 1, Cols - 1> StaticMatrix<T, Rows, Cols>::minor(size_type row, size_type col) const requires(non_zero_dimension<Rows - 1, Cols - 1>) {
        StaticMatrix<T, Rows - 1, Cols - 1> minored;

        size_type skip_row = 0, skip_col = 0;
        for (size_type r = 0; r != Rows - 1; ++r) {
            if (row == r)
                skip_row = 1;

            skip_col = 0;
            for (size_type c = 0; c != Cols - 1; ++c) {
                if (col == c)
                    skip_col = 1;

                minored(r, c) = (*this)(r + skip_col, c + skip_row);
            }
        }

        return minored;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <fundamental U>
    requires(std::convertible_to<U, T>)
    constexpr std::array<U, Rows * Cols> StaticMatrix<T, Rows, Cols>::to_array() const {
        std::array<U, Rows * Cols> arr;

        size_type current = 0;
        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                arr[current++] = (*this)(row, col);

        return arr;
    }

    template <fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    template <fundamental U>
    requires(std::convertible_to<U, T>)
    constexpr StaticMatrix<U, Rows, Cols> StaticMatrix<T, Rows, Cols>::convert_to() const {
        StaticMatrix<U, Rows, Cols> converted;

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                converted(row, col) = (*this)(row, col);

        return converted;
    }

}

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP
