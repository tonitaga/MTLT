#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    IMatrix m1(4, 5); m1.fill_random(0, 5);
    IMatrix m2(5, 4); m2.fill_random(0, 5);

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    m1.mul(m2);

    std::cout << m1 << std::endl;

    return EXIT_SUCCESS;
}