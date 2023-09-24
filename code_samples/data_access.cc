#include "matrix"

using namespace ng;

int main() {
    Matrix<int> m1(5, 5);

    // rows cols
    m1.rows(), m1.cols();

    // row col item
    m1(0, 0), m1.at(0, 0);

    // change rows cols of matrix
    m1.rows(6), m1.cols(6);

    // resize matrix
    m1.resize(6, 6);

    // sum of elements
    m1.sum();

    return EXIT_SUCCESS;
}