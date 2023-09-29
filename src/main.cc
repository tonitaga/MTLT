#include <iostream>
#include <vector>
#include <array>
#include "static_matrix"
#include "matrix.h"

using namespace ng;

int main() {
    constexpr Matrix3x3<int> matrix({
       0, 6, -2,
       3, 8, 1,
       -4, 2, 6
    });

    constexpr StaticMatrix transposed = matrix.transpose();
    print(transposed);

    constexpr int sum = matrix.sum();
    constexpr int determinant1 = matrix.determinant();
    constexpr int minor_item00 = matrix.minor_item(0, 0);

    constexpr StaticMatrix complements = matrix.calc_complements();
    constexpr StaticMatrix inverse = matrix.convert_to<double>().inverse();

    print(inverse);


    return EXIT_SUCCESS;
}