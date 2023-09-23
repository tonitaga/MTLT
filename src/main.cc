#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    FMatrix matrix(5, 5);
    matrix.fill_random(1, 9);

    std::cout << matrix << std::endl;

    matrix.mul(2);

    std::cout << matrix << std::endl;

    matrix.div(2);

    std::cout << matrix << std::endl;

    try {
        matrix.div(0);
        std::cout << matrix << std::endl;
    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}