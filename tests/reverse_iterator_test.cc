#include "matrix.h"
#include "static_matrix.h"

#include <gtest/gtest.h>

using namespace mtl;

TEST(ReverseIterator, begin_matrix) {
    matrix<int> m1(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});
    const matrix<int> m2(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});

    auto begin1 = m1.rbegin();
    auto const_begin1 = m1.crbegin();

    auto begin2 = m2.rbegin();
    auto const_begin2 = m2.crbegin();

    ASSERT_EQ(*begin1, 1);
    ASSERT_EQ(*begin2, 1);

    ASSERT_EQ(*(begin1 + 2), 3);
    ASSERT_EQ(*(begin2 + 2), 3);

    ASSERT_EQ(*(++begin1), 2);
    ASSERT_EQ(*(++begin2), 2);
}

TEST(ReverseIterator, begin_static_matrix) {
    static_matrix<int, 3, 3> m1({9, 8, 7, 6, 5, 4, 3, 2, 1});
    const static_matrix<int, 3, 3> m2({9, 8, 7, 6, 5, 4, 3, 2, 1});

    auto begin1 = m1.rbegin();
    auto const_begin1 = m1.crbegin();

    auto begin2 = m2.rbegin();
    auto const_begin2 = m2.crbegin();

    ASSERT_EQ(*begin1, 1);
    ASSERT_EQ(*begin2, 1);

    ASSERT_EQ(*(begin1 + 2), 3);
    ASSERT_EQ(*(begin2 + 2), 3);

    ASSERT_EQ(*(++begin1), 2);
    ASSERT_EQ(*(++begin2), 2);
}

TEST(ReverseIterator, iter_tag) {
    bool is_same1 = std::is_same<static_matrix<int, 1, 1>::reverse_iterator::iterator_category, std::random_access_iterator_tag>::value;
    bool is_same2 = std::is_same<matrix<int>::reverse_iterator::iterator_category, std::random_access_iterator_tag>::value;

    ASSERT_TRUE(is_same1);
    ASSERT_TRUE(is_same2);
}

TEST(ReverseIterator, distance) {
    matrix<int> m1(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});
    static_matrix<int, 3, 3> m2({9, 8, 7, 6, 5, 4, 3, 2, 1});

    auto begin1 = m1.rbegin(), end1 = m1.rend();
    auto begin2 = m2.rbegin(), end2 = m2.rend();

    ASSERT_EQ(std::distance(begin1, end1), 9);
    ASSERT_EQ(std::distance(begin2, end2), 9);
}

TEST(ReverseIterator, container_creation) {
    matrix<int> m1(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});
    static_matrix<int, 3, 3> m2({9, 8, 7, 6, 5, 4, 3, 2, 1});

    std::vector<int> vec1(m1.rbegin(), m1.rend());
    std::vector<int> vec2(m2.rbegin(), m2.rend());

    auto begin_m1 = m1.rbegin();
    auto begin_m2 = m2.rbegin();
    auto begin_vec1 = vec1.begin();
    auto begin_vec2 = vec2.begin();

    auto end_m1 = m1.rend();

    while (begin_m1 != end_m1) {
        ASSERT_EQ(*begin_m1, *begin_vec1);
        ASSERT_EQ(*begin_m2, *begin_vec2);

        ++begin_m1, ++begin_m2, ++begin_vec1, ++begin_vec2;
    }
}