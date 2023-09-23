#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    IMatrix matrix(10, 10);

    matrix.add(10);
    std::cout << matrix << std::endl;

    matrix.substract(2);
    std::cout << matrix << std::endl;

    matrix.multiply(3);
    std::cout << matrix << std::endl;

    matrix.divide(3);
    std::cout << matrix << std::endl;

    return EXIT_SUCCESS;
}