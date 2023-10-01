#ifndef MATRIX_LIBRARY_CPP_MATRIX_TPP_
#define MATRIX_LIBRARY_CPP_MATRIX_TPP_

#include <matrix/matrix.h>

#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <algorithm>

namespace ng {
    template <fundamental T>
    constexpr Matrix<T>::Matrix(size_type rows, size_type cols, value_type f)
        : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {
        if (f != value_type{})
            fill(f);
    }

    template <fundamental T>
    constexpr Matrix<T>::Matrix(const Matrix &other)
        : Matrix(other.rows_, other.cols_) {
        std::copy(other.begin(), other.end(), begin());
    }

    template <fundamental T>
    constexpr Matrix<T>::Matrix(const std::vector<std::vector<value_type>> &matrix_vector)
        : Matrix(matrix_vector.size(), matrix_vector[0].size()) {
        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                (*this)(row, col) = matrix_vector[row][col];
    }

    template <fundamental T>
    constexpr Matrix<T>::Matrix(size_type rows, size_type cols, const std::initializer_list<T> &initializer)
        : Matrix(rows, cols) {
        std::copy(initializer.begin(), initializer.end(), begin());
    }

    template <fundamental T>
    template <typename Container>
    requires (std::convertible_to<typename Container::value_type, T>)
    constexpr Matrix<T>::Matrix(size_type rows, size_type cols, const Container &container)
        : Matrix(rows, cols) {
        std::copy(container.begin(), container.end(), begin());
    }

    template <fundamental T>
    Matrix<T> Matrix<T>::identity(size_type rows, size_type cols) {
        Matrix identity(rows, cols);
        identity.to_identity();
        return identity;
    }

