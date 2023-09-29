#include "matrix"
#include "static_matrix"

using namespace ng;

int main() {
    //
    // Matrix classes supports different ways of creation
    //

    // Empty Dynamic matrix
    Matrix<int> matrix1;

    // Rows Cols matrix
    Matrix<int> matrix2(3, 3);
    StaticMatrix<int, 3, 3> matrix3;

    // Square matrix
    Matrix<int> matrix4(5);
    SquareMatrix<int, 5> matrix5;

    // Filled matrix
    Matrix<int> matrix6(5, 5, 1);
    StaticMatrix<int, 2, 4> matrix7(1);

    // Identity matrix
    Matrix matrix8 = Matrix<int>::identity(5, 5);
    StaticMatrix matrix9 = StaticMatrix<int, 5, 5>().identity();

    // Construction from container
    std::vector<int> vec1 {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    Matrix<int> matrix10(3, 3, vec1);
    StaticMatrix<int, 3, 3> matrix11(vec1);

    // Static matrix creation in compile(non-compile) time using array
    StaticMatrix<int, 3, 3> matrix12({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    constexpr StaticMatrix<int, 3, 3> matrix13({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    // Dynamic matrix creation from matrix vector
    std::vector<std::vector<int>> vec2 {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    Matrix<int> matrix14(vec2);

    return EXIT_SUCCESS;
}