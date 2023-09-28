#include <iostream>
#include <vector>
#include <array>
#include "static_matrix"

using namespace ng;

int main() {
    constexpr StaticMatrix<int, 3, 3> matrix1({
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    });

    constexpr int sum = matrix1.sum();

    constexpr StaticMatrix matrix1_identity = matrix1.identity();
    constexpr int identity_sum = matrix1_identity.sum();

    matrix1_identity.print();

    return EXIT_SUCCESS;
}