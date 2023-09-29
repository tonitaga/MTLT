#include "matrix"
#include "static_matrix"

#include <set>

using namespace ng;

int main() {
    //
    //  Converting of Matrix classes supported different ways
    //

    // Dynamic matrix to static
    {
        Matrix<int> dynamic(3, 3);
        StaticMatrix<int, 3, 3> static_matrix(dynamic);
    }

    // Static matrix to dynamic
    {
        StaticMatrix<int, 3, 3> static_matrix;
        Matrix<int> dynamic(3, 3, static_matrix);
    }

    // Converting to other type
    {
        Matrix<float> float_matrix = Matrix<int>(3, 3).convert_to<float>();
        StaticMatrix<float, 3, 3> float_static_matrix = StaticMatrix<int, 3, 3>().convert_to<float>();
    }

    // Converting to vector of dynamic matrix
    {
        Matrix<int> matrix(3, 3, 1);

        std::vector<int> vector1(matrix.begin(), matrix.end());
        std::vector vector2 = matrix.convert_to_vector();
        std::vector<std::vector<int>> vector3 = matrix.convert_to_matrix_vector();
    }

    // Converting to array of static matrix
    {
        // More useful in compile time
        StaticMatrix<int, 3, 3> matrix;
        std::array array1 = matrix.to_array();
        std::array array2 = matrix.to_array<double>();
    }

    // Construction of any container using matrix interators
    {
        Matrix<int> dynamic_matrix(3, 3);
        StaticMatrix<int, 3, 3> static_matrix;

        std::set<int> set1(dynamic_matrix.begin(), dynamic_matrix.end());
        std::set<int> set2(static_matrix.begin(), static_matrix.end());
    }

    return EXIT_SUCCESS;
}