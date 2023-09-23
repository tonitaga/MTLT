#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    FMatrix matrix(10, 10);

    float value_start = 0;
    matrix.transform([&](float) {
        value_start += 0.13;
        return value_start;
    });

    std::cout << matrix << std::endl;

    FMatrix copy = std::move(matrix);
    std::cout << copy << std::endl;

    return EXIT_SUCCESS;
}