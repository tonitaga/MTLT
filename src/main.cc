#include <iostream>
#include <vector>

#include <matrix.h>

int main() {
    std::cout << "Hello world!" << std::endl;

    ng::Matrix<int> matrix(5, 5);
    *matrix.begin() = 5;

    for (auto item : matrix) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    auto copyied = matrix;

    for (const auto &item : copyied) {
        std::cout << item << ' ';
    }

    return EXIT_SUCCESS;
}