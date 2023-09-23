#ifndef MATRIX_LIBRARY_CPP_MATRIX_TPP_
#define MATRIX_LIBRARY_CPP_MATRIX_TPP_

#include "matrix.h"

#include <algorithm>

namespace ng {
    template <typename T>
    Matrix<T>::Matrix(const Matrix &other)
        : Matrix(other.rows_, other.cols_) {
        std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix &&other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
        if (&other == this)
            return *this;

        Matrix tmp(other);
        *this = std::move(tmp);

        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept {
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
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_TPP_
