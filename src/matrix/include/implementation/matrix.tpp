#ifndef MATRIX_LIBRARY_CPP_MATRIX_TPP_
#define MATRIX_LIBRARY_CPP_MATRIX_TPP_

#include "matrix.h"

#include <algorithm>

namespace ng {
    template <typename T>
    constexpr Matrix<T>::Matrix(const Matrix &other)
        : Matrix(other.rows_, other.cols_) {
        std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    }

    template <typename T>
    constexpr Matrix<T>::Matrix(Matrix &&other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);
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
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_TPP_
