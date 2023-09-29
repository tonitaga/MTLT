#ifndef MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H
#define MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H

namespace ng {
    template <typename T>
    concept fundamental = std::is_fundamental_v<T>;

    template <std::size_t Rows, std::size_t Cols>
    concept non_zero_dimension = requires { Rows != 0 and Cols != 0; };

    template <typename T>
    concept printable = requires(T t) {
        std::cout << t;
    };

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

    template <typename T> struct MatrixEpsilon {};

    template <> struct MatrixEpsilon<char> { static constexpr char epsilon = 0; };

    template <> struct MatrixEpsilon<int> { static constexpr int epsilon = 0; };
    template <> struct MatrixEpsilon<long int> { static constexpr long int epsilon = 0; };
    template <> struct MatrixEpsilon<long long int> { static constexpr long long int epsilon = 0; };

    template <> struct MatrixEpsilon<unsigned> { static constexpr unsigned epsilon = 0; };
    template <> struct MatrixEpsilon<long unsigned> { static constexpr long unsigned epsilon = 0; };
    template <> struct MatrixEpsilon<long long unsigned> { static constexpr long long unsigned epsilon = 0; };

    template <> struct MatrixEpsilon<short> { static constexpr short epsilon = 0; };

    template <> struct MatrixEpsilon<float> { static constexpr float epsilon = 1e-6; };

    template <> struct MatrixEpsilon<double> { static constexpr double epsilon = 1e-6; };
    template <> struct MatrixEpsilon<long double> { static constexpr long double epsilon = 1e-6; };

    template <typename Object>
    void print(Object &&object) requires printable<Object> {
        std::cout << object << '\n';
    }

    template <typename Head, typename ...Tail>
    void print(Head &&head, Tail &&...tail) {
        print(std::forward<Head>(head));
        print(std::forward<Tail>(tail)...);
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_DEBUG_H
