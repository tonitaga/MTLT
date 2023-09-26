#include <iostream>
#include <vector>
#include "static_matrix"

using namespace ng;

int main() {
    std::vector<int> vector1 {
        1, 2,
        2, 1,
    };

    StaticMatrix<bool, 2, 2> matrix1(vector1);
    matrix1.print();

    return EXIT_SUCCESS;
}