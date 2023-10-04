#ifndef MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H_
#define MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H_

#include <iterator>

#include "matrix_config.h"

namespace mtl {
    template <typename NormalIterator>
    class matrix_reverse_iterator {
    protected:
        NormalIterator current_;

    public:
        MATRIX_CXX17_CONSTEXPR          matrix_reverse_iterator() noexcept : current_(NormalIterator()) {};
        explicit MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator(const typename NormalIterator::iterator_type &it) noexcept : current_(it) {};

    public:
        using iterator_type =     typename NormalIterator::iterator_type;
        using pointer =           typename NormalIterator::pointer;
        using reference =         typename NormalIterator::reference;
        using value_type =        typename NormalIterator::value_type;
        using difference_type =   typename NormalIterator::difference_type;
        using iterator_category = typename NormalIterator::iterator_category;

    public:
        MATRIX_CXX17_CONSTEXPR reference operator*() const noexcept { return *current_; }
        MATRIX_CXX17_CONSTEXPR pointer   operator->() const noexcept { return current_.Base(); }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator &operator++() noexcept {
            --current_;
            return *this;
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator operator++(int) noexcept {
            return matrix_reverse_iterator(current_--);
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator &operator--() noexcept {
            ++current_;
            return *this;
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator operator--(int) noexcept {
            return matrix_reverse_iterator(current_++);
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator &operator+=(difference_type n) noexcept {
            current_ -= n;
            return *this;
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator operator+(difference_type n) noexcept {
            return matrix_reverse_iterator((current_ - n).Base());
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator &operator-=(difference_type n) noexcept {
            current_ += n;
            return *this;
        }

        MATRIX_CXX17_CONSTEXPR matrix_reverse_iterator operator-(difference_type n) noexcept {
            return matrix_reverse_iterator((current_ + n).Base());
        }

        const iterator_type &Base() const noexcept {
            return current_.Base();
        }
    };

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    MATRIX_CXX17_CONSTEXPR bool operator==(const matrix_reverse_iterator<NormalIterator> &lhs,
                                           const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() == rhs.Base();
    }

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    MATRIX_CXX17_CONSTEXPR bool operator!=(const matrix_reverse_iterator<NormalIterator> &lhs,
                                           const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() != rhs.Base();
    }

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    inline bool operator<(const matrix_reverse_iterator<NormalIterator> &lhs,
                          const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    inline bool operator>(const matrix_reverse_iterator<NormalIterator> &lhs,
                          const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    inline bool operator<=(const matrix_reverse_iterator<NormalIterator> &lhs,
                           const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    inline bool operator>=(const matrix_reverse_iterator<NormalIterator> &lhs,
                           const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename NormalIterator>
    MATRIX_CXX17_NODISCARD
    inline std::ptrdiff_t operator-(const matrix_reverse_iterator<NormalIterator> &lhs,
                                    const matrix_reverse_iterator<NormalIterator> &rhs) {
        return rhs.Base() - lhs.Base();
    }
}

#endif //MATRIX_TEMPLATE_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H_
