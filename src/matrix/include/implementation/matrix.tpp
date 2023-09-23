#ifndef MATRIX_LIBRARY_CPP_MATRIX_TPP_
#define MATRIX_LIBRARY_CPP_MATRIX_TPP_

#include "matrix.h"

#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

namespace ng {
    template <typename T>
    constexpr Matrix<T>::Matrix(size_type rows, size_type cols, value_type f)
        : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {
        fill(f);
    };

    template <typename T>
    constexpr Matrix<T>::Matrix(const Matrix &other)
        : Matrix(other.rows_, other.cols_) {
        std::copy(other.begin(), other.end(), begin());
    }

    template <typename T>
    template <typename U>
    constexpr Matrix<T>::Matrix(const Matrix<U> &other)
        : Matrix(other.rows(), other.cols()) {
        std::copy(other.begin(), other.end(), begin());
    }

    template <typename T>
    Matrix<T> Matrix<T>::identity(size_type rows, size_type cols) {
        Matrix identity(rows, cols);
        identity.to_identity();
        return identity;
    }

    template <typename T>
    constexpr Matrix<T>::Matrix(Matrix &&other) noexcept
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
        other.rows_ = other.cols_ = size_type{};
        other.data_ = nullptr;
    }

    template <typename T>
    constexpr Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
        if (&other == this)
            return *this;

        Matrix tmp(other);
        *this = std::move(tmp);

        return *this;
    }

    template <typename T>
    constexpr Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept {
        if (&other == this)
            return *this;

        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);

        return *this;
    }

    template <typename T>
    Matrix<T>::~Matrix() noexcept {
        delete [] data_;
    }

    template <typename T>
    typename Matrix<T>::reference Matrix<T>::operator()(size_type row, size_type col) {
        return data_[row * cols_ + col];
    }

    template <typename T>
    typename Matrix<T>::const_reference Matrix<T>::operator()(size_type row, size_type col) const {
        return data_[row * cols_ + col];
    }

    template <typename T>
    typename Matrix<T>::reference Matrix<T>::at(size_type row, size_type col) {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of range of matrix");

        return (*this)(row, col);
    }

    template <typename T>
    typename Matrix<T>::const_reference Matrix<T>::at(size_type row, size_type col) const {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of range of matrix");

        return (*this)(row, col);
    }

    template <typename T>
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

    template <typename T>
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

    template <typename T>
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

    template <typename T>
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

    template <typename T>
    template <typename UnaryOperation>
    void Matrix<T>::transform(UnaryOperation &&op) {
        std::transform(begin(), end(), begin(), std::forward<UnaryOperation>(op));
    }

    template <typename T>
    template <typename BinaryOperation>
    void Matrix<T>::transform(const Matrix &other, BinaryOperation &&op) {
        std::transform(begin(), end(), other.begin(), begin(), std::forward<BinaryOperation>(op));
    }

    template <typename T>
    template <typename Operation>
    void Matrix<T>::generate(Operation &&op) {
        std::generate(begin(), end(), std::forward<Operation>(op));
    }

    template <typename T>
    void Matrix<T>::mul(const value_type &number) {
        transform([&number](const value_type &item) {
           return item * number;
        });
    }

    template <typename T>
    void Matrix<T>::add(const value_type &number) {
        transform([&number](const value_type &item) {
            return item + number;
        });
    }

    template <typename T>
    void Matrix<T>::sub(const value_type &number) {
        transform([&number](const value_type &item) {
            return item - number;
        });
    }

    template <typename T>
    void Matrix<T>::div(const value_type &number) {
        transform([&number](const value_type &item) {
            return item / number;
        });
    }

    template <typename T>
    void Matrix<T>::round() {
        transform([](const value_type &item) {
           return std::round(item);
        });
    }

    template <typename T>
    void Matrix<T>::floor() {
        transform([](const value_type &item) {
            return std::floor(item);
        });
    }

    template <typename T>
    void Matrix<T>::ceil() {
        transform([](const value_type &item) {
            return std::ceil(item);
        });
    }

    template <typename T>
    void Matrix<T>::zero() {
        generate([]() { return value_type{}; });
    }

    template <typename T>
    void Matrix<T>::fill(const value_type &number) {
        generate([&number]() { return number; });
    }

    template <typename T>
    void Matrix<T>::fill_random(const value_type &left, const value_type &right) {
        using namespace std::chrono;

        std::default_random_engine re(system_clock::now().time_since_epoch().count());
        auto distribution = std::conditional_t<std::is_integral_v<T>,
                                               std::uniform_int_distribution<T>,
                                               std::uniform_real_distribution<T>>(left, right);

        generate([&distribution, &re]() {
            return distribution(re);
        });
    }

    template <typename T>
    void Matrix<T>::to_identity() {
        if (rows_ != cols_)
            throw std::logic_error("Only square matrices can be identity");

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                (*this)(row, col) = row == col ? value_type{1} : value_type{};
    }

    template <typename T>
    template <typename ConvertType>
    Matrix<ConvertType> Matrix<T>::convert_to() const {
        Matrix<ConvertType> convert(rows_, cols_);
        std::copy(begin(), end(), convert.begin());
        return convert;
    }

    template <typename T>
    std::vector<typename Matrix<T>::value_type> Matrix<T>::convert_to_vector() const {
        std::vector<value_type> v(rows_ * cols_);
        std::copy(begin(), end(), v.begin());
        return v;
    }

    template <typename T>
    std::vector<std::vector<typename Matrix<T>::value_type>> Matrix<T>::convert_to_matrix_vector() const {
        std::vector<std::vector<value_type>> v(rows_, std::vector<value_type>(cols_));

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                v[row][col] = (*this)(row, col);

        return v;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs) {
        rhs.print(out);
        return out;
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_TPP_