    template <fundamental T>
    constexpr Matrix<T>::Matrix(Matrix &&other) noexcept
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
        other.rows_ = other.cols_ = size_type{};
        other.data_ = nullptr;
    }

    template <fundamental T>
    constexpr Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
        if (&other == this)
            return *this;

        Matrix tmp(other);
        *this = std::move(tmp);

        return *this;
    }

    template <fundamental T>
    constexpr Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept {
        if (&other == this)
            return *this;

        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);

        return *this;
    }

    template <fundamental T>
    Matrix<T>::~Matrix() noexcept {
        delete [] data_;
    }

    template <fundamental T>
    typename Matrix<T>::reference Matrix<T>::operator()(size_type row, size_type col) {
        return data_[row * cols_ + col];
    }

    template <fundamental T>
    typename Matrix<T>::const_reference Matrix<T>::operator()(size_type row, size_type col) const {
        return data_[row * cols_ + col];
    }

    template <fundamental T>
    typename Matrix<T>::reference Matrix<T>::at(size_type row, size_type col) {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of range of matrix");

        return (*this)(row, col);
    }

    template <fundamental T>
    typename Matrix<T>::const_reference Matrix<T>::at(size_type row, size_type col) const {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of range of matrix");

        return (*this)(row, col);
    }

    template <fundamental T>
    void Matrix<T>::rows(size_type rows) {
        if (rows_ == rows)
            return;

        Matrix tmp(rows, cols_);
        const size_type min_rows = std::min(rows, rows_);

        for (size_type row = 0; row != min_rows; ++row)
            for (size_type col = 0; col != cols_; ++col)
                tmp(row, col) = (*this)(row, col);

        *this = std::move(tmp);
    }

    template <fundamental T>
    void Matrix<T>::cols(size_type cols) {
        if (cols_ == cols)
            return;

        Matrix tmp(rows_, cols);
        const size_type min_cols = std::min(cols, cols_);

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != min_cols; ++col)
                tmp(row, col) = (*this)(row, col);

        *this = std::move(tmp);
    }

    template <fundamental T>
    void Matrix<T>::resize(size_type rows, size_type cols) {
        if (cols_ == cols and rows_ == rows)
            return;

        Matrix tmp(rows, cols);
        const size_type min_cols = std::min(cols, cols_);
        const size_type min_rows = std::min(rows, rows_);

        for (size_type row = 0; row != min_rows; ++row)
            for (size_type col = 0; col != min_cols; ++col)
                tmp(row, col) = (*this)(row, col);

        *this = std::move(tmp);
    }

    template <fundamental T>
    void Matrix<T>::clear() noexcept {
        rows_ = cols_ = value_type {};
        delete [] data_;
        data_ = nullptr;
    }

    template <fundamental T>
    void Matrix<T>::print(std::ostream &os, MatrixDebugSettings settings) const {
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

    template <fundamental T>
    template <typename UnaryOperation>
    void Matrix<T>::transform(UnaryOperation &&op) {
        std::transform(begin(), end(), begin(), std::forward<UnaryOperation>(op));
    }

    template <fundamental T>
    template <typename BinaryOperation>
    void Matrix<T>::transform(const Matrix &other, BinaryOperation &&op) {
        std::transform(begin(), end(), other.begin(), begin(), std::forward<BinaryOperation>(op));
    }

    template <fundamental T>
    template <typename Operation>
    void Matrix<T>::generate(Operation &&op) {
        std::generate(begin(), end(), std::forward<Operation>(op));
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::mul(const value_type &number) {
        transform([&number](const value_type &item) { return item * number; });
        return *this;
    }

    template <fundamental T>
    template <typename U>
    requires(std::convertible_to<U, T>)
    Matrix<T> &Matrix<T>::mul(const Matrix<U> &rhs) {
        if (cols_ != rhs.rows())
            throw std::logic_error("Can't multiply two matrices because lhs.cols() != rhs.rows()");

        const size_type cols = rhs.cols();
        const size_type rows = rows_;

        Matrix multiplied(rows, cols);
        for (size_type row = 0; row != rows; ++row)
            for (size_type col = 0; col != cols; ++col)
                for (size_type k = 0; k != cols_; ++k)
                    multiplied(row, col) += (*this)(row, k) * rhs(k, col);

        *this = std::move(multiplied);
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::add(const value_type &number) {
        transform([&number](const value_type &item) { return item + number; });
        return *this;
    }


    template <fundamental T>
    template <typename U>
    requires(std::convertible_to<U, T>)
    Matrix<T> &Matrix<T>::add(const Matrix<U> &rhs) {
        if (rhs.rows() != rows_ or rhs.cols() != cols_)
            throw std::logic_error("Can't add different sized matrices");

        transform(rhs, [](const T &lhs, const U &rhs) { return lhs + rhs; });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::sub(const value_type &number) {
        transform([&number](const value_type &item) { return item - number; });
        return *this;
    }

    template <fundamental T>
    template <typename U>
    requires(std::convertible_to<U, T>)
    Matrix<T> &Matrix<T>::sub(const Matrix<U> &rhs) {
        if (rhs.rows() != rows_ or rhs.cols() != cols_)
            throw std::logic_error("Can't add different sized matrices");

        transform(rhs, [](const T &lhs, const U &rhs) { return lhs - rhs; });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::div(const value_type &number) {
        if (std::is_integral_v<T> and number == 0)
            throw std::logic_error("Dividing by zero");

        transform([&number](const value_type &item) { return item / number; });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::round() {
        transform([](const value_type &item) { return std::round(item); });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::floor() {
        transform([](const value_type &item) { return std::floor(item); });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::ceil() {
        transform([](const value_type &item) { return std::ceil(item); });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::zero() {
        generate([]() { return value_type{}; });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::fill(const value_type &number) {
        generate([&number]() { return number; });
        return *this;
    }

    template <fundamental T>
    Matrix<T> &Matrix<T>::fill_random(const value_type &left, const value_type &right) {
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

    template <fundamental T>
    Matrix<T> &Matrix<T>::to_identity() {
        if (rows_ != cols_)
            throw std::logic_error("Only square matrices can be identity");

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                (*this)(row, col) = row == col ? value_type{1} : value_type{};

        return *this;
    }

    template <fundamental T>
    typename Matrix<T>::value_type Matrix<T>::sum() const {
        return std::accumulate(begin(), end(), value_type{});
    }

    template <fundamental T>
    Matrix<T> Matrix<T>::transpose() const {
        Matrix transposed(cols_, rows_);

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                transposed(col, row) = (*this)(row, col);

        return transposed;
    }

    template <fundamental T>
    Matrix<T> Matrix<T>::minor(size_type row, size_type col) const {
        Matrix minor(rows() - 1, cols() - 1);

        size_type skip_row = 0, skip_col = 0;
        for (size_type r = 0; r != minor.rows_; ++r) {
            if (row == r)
                skip_row = 1;

            skip_col = 0;
            for (size_type c = 0; c != minor.cols_; ++c) {
                if (col == c)
                    skip_col = 1;

                minor(r, c) = (*this)(r + skip_row, c + skip_col);
            }
        }

        return minor;
    }

    template <fundamental T>
    typename Matrix<T>::value_type Matrix<T>::minor_item(size_type row, size_type col) const {
        return minor(row, col).determinant();
    }

    template <fundamental T>
    typename Matrix<T>::value_type Matrix<T>::determinant() const {
        if (rows_ != cols_)
            throw std::logic_error("Determinant can be found only for square matrices");

        value_type determinant_value {};
        int sign = 1;

        if (rows_ == 1 and cols_ == 1)
            determinant_value = (*this)(0, 0);
        else if (rows_ == 2 and cols_ == 2)
            determinant_value = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
        else {
            for (size_type col = 0; col != cols_; ++col) {
                Matrix minored = minor(0, col);
                determinant_value += sign * (*this)(0, col) * minored.determinant();
                sign = -sign;
            }
        }

        return determinant_value;
    }

    template <fundamental T>
    typename Matrix<T>::value_type Matrix<T>::trace() const {
        if (rows_ != cols_)
            throw std::logic_error("Can't find trace for non square matrices");

        value_type tr {};
        for (size_type i = 0; i != rows_; ++i)
            tr += (*this)(i, i);
        return tr;
    }

    template <fundamental T>
    Matrix<T> Matrix<T>::calc_complements() const {
        if (rows_ != cols_)
            throw std::logic_error("Complements matrix can be found only for square matrices");

        Matrix<T> complements(rows_, cols_);

        for (size_type row = 0; row != rows_; ++row) {
            for (size_type col = 0; col != cols_; ++col) {
                complements(row, col) = minor_item(row, col);

                if ((row + col) % 2 != 0)
                    complements(row, col) = -complements(row, col);
            }
        }

        return complements;
    }

    template <fundamental T>
    Matrix<T> Matrix<T>::inverse() const {
        value_type det = determinant();

        if (det == value_type{})
            throw std::logic_error("Can't found inverse matrix because determinant is zero");

        return calc_complements().transpose().mul(1 / det);
    }

    template <fundamental T>
    bool Matrix<T>::equal_to(const Matrix &rhs) const {
        if (rhs.rows() != rows_ or rhs.cols() != cols_)
            throw std::logic_error("Can't add different sized matrices");

        T epsilon;
        constexpr bool is_bool = std::is_same_v<bool, T>;

        if constexpr (!is_bool) {
            epsilon = MatrixEpsilon<T>::epsilon;
        }

        bool equal = true;
        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col) {
                if constexpr (is_bool) {
                    if ((*this)(row, col) != rhs(row, col))
                        equal = false;
                } else {
                    if (fabs((*this)(row, col) - rhs(row, col)) > epsilon)
                        equal = false;
                }

                if (!equal) break;
            }

        return equal;
    }

    template <fundamental T>
    template <typename ConvertType>
    Matrix<ConvertType> Matrix<T>::convert_to() const {
        Matrix<ConvertType> convert(rows_, cols_);
        std::copy(begin(), end(), convert.begin());
        return convert;
    }

    template <fundamental T>
    std::vector<typename Matrix<T>::value_type> Matrix<T>::convert_to_vector() const {
        std::vector<value_type> v(rows_ * cols_);
        std::copy(begin(), end(), v.begin());
        return v;
    }

    template <fundamental T>
    std::vector<std::vector<typename Matrix<T>::value_type>> Matrix<T>::convert_to_matrix_vector() const {
        std::vector<std::vector<value_type>> v(rows_, std::vector<value_type>(cols_));

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                v[row][col] = (*this)(row, col);

        return v;
    }

    template <fundamental T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs) {
        rhs.print(out);
        return out;
    }

    template <typename T, typename U>
    Matrix<T> &operator +=(Matrix<T> &lhs, const Matrix<U> &rhs) {
        lhs.add(rhs);
        return lhs;
    }

    template <typename T, typename U>
    Matrix<T> &operator -=(Matrix<T> &lhs, const Matrix<U> &rhs) {
        lhs.sub(rhs);
        return lhs;
    }

    template <typename T, typename U>
    Matrix<T> &operator *=(Matrix<T> &lhs, const Matrix<U> &rhs) {
        lhs.mul(rhs);
        return lhs;
    }

    template <fundamental T>
    Matrix<T> &operator +=(Matrix<T> &lhs, const T &value) {
        lhs.add(value);
        return lhs;
    }

    template <fundamental T>
    Matrix<T> &operator -=(Matrix<T> &lhs, const T &value) {
        lhs.sub(value);
        return lhs;
    }

    template <fundamental T>
    Matrix<T> &operator *=(Matrix<T> &lhs, const T &value) {
        lhs.mul(value);
        return lhs;
    }

    template <fundamental T>
    Matrix<T> &operator /=(Matrix<T> &lhs, const T &value) {
        lhs.div(value);
        return lhs;
    }

    template <typename T, typename U>
    Matrix<T> operator +(const Matrix<T> &lhs, const Matrix<U> &rhs) {
        Matrix<T> result(lhs);
        result += rhs;
        return result;
    }

    template <typename T, typename U>
    Matrix<T> operator -(const Matrix<T> &lhs, const Matrix<U> &rhs) {
        Matrix<T> result(lhs);
        result -= rhs;
        return result;
    }

    template <typename T, typename U>
    Matrix<T> operator *(const Matrix<T> &lhs, const Matrix<U> &rhs) {
        Matrix<T> result(lhs);
        result *= rhs;
        return result;
    }

    template <fundamental T>
    Matrix<T> operator +(const Matrix<T> &lhs, const T &value) {
        Matrix<T> result(lhs);
        result += value;
        return result;
    }

    template <fundamental T>
    Matrix<T> operator -(const Matrix<T> &lhs, const T &value) {
        Matrix<T> result(lhs);
        result -= value;
        return result;
    }

    template <fundamental T>
    Matrix<T> operator *(const Matrix<T> &lhs, const T &value) {
        Matrix<T> result(lhs);
        result *= value;
        return result;
    }

    template <fundamental T>
    Matrix<T> operator *(const T &value, const Matrix<T> &lhs) {
        return lhs * value;
    }

    template <fundamental T>
    Matrix<T> operator /(const Matrix<T> &lhs, const T &value) {
        Matrix<T> result(lhs);
        result /= value;
        return result;
    }

    template <fundamental T>
    bool inline operator ==(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        return lhs.equal_to(rhs);
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_TPP_
