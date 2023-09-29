#include "matrix"
#include "static_matrix"

using namespace ng;

int main() {
    Matrix<int> dynamic_matrix(3, 3);
    StaticMatrix<int, 3, 3> static_matrix;

    //
    //  Matrix and StaticMatrix classes are containers, so they have their own iterators
    //
    //  ng::__internal::MatrixNormalIterator (random_access_iterator)
    //  ng::__internal::MatrixReverseInterator (random_access_iterator)
    //
    //  Don't create them manually, get them from classes
    //

    // MatrixNormalIterator
    dynamic_matrix.begin();
    static_matrix.begin();

    dynamic_matrix.end();
    static_matrix.end();

    dynamic_matrix.cbegin();
    static_matrix.cbegin();

    // MatrixReverseIterator
    dynamic_matrix.rbegin();
    static_matrix.rbegin();

    dynamic_matrix.rend();
    static_matrix.rend();

    dynamic_matrix.crbegin();
    static_matrix.crbegin();

    // Support of matrix iteration is useful, you can create other container from your matrix
    std::vector<int> vec1(dynamic_matrix.begin(), dynamic_matrix.end());
    std::vector<int> vec2(static_matrix.begin(), static_matrix.end());

    std::vector<int> vec3(dynamic_matrix.rbegin(), dynamic_matrix.rend());
    std::vector<int> vec4(static_matrix.rbegin(), static_matrix.rend());
}