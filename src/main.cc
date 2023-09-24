#include <iostream>
#include <vector>

#include "matrix"

int main() {
    ng::Matrix<int> matrix = ng::Matrix<int>(3, 3).fill_random(0, 5);

    auto begin = matrix.begin();
    auto end = matrix.end();

    auto rbegin = matrix.rbegin();
    auto rend = matrix.rend();

    while (begin != end) {
        std::cout << *begin << ' ';
        ++begin;
    }

    std::cout << std::endl;

    while (rbegin != rend) {
        std::cout << *rbegin << ' ';
        ++rbegin;
    }

    std::cout << std::endl;
}