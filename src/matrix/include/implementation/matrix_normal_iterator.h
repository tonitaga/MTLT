#ifndef MATRIX_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H
#define MATRIX_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H

#include <iterator>

namespace ng::__internal {
    template <typename Iterator>
    class MatrixNormalIterator {
    protected:
        Iterator current_;

    public:
        using iterator_type = Iterator;
        using pointer = Iterator;
        using reference = decltype(*current_) &;
        using value_type = decltype(*current_);
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        
    public:
        constexpr MatrixNormalIterator() noexcept : current_(Iterator()) {};
        explicit constexpr MatrixNormalIterator(const Iterator &it) noexcept : current_(it) {};
        
    public:
        constexpr reference operator*() const noexcept { return *current_; }
        constexpr pointer   operator->() const noexcept { return current_; }
        
        constexpr MatrixNormalIterator &operator++() noexcept {
            ++current_;
            return *this;
        }
        
        constexpr MatrixNormalIterator operator++(int) noexcept {
            return MatrixNormalIterator(current_++);
        }

        constexpr MatrixNormalIterator &operator--() noexcept {
            --current_;
            return *this;
        }

        constexpr MatrixNormalIterator operator--(int) noexcept {
            return MatrixNormalIterator(current_--);
        }
        
        constexpr MatrixNormalIterator &operator+=(difference_type n) noexcept {
            current_ += n;
            return *this;
        }

        constexpr MatrixNormalIterator &operator+(difference_type n) noexcept {
            return MatrixNormalIterator(current_ + n);
        }

        constexpr MatrixNormalIterator &operator-=(difference_type n) noexcept {
            current_ -= n;
            return *this;
        }

        constexpr MatrixNormalIterator &operator-(difference_type n) noexcept {
            return MatrixNormalIterator(current_ - n);
        }
        
        constexpr const Iterator &Base() const noexcept {
            return current_;
        }
    };
    
    template <typename Iterator>
    [[__nodiscard__]] constexpr bool operator==(const MatrixNormalIterator<Iterator> &lhs,
                                                const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() == rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]] constexpr bool operator!=(const MatrixNormalIterator<Iterator> &lhs,
                                                const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() != rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator<(const MatrixNormalIterator<Iterator> &lhs,
                                             const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator>(const MatrixNormalIterator<Iterator> &lhs,
                                             const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator<=(const MatrixNormalIterator<Iterator> &lhs,
                                             const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator>=(const MatrixNormalIterator<Iterator> &lhs,
                                              const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline auto operator-(const MatrixNormalIterator<Iterator> &lhs,
                                             const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() - rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline auto operator+(const MatrixNormalIterator<Iterator> &lhs,
                                             const MatrixNormalIterator<Iterator> &rhs) {
        return lhs.Base() + rhs.Base();
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H
