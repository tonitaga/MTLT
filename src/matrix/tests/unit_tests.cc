#include <gtest/gtest.h>

#include "matrix"
#include "static_matrix"

using namespace ng;

TEST(DynamicMatrix, EmptyMatrix) {
    Matrix<int> m;
    ASSERT_EQ(m.size(), 0);
}

TEST(DynamicMatrix, SizedMatrix) {
    Matrix<int> m(3, 3, 5);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 5);
}

TEST(DynamicMatrix, SqMatrix) {
    Matrix<int> m(5);
    ASSERT_EQ(m.size(), 25);
    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.cols(), 5);
    ASSERT_EQ(m(0, 0), 0);
}

TEST(DynamicMatrix, MatrixVector) {
    std::vector<std::vector<int>> v {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    Matrix<int> m(v);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(DynamicMatrix, InitializerList) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(DynamicMatrix, ContainerConstructor) {
    Matrix<int> m(3, 3, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(DynamicMatrix, IdentityStaticMethod) {
    Matrix m = Matrix<int>::identity(3, 3);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(2, 2), 1);
}

TEST(DynamicMatrix, CopyConstructor) {
    Matrix m = Matrix<int>::identity(3, 3);
    Matrix m2 = m;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
}

TEST(DynamicMatrix, CopyAssignment) {
    Matrix m = Matrix<int>::identity(3, 3);
    Matrix<int> m2;
    m2 = m;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
}

TEST(DynamicMatrix, MoveConstructor) {
    Matrix m = Matrix<int>::identity(3, 3);
    Matrix<int> m2 = std::move(m);
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
    ASSERT_EQ(m.size(), 0);
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
}

TEST(DynamicMatrix, IterationBegin) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto begin = m.begin(); begin += 2;
    auto cbegin = m.cbegin();
    auto rbegin = m.rbegin(); rbegin += 1;
    auto crbegin = m.crbegin();
    ASSERT_EQ(*begin, 3);
    ASSERT_EQ(*cbegin, 1);
    ASSERT_EQ(*rbegin, 8);
    ASSERT_EQ(*crbegin, 9);
}

TEST(DynamicMatrix, IterationEnd) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto end = m.end(); end -= 2;
    auto cend = m.end(); cend -= 1;
    auto rend = m.rend(); rend -= 1;
    auto crend = m.crend(); crend -= 2;
    ASSERT_EQ(*end, 8);
    ASSERT_EQ(*cend, 9);
    ASSERT_EQ(*rend, 1);
    ASSERT_EQ(*crend, 2);
}

TEST(DynamicMatrix, ChangeSizes) {
    Matrix<int> m(3, 3, 1);
    m.rows(5); m.cols(5);
    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.cols(), 5);
    ASSERT_EQ(m(4, 4), 0);

    m.resize(3, 3);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(2, 2), 1);

    m.clear();
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
}

// In Future will be more tests

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
