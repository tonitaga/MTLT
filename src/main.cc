#include <iostream>
#include <vector>

#include "matrix"

int main() {
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution dist(4, 5);

    const ng::DMatrix cm1 = ng::DMatrix(5, 5).fill_random(4, 5).round();

    std::cout << cm1 << std::endl;
    std::cout << "sum of elements: " << cm1.sum() << std::endl;

    return EXIT_SUCCESS;
}