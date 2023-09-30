#include <iostream>
#include <vector>
#include <array>
#include "static_matrix"
#include "matrix.h"

using namespace ng;

int main() {
    Matrix<int> matrix(3, 3, {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    });

    std::vector<int> b;
    auto r = b.rbegin();

    return EXIT_SUCCESS;
}