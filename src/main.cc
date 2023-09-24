#include <iostream>
#include <vector>

#include "matrix"

int main() {
    std::Matrix<int> matrix(5, 5);
    matrix.fill_random(0, 5);
    std::cout << matrix << std::endl;

    std::Matrix<unsigned> matrix2(5, 5);
    matrix2.fill_random(0, 5);
    std::cout << matrix2 << std::endl;

    std::cout << matrix << std::endl;

    auto result = matrix * 2;

    return EXIT_SUCCESS;
}