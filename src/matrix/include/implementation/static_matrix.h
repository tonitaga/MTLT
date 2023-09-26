#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_H

#include <vector>
#include <type_traits>

#include "matrix_state.h"
#include "matrix_normal_iterator.h"
#include "matrix_reverse_iterator.h"

namespace ng {
    template <typename T, std::size_t Rows, std::size_t Cols>
    class StaticMatrix {
        static_assert(std::is_fundamental_v<T>,
                      "Template parameter T must be fundamental!");

    public:
        using value_type = typename std::allocator_traits<std::allocator<T>>::value_type;
        using pointer = typename std::allocator_traits<std::allocator<T>>::pointer;
        using const_pointer = typename std::allocator_traits<std::allocator<T>>::const_pointer;
        using size_type = typename std::allocator_traits<std::allocator<T>>::size_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = __internal::MatrixNormalIterator<pointer>;
        using const_iterator = __internal::MatrixNormalIterator<const_pointer>;
        using reverse_iterator = __internal::MatrixReverseInterator<iterator>;
        using const_reverse_iterator = __internal::MatrixReverseInterator<const_iterator>;

    public:
        constexpr StaticMatrix() noexcept = default;
        constexpr explicit StaticMatrix(value_type fill) noexcept;

        constexpr StaticMatrix(const StaticMatrix &);
        constexpr Stati


    public:
        iterator begin() noexcept { return iterator(data_); }
        iterator end() noexcept { return iterator(data_ + rows_ * cols_); }

        const_iterator begin() const noexcept { return const_iterator(data_); }
        const_iterator end() const noexcept { return const_iterator(data_ + rows_ * cols_); }

        const_iterator cbegin() const noexcept { return const_iterator(data_); }
        const_iterator cend() const noexcept { return const_iterator(data_ + rows_ * cols_); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(data_ + rows_ * cols_ - 1); }
        reverse_iterator rend() noexcept { return reverse_iterator(data_ - 1); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(data_ - 1); }

        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(data_ - 1); }

    private:
        size_type rows_ = Rows, cols_ = Cols;
        value_type data_[Rows * Cols] {};
    };

    template <typename T, std::size_t Square>
    using SquareMatrix = StaticMatrix<T, Square, Square>;
}

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
