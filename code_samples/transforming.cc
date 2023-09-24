#include "matrix"

using namespace ng;

int main() {
    Matrix<int> m1(5, 5);

    // mul number
    m1.mul(2);
    m1 *= 2;
    m1 = m1 * 2;

    // mul matrix same type
    m1.mul(Matrix<int>());
    m1 *= Matrix<int>();
    m1 = m1 * Matrix<int>();

    // mul matrix other type
    m1.mul(Matrix<float>());
    m1 *= Matrix<float>();
    m1 = m1 * Matrix<float>();

    // add number
    m1.add(2);
    m1 += 2;
    m1 = m1 + 2;

    // add matrix same type
    m1.add(Matrix<int>());
    m1 += Matrix<int>();
    m1 = m1 + Matrix<int>();

    // add matrix other type
    m1.add(Matrix<float>());
    m1 += Matrix<float>();
    m1 = m1 + Matrix<float>();

    // sub number
    m1.sub(2);
    m1 -= 2;
    m1 = m1 - 2;

    // sub matrix same type
    m1.sub(Matrix<int>());
    m1 -= Matrix<int>();
    m1 = m1 - Matrix<int>();

    // sub matrix other type
    m1.sub(Matrix<float>());
    m1 -= Matrix<float>();
    m1 = m1 - Matrix<float>();

    // div number
    m1.div(2);
    m1 /= 2;
    m1 = m1 / 2;

    // round items in matrix
    m1.round();

    // floor items in matrix
    m1.floor();

    // ceil items in matrix
    m1.ceil();

    // transform matrix with lambda
    m1.transform([](auto item) {
        return item << 1;
    });

    // transform matrix with lambda using other matrix
    // sum example
    Matrix<int> m2 = m1;
    m1.transform(m2, [](int lhs, int rhs) {
        return lhs + rhs;
    });

    // fill matrix with value
    m1.fill(1);

    // fill randomly
    m1.fill_random(0, 1);

    // load to identity
    m1.to_identity();

    // zero matrix
    m1.zero();

    // clear matrix
    m1.clear();

    // generate matrix items with lambda
    int value = 0;
    m1.generate([&value](){
       return value * 2 / 4 + 4;
    });

    // transpose matrix
    auto transpose = m1.transpose();

    return EXIT_SUCCESS;
}