#ifndef MATRIX_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H
#define MATRIX_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H

namespace ng{
    template <typename NormalIterator>
    class matrix_reverse_iterator {
    protected:
        NormalIterator current_;

    public:
        constexpr matrix_reverse_iterator() noexcept : current_(NormalIterator()) {};
        explicit constexpr matrix_reverse_iterator(const typename NormalIterator::iterator_type &it) noexcept : current_(it) {};

    public:
        using iterator_type = typename NormalIterator::iterator_type;
        using pointer = typename NormalIterator::pointer;
        using reference = typename NormalIterator::reference;
        using value_type = typename NormalIterator::value_type;
        using difference_type = typename NormalIterator::difference_type;
        using iterator_category = typename NormalIterator::iterator_category;

    public:
        constexpr reference operator*() const noexcept { return *current_; }
        constexpr pointer   operator->() const noexcept { return current_.Base(); }

        constexpr matrix_reverse_iterator &operator++() noexcept {
            --current_;
            return *this;
        }

        constexpr matrix_reverse_iterator operator++(int) noexcept {
            return matrix_reverse_iterator(current_--);
        }

        constexpr matrix_reverse_iterator &operator--() noexcept {
            ++current_;
            return *this;
        }

        constexpr matrix_reverse_iterator operator--(int) noexcept {
            return matrix_reverse_iterator(current_++);
        }

        constexpr matrix_reverse_iterator &operator+=(difference_type n) noexcept {
            current_ -= n;
            return *this;
        }

        constexpr matrix_reverse_iterator operator+(difference_type n) noexcept {
            return matrix_reverse_iterator((current_ - n).Base());
        }

        constexpr matrix_reverse_iterator &operator-=(difference_type n) noexcept {
            current_ += n;
            return *this;
        }

        constexpr matrix_reverse_iterator operator-(difference_type n) noexcept {
            return matrix_reverse_iterator((current_ - n).Base());
        }

        const iterator_type &Base() const noexcept {
            return current_.Base();
        }
    };

    template <typename NormalIterator>
    [[__nodiscard__]] constexpr bool operator==(const matrix_reverse_iterator<NormalIterator> &lhs,
                                                const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() == rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]] constexpr bool operator!=(const matrix_reverse_iterator<NormalIterator> &lhs,
                                                const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() != rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator<(const matrix_reverse_iterator<NormalIterator> &lhs,
                                             const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator>(const matrix_reverse_iterator<NormalIterator> &lhs,
                                             const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator<=(const matrix_reverse_iterator<NormalIterator> &lhs,
                                              const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator>=(const matrix_reverse_iterator<NormalIterator> &lhs,
                                              const matrix_reverse_iterator<NormalIterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline auto operator-(const matrix_reverse_iterator<NormalIterator> &lhs,
                                             const matrix_reverse_iterator<NormalIterator> &rhs) {
        return rhs.Base() - lhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline auto operator+(const matrix_reverse_iterator<NormalIterator> &lhs,
                                             const matrix_reverse_iterator<NormalIterator> &rhs) {
        return rhs.Base() + lhs.Base();
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H
