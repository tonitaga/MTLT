#include "matrix"
#include "static_matrix"

using namespace ng;

struct S{};

int main() {
    Matrix<int> dynamic_matrix(3, 3);
    StaticMatrix<int, 3, 3> static_matrix;

    using size_type = typename Matrix<int>::size_type;

    //
    // Matrix and StaticMatrix classes supports different ways to print your matrix
    //

    // Default printing using rows and cols sizes
    for (size_type r = 0; r != dynamic_matrix.rows(); ++r) {
        for (size_type c = 0; c != dynamic_matrix.cols(); ++c) {
            std::cout << dynamic_matrix(r, c) << ' ';
            std::cout << static_matrix(r, c) << ' ';
        }
        std::cout << '\n';
    }

    // Using iterators in range-based-for (Print matrix in a row style)
    for (auto item : dynamic_matrix)
        std::cout << item;

    for (auto item : static_matrix)
        std::cout << item;

    // Using special method of both classes
    dynamic_matrix.print(std::cout);
    static_matrix.print(std::cout);

    // Using overloaded operator << of both classes
    std::cout << dynamic_matrix << '\n';
    std::cout << static_matrix << '\n';

    // Also print method supports print/debug settings
    MatrixDebugSettings s {
            .width = 6,
            .precision = 12,
            .separator = '\t',
            .end = '\t',
            .is_double_end = true
    };
    dynamic_matrix.print(std::cout, s);
    static_matrix.print(std::cout, s);

    // Variadic template function
    // Variadic params must be printable with std::ostream
    // Guard by concept 'printable'
    print(dynamic_matrix, static_matrix);
}