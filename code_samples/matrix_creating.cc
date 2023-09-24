#include "matrix"

using namespace ng;

int main() {
    // Empty
    Matrix<int> m1;

    // Rows Cols
    Matrix<int> m2(5, 5);

    // Square
    Matrix<int> m3(5);

    // Rows Cols Filled
    Matrix<int> m4(5, 5, 1);

    // Identity
    Matrix<int> m5 = Matrix<int>::identity(5, 5);

    // Random filled
    Matrix<int> m6 = Matrix<int>(5, 5).fill_random(0, 5);

    // Copy construction matrix
    Matrix<int> m7 = m6;

    // Move construction matrix
    Matrix<int> m8 = std::move(m7);

    // Copy assignment matrix
    m1 = m2;

    // Move assignment matrix
    m1 = std::move(m2);

    // Creating from other type of matrix
    Matrix<int> m9 = Matrix<float>(5, 5);

    return EXIT_SUCCESS;
}