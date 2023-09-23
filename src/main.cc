#include <iostream>
#include <vector>

#include <matrix.h>

int main() {
    std::cout << "Hello world!" << std::endl;

    ng::Matrix<float> matrix(10, 10);
    float value_start = 0.13;
    for (auto &item : matrix) {
        item = value_start;
        value_start += 0.1;
    }

    matrix.print(std::cout);

    auto copyied = std::move(matrix);
    copyied.print(std::cout);

    matrix.print(std::cout);



    return EXIT_SUCCESS;
}