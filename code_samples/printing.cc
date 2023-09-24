#include "matrix"

using namespace ng;

int main() {
    Matrix<int> m1(5, 5);

    // default printing
    for (std::size_t row = 0; row != m1.rows(); ++row) {
        for (std::size_t col = 0; col != m1.cols(); ++col) {
            std::cout << m1(row, col) << ' ';
        }
        std::cout << std::endl;
    }

    // printing row-type
    for (auto item : m1)
        std::cout << item << ' ';
    std::cout << std::endl;

    // public method of Matrix class
    m1.print(std::cout);

    // using overloading operator <<
    std::cout << m1 << std::endl;

    // print method supports print settings
    MatrixDebugSettings settings {
        .width = 6,
        .precision = 12,
        .separator = ' ',
        .end = '\n',
        .is_double_end = false
    };
    m1.print(std::cout, settings);

    return EXIT_SUCCESS;
}