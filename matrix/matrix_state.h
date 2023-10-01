#ifndef MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H
#define MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H

#include <iostream>

namespace ng {
#if __cplusplus > 201703L
    template <typename T>
    concept fundamental = std::is_fundamental_v<T>;

    template <std::size_t Rows, std::size_t Cols>
    concept non_zero_dimension = requires { Rows != 0 and Cols != 0; };

    template <typename T>
    concept printable = requires(T t, std::ostream os) {
        os << t;
    };
#endif

    struct matrix_debug_settings {
        static int width;
        static int precision;
        static char separator;
        static char end;
        static bool is_double_end;
    };

    template <typename T> struct matrix_epsilon {
        static constexpr T epsilon = T{};
    };

    template <> struct matrix_epsilon<char> { static constexpr char epsilon = 0; };
    template <> struct matrix_epsilon<int> { static constexpr int epsilon = 0; };
    template <> struct matrix_epsilon<long int> { static constexpr long int epsilon = 0; };
    template <> struct matrix_epsilon<long long int> { static constexpr long long int epsilon = 0; };
    template <> struct matrix_epsilon<unsigned> { static constexpr unsigned epsilon = 0; };
    template <> struct matrix_epsilon<long unsigned> { static constexpr long unsigned epsilon = 0; };
    template <> struct matrix_epsilon<long long unsigned> { static constexpr long long unsigned epsilon = 0; };
    template <> struct matrix_epsilon<short> { static constexpr short epsilon = 0; };
    template <> struct matrix_epsilon<float> { static constexpr float epsilon = 1e-6; };
    template <> struct matrix_epsilon<double> { static constexpr double epsilon = 1e-6; };
    template <> struct matrix_epsilon<long double> { static constexpr long double epsilon = 1e-6; };

#if __cplusplus > 201703L
    template <typename Object>
    void print(Object &&object) requires printable<Object> {
#else
    template <typename Object>
    void print(Object &&object) {
#endif
        std::cout << object << '\n';
    }

    template <typename Head, typename ...Tail>
    void print(Head &&head, Tail &&...tail) {
        print(std::forward<Head>(head));
        print(std::forward<Tail>(tail)...);
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H
