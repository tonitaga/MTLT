#include <iostream>
#include <vector>

#include <matrix.h>

int main() {
    std::cout << "Hello world!" << std::endl;

    ng::Matrix<int> matrix(5, 5);
    *matrix.begin() = 5;

    std::cout << "Matrix1: ";
    for (auto item : matrix) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    auto copyied = std::move(matrix);

    std::cout << "Matrix2: ";
    for (const auto &item : copyied) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    std::cout << "Matrix1: ";
    for (auto item : matrix) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}