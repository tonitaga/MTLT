#ifndef MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H
#define MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H

namespace ng {
    struct MatrixDebugSettings {
        int width = 0, precision = 0;
        char separator = ' ', end = '\n';
        bool is_double_end = false;
    };

    constexpr MatrixDebugSettings default_debug = {
            .width = 3,
            .precision = 3,
            .separator = ' ',
            .end = '\n',
            .is_double_end = false
    };
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H
