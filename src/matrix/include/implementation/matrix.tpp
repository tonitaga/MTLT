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
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_TPP_
