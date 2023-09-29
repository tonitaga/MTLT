#include "matrix_oop.h"

int main() {
    Matrix m(3, 3);
    m(0, 0) = 0;
    m(0, 1) = 6;
    m(0, 2) = -2;

    m(1, 0) = 3;
    m(1, 1) = 8;
    m(1, 2) = 1;

    m(2, 0) = -4;
    m(2, 1) = 2;
    m(2, 2) = 6;

    auto det = m.Determinant();
    std::cout << det;
}
