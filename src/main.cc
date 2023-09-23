#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    FMatrix matrix(10, 10);

    float value_start = 0.13;
    for (auto &item : matrix) {
        item = value_start;
        value_start += 0.1;
    }

    std::cout << matrix << std::endl;

    FMatrix copy = std::move(matrix);
    std::cout << copy << std::endl;

    return EXIT_SUCCESS;
}