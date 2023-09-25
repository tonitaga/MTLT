#include <iostream>
#include <vector>

#include "matrix"

using namespace ng;

int main() {
    std::vector<int> vec {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };

    Matrix<int> matrix(3, 3, vec);
    matrix.print(std::cout);

    auto transformed_matrix = (matrix * 4 + 2 - 1).convert_to<double>() / 4.;

    transformed_matrix.print(std::cout);
    matrix.print(std::cout);
}