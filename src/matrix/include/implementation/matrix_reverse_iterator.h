#ifndef MATRIX_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H
#define MATRIX_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H

namespace ng::__internal {
    template <typename NormalIterator>
    class MatrixReverseInterator {
    protected:
        NormalIterator current_;

    public:
        constexpr MatrixReverseInterator() noexcept : current_(NormalIterator()) {};
        explicit constexpr MatrixReverseInterator(const typename NormalIterator::iterator_type &it) noexcept : current_(it) {};

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

        constexpr MatrixReverseInterator &operator++() noexcept {
            --current_;
            return *this;
        }

        constexpr MatrixReverseInterator operator++(int) noexcept {
            return MatrixReverseInterator(current_--);
        }

        constexpr MatrixReverseInterator &operator--() noexcept {
            ++current_;
            return *this;
        }

        constexpr MatrixReverseInterator operator--(int) noexcept {
            return MatrixNormalIterator(current_++);
        }

        constexpr MatrixReverseInterator &operator+=(difference_type n) noexcept {
            current_ -= n;
            return *this;
        }

        constexpr MatrixReverseInterator &operator+(difference_type n) noexcept {
            return MatrixNormalIterator(current_ + n);
        }

        constexpr MatrixReverseInterator &operator-=(difference_type n) noexcept {
            current_ += n;
            return *this;
        }

        constexpr MatrixReverseInterator &operator-(difference_type n) noexcept {
            return MatrixNormalIterator(current_ - n);
        }

        const iterator_type &Base() const noexcept {
            return current_.Base();
        }
    };

    template <typename NormalIterator>
    [[__nodiscard__]] constexpr bool operator==(const MatrixReverseInterator<NormalIterator> &lhs,
                                                const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() == rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]] constexpr bool operator!=(const MatrixReverseInterator<NormalIterator> &lhs,
                                                const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() != rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator<(const MatrixReverseInterator<NormalIterator> &lhs,
                                             const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator>(const MatrixReverseInterator<NormalIterator> &lhs,
                                             const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator<=(const MatrixReverseInterator<NormalIterator> &lhs,
                                              const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline bool operator>=(const MatrixReverseInterator<NormalIterator> &lhs,
                                              const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline auto operator-(const MatrixReverseInterator<NormalIterator> &lhs,
                                             const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() - rhs.Base();
    }

    template <typename NormalIterator>
    [[__nodiscard__]]  inline auto operator+(const MatrixReverseInterator<NormalIterator> &lhs,
                                             const MatrixReverseInterator<NormalIterator> &rhs) {
        return lhs.Base() + rhs.Base();
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_REVERSE_ITERATOR_H
