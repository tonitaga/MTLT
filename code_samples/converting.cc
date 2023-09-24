#include "matrix"

using namespace ng;

int main() {
    Matrix<int> m1(5, 5);

    // to row-vector
    auto row_vector = m1.convert_to_vector();

    // to matrix-vector
    auto matrix_vector = m1.convert_to_matrix_vector();

    // to matrix other type
    auto matrix = m1.convert_to<float>();

    return EXIT_SUCCESS;
}