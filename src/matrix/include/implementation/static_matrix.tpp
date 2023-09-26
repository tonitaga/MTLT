#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP

#include "static_matrix.h"

namespace ng {
    template<typename T, std::size_t Rows, std::size_t Cols>
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(value_type fill) noexcept {
        std::fill(begin(), end(), fill);
    }
}

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP
