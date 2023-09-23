#ifndef MATRIX_LIBRARY_CPP_MATRIX_H_
#define MATRIX_LIBRARY_CPP_MATRIX_H_

#include <type_traits>

#include "matrix_debug.h"
#include "matrix_normal_iterator.h"

namespace ng {
    template <typename T>
    class Matrix {
        static_assert(std::is_integral_v<T> or std::is_floating_point_v<T>,
                      "Template parameter T must be integral or floating point!");

    public:
        using value_type = typename std::allocator_traits<std::allocator<T>>::value_type;
        using pointer = typename std::allocator_traits<std::allocator<T>>::pointer;
        using const_pointer = typename std::allocator_traits<std::allocator<T>>::const_pointer;
        using size_type = typename std::allocator_traits<std::allocator<T>>::size_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = __internal::MatrixNormalIterator<pointer>;
        using const_iterator = __internal::MatrixNormalIterator<const_pointer>;

    public:
        constexpr Matrix() noexcept = default;

        constexpr Matrix(size_type rows, size_type cols) : rows_(rows), cols_(cols), data_(new value_type[rows * cols]{}) {};
        constexpr explicit Matrix(size_type square) : Matrix(square, square) {};

        template<typename U>
        constexpr Matrix(const Matrix<U> &);

        constexpr Matrix(const Matrix &);
        constexpr Matrix(Matrix &&) noexcept;

        constexpr Matrix &operator=(const Matrix &);
        constexpr Matrix &operator=(Matrix &&) noexcept;

        ~Matrix() noexcept;

    public:
        iterator begin() noexcept { return iterator(data_); }
        iterator end() noexcept { return iterator(data_ + rows_ * cols_); }

        const_iterator begin() const noexcept { return const_iterator(data_); }
        const_iterator end() const noexcept { return const_iterator(data_ + rows_ * cols_); }

        const_iterator cbegin() const noexcept { return const_iterator(data_); }
        const_iterator cend() const noexcept { return const_iterator(data_ + rows_ * cols_); }

    public:
        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        reference at(size_type row, size_type col);
        const_reference at(size_type row, size_type col) const;

        size_type rows() const noexcept { return rows_; }
        size_type cols() const noexcept { return cols_; }

        void rows(size_type rows);
        void cols(size_type cols);
        void resize(size_type rows, size_type cols);

    public:
        void print(std::ostream &os, MatrixDebugSettings settings = default_debug) const;

    public:
        template<typename UnaryOperation>
        void transform(UnaryOperation &&op);

        template<typename BinaryOperation>
        void transform(const Matrix &other, BinaryOperation &&op);

        template<typename Operation>
        void generate(Operation &&op);

        void mul(const value_type &number);
        void div(const value_type &number);
        void add(const value_type &number);
        void sub(const value_type &number);

        void fill(const value_type &number);
        void fill_random(const value_type &left, const value_type &right);

        void round();
        void floor();
        void ceil();
        void zero();

        void to_identity();

    public:
        template<typename ConvertType>
        Matrix<ConvertType> convert_to() const;

        std::vector<value_type> convert_to_vector() const;
        std::vector<std::vector<value_type>> convert_to_matrix_vector() const;

    private:
        size_type rows_ {}, cols_ {};
        pointer data_ = nullptr;
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs);

    using IMatrix = Matrix<int>;
    using UMatrix = Matrix<unsigned>;
    using FMatrix = Matrix<float>;
    using DMatrix = Matrix<double>;
}

#include "matrix.tpp"

#endif //MATRIX_LIBRARY_CPP_MATRIX_H_
