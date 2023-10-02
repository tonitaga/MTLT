#ifndef MATRIX_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H
#define MATRIX_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H

#include <iterator>

namespace ng {
    template <typename Iterator>
    class matrix_normal_iterator {
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
        _GLIBCXX17_CONSTEXPR matrix_normal_iterator() noexcept : current_(Iterator()) {};
        explicit _GLIBCXX17_CONSTEXPR matrix_normal_iterator(const Iterator &it) noexcept : current_(it) {};
        
    public:
        _GLIBCXX17_CONSTEXPR reference operator*() const noexcept { return *current_; }
        _GLIBCXX17_CONSTEXPR pointer   operator->() const noexcept { return current_; }

        _GLIBCXX17_CONSTEXPR reference operator[](difference_type n) noexcept {
            return current_[n];
        }
        
        _GLIBCXX17_CONSTEXPR matrix_normal_iterator &operator++() noexcept {
            ++current_;
            return *this;
        }
        
        _GLIBCXX17_CONSTEXPR matrix_normal_iterator operator++(int) noexcept {
            return matrix_normal_iterator(current_++);
        }

        _GLIBCXX17_CONSTEXPR matrix_normal_iterator &operator--() noexcept {
            --current_;
            return *this;
        }

        _GLIBCXX17_CONSTEXPR matrix_normal_iterator operator--(int) noexcept {
            return matrix_normal_iterator(current_--);
        }
        
        _GLIBCXX17_CONSTEXPR matrix_normal_iterator &operator+=(difference_type n) noexcept {
            current_ += n;
            return *this;
        }

        _GLIBCXX17_CONSTEXPR matrix_normal_iterator operator+(difference_type n) noexcept {
            return matrix_normal_iterator(current_ + n);
        }

        _GLIBCXX17_CONSTEXPR matrix_normal_iterator &operator-=(difference_type n) noexcept {
            current_ -= n;
            return *this;
        }

        _GLIBCXX17_CONSTEXPR matrix_normal_iterator operator-(difference_type n) noexcept {
            return matrix_normal_iterator(current_ - n);
        }
        
        _GLIBCXX17_CONSTEXPR const Iterator &Base() const noexcept {
            return current_;
        }
    };
    
    template <typename Iterator>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR bool operator==(const matrix_normal_iterator<Iterator> &lhs,
                                                const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() == rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR bool operator!=(const matrix_normal_iterator<Iterator> &lhs,
                                                const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() != rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator<(const matrix_normal_iterator<Iterator> &lhs,
                                             const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator>(const matrix_normal_iterator<Iterator> &lhs,
                                             const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator<=(const matrix_normal_iterator<Iterator> &lhs,
                                             const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() < rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline bool operator>=(const matrix_normal_iterator<Iterator> &lhs,
                                              const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() > rhs.Base();
    }

    template <typename Iterator>
    [[__nodiscard__]]  inline std::ptrdiff_t operator-(const matrix_normal_iterator<Iterator> &lhs,
                                             const matrix_normal_iterator<Iterator> &rhs) {
        return lhs.Base() - rhs.Base();
    }
}

#endif //MATRIX_LIBRARY_CPP_MATRIX_NORMAL_ITERATOR_H
