#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    FMatrix matrix(5, 5);

    matrix.add(0.11);
    std::cout << matrix << std::endl;

    matrix.sub(0.05);
    std::cout << matrix << std::endl;

    matrix.mul(1.15);
    std::cout << matrix << std::endl;

    matrix.div(2.2);
    std::cout << matrix << std::endl;

    matrix.ceil();
    std::cout << matrix << std::endl;

    matrix.sub(0.1);
    std::cout << matrix << std::endl;

    matrix.round();
    std::cout << matrix << std::endl;

    matrix.sub(0.1);
    std::cout << matrix << std::endl;

    matrix.floor();
    std::cout << matrix << std::endl;

    matrix.fill(1.5);
    std::cout << matrix << std::endl;

    matrix.fill_random(5, 6);
    std::cout << matrix << std::endl;

    matrix.resize(6, 6);

    std::cout << matrix << std::endl;

    return EXIT_SUCCESS;
}