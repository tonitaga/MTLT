#include "matrix"

#include <cassert>

using namespace ng;

int main() {
    Matrix<int> m1(5, 5);

    // normal iterator
    auto begin = m1.begin();
    auto end = m1.end();
    auto cbegin = m1.cbegin();
    auto cend = m1.cend();

    // reverse iterator
    auto rbegin = m1.rbegin();
    auto rend = m1.rend();
    auto crbegin = m1.crbegin();
    auto crend = m1.crend();

    // containers construction from matrix data
    std::vector<int> normal(begin, end);
    std::vector<int> reverse(rbegin, rend);

    auto random_access_iterator1 = std::iterator_traits<Matrix<int>::iterator>::iterator_category{};
    auto random_access_iterator2 = std::iterator_traits<Matrix<int>::reverse_iterator>::iterator_category{};

    return EXIT_SUCCESS;
}