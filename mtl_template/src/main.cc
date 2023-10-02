#include <matrix/matrix.h>
#include <matrix/static_matrix.h>

int main() {
    mtl::static_matrix<double, 4, 4> matrix1;
    mtl::matrix<double> matrix2(4, 4);

    mtl::print(matrix1, matrix2);
    return EXIT_SUCCESS;
}
