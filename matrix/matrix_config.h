#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_CONFIG_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_CONFIG_H_

#include <iostream>

#ifndef MATRIX_CXX17_CONSTEXPR
    #if __cplusplus >= 201703L
    #define MATRIX_CXX17_CONSTEXPR constexpr
    #else
    #define MATRIX_CXX17_CONSTEXPR
    #endif
#endif

#ifndef MATRIX_CXX20_CONSTEXPR
#if __cplusplus > 201703L
    #define MATRIX_CXX20_CONSTEXPR constexpr
    #else
    #define MATRIX_CXX20_CONSTEXPR
    #endif
#endif

#ifndef MATRIX_CXX23_CONSTEXPR
#if __cplusplus > 202002L
    #define MATRIX_CXX23_CONSTEXPR constexpr
    #else
    #define MATRIX_CXX23_CONSTEXPR
    #endif
#endif

#ifndef MATRIX_CXX17_NODISCARD
    #if __cplusplus >= 201703L
    #define MATRIX_CXX17_NODISCARD [[nodiscard]]
    #else
    #define MATRIX_CXX17_NODISCARD
    #endif
#endif

#ifndef MATRIX_CXX17_UNUSED
    #if __cplusplus >= 201703L
    #define MATRIX_CXX17_UNUSED [[maybe_unused]]
    #else
    #define MATRIX_CXX17_UNUSED
    #endif
#endif

#endif //MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_CONFIG_H_
