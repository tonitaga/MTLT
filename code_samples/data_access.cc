#include "matrix"
#include "static_matrix"

using namespace ng;

int main() {
    Matrix<int> dynamic_matrix(3, 3);
    Matrix3x3<int> static_matrix;

    // Rows Cols Size methods
    // Size is Rows * Cols
    dynamic_matrix.rows(), dynamic_matrix.cols(), dynamic_matrix.size();
    static_matrix.rows(), static_matrix.cols(), static_matrix.size();

    // Elements access
    dynamic_matrix(0, 0), static_matrix(0, 0);

    // Sum of elements
    dynamic_matrix.sum(), static_matrix.sum();

    return EXIT_SUCCESS;
}