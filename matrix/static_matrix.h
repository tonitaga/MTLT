#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_H

#include <array>

#if __cplusplus > 201703L
    #include <concepts>
#endif

#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <type_traits>

#include "matrix_state.h"
#include "matrix_normal_iterator.h"
#include "matrix_reverse_iterator.h"

namespace ng {
#if __cplusplus > 201703L
    template<fundamental T, std::size_t Rows, std::size_t Cols> requires(non_zero_dimension<Rows, Cols>)
    class static_matrix {
#else
    template <typename T, std::size_t Rows, std::size_t Cols>
    class static_matrix {
        static_assert(std::is_fundamental<T>::value, "Template paramener T must be fundamental");
#endif // C++ <= 201703L
    public:
        using value_type =             T;
        using pointer =                value_type *;
        using const_pointer =          const value_type *;
        using size_type =              std::size_t;
        using reference =              value_type &;
        using const_reference =        const value_type &;
        using iterator =               matrix_normal_iterator<pointer>;
        using const_iterator =         matrix_normal_iterator<const_pointer>;
        using reverse_iterator =       matrix_reverse_iterator<iterator>;
        using const_reverse_iterator = matrix_reverse_iterator<const_iterator>;

    public:
        _GLIBCXX17_CONSTEXPR          static_matrix() noexcept = default;
        _GLIBCXX17_CONSTEXPR explicit static_matrix(value_type fill) noexcept {
            if (fill != value_type{})
                for (size_type i = 0; i != Rows * Cols; ++i)
                    data_[i] = fill;
        }

        _GLIBCXX17_CONSTEXPR explicit static_matrix(const std::array<T, Rows * Cols> &initializer) {
            _GLIBCXX17_CONSTEXPR std::size_t kSize = Rows * Cols;
            for (std::size_t i = 0; i != kSize; ++i)
                data_[i] = initializer[i];
        }

#if __cplusplus > 201703L
        template<typename Container>
        requires(std::convertible_to<typename Container::value_type, T>)
        _GLIBCXX17_CONSTEXPR explicit static_matrix(const Container &container) {
            if (Rows * Cols != container.size())
                throw std::logic_error("container has more/less items than in matrix");

            std::copy(container.begin(), container.end(), begin());
        }

        template<typename Container>
        requires(std::convertible_to<typename Container::value_type, T>)
        _GLIBCXX17_CONSTEXPR static_matrix &operator=(const Container &container) {
            if (Rows * Cols != container.size())
                throw std::logic_error("");

            std::copy(container.begin(), container.end(), begin());
        }
#else
        template <typename Container>
        _GLIBCXX17_CONSTEXPR explicit static_matrix(const Container &container) {
            static_assert(std::is_convertible<typename Container::value_type, T>::value, "Container::value_type must be convertible to T");

            if (Rows * Cols != container.size())
                throw std::logic_error("");

            std::copy(container.begin(), container.end(), begin());
        }

        template<typename Container>
        _GLIBCXX17_CONSTEXPR static_matrix &operator=(const Container &container) {
            static_assert(std::is_convertible<typename Container::value_type, T>::value, "Container::value_type must be convertible to T");

            if (Rows * Cols != container.size())
                throw std::logic_error("");

            std::copy(container.begin(), container.end(), begin());
        }
#endif // C++ <= 201703L

    public:
        _GLIBCXX17_CONSTEXPR iterator               begin() noexcept { return iterator(data_); }
        _GLIBCXX17_CONSTEXPR const_iterator         begin() const noexcept { return const_iterator(data_); }
        _GLIBCXX17_CONSTEXPR const_iterator         cbegin() const noexcept { return const_iterator(data_); }
        _GLIBCXX17_CONSTEXPR reverse_iterator       rbegin() noexcept { return reverse_iterator(data_ + rows_ * cols_ - 1); }
        _GLIBCXX17_CONSTEXPR const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }
        _GLIBCXX17_CONSTEXPR const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(data_ + rows_ * cols_ - 1); }

        _GLIBCXX17_CONSTEXPR iterator               end()   noexcept       { return iterator(data_ + rows_ * cols_); }
        _GLIBCXX17_CONSTEXPR const_iterator         end()   const noexcept { return const_iterator(data_ + rows_ * cols_); }
        _GLIBCXX17_CONSTEXPR const_iterator         cend()  const noexcept { return const_iterator(data_ + rows_ * cols_); }
        _GLIBCXX17_CONSTEXPR reverse_iterator       rend()  noexcept       { return reverse_iterator(data_ - 1); }
        _GLIBCXX17_CONSTEXPR const_reverse_iterator rend()  const noexcept { return const_reverse_iterator(data_ - 1); }
        _GLIBCXX17_CONSTEXPR const_reverse_iterator crend() const noexcept { return const_reverse_iterator(data_ - 1); }

    public:
        _GLIBCXX17_CONSTEXPR reference operator()(size_type row, size_type col) {
            return data_[row * cols_ + col];
        }

        _GLIBCXX17_CONSTEXPR const_reference operator()(size_type row, size_type col) const {
            return data_[row * cols_ + col];
        }

        _GLIBCXX17_CONSTEXPR reference at(size_type row, size_type col) {
            if (row >= rows_ or col >= cols_)
                throw std::out_of_range("row or col is out of matrix bounds");
            return (*this)(row, col);
        }

        _GLIBCXX17_CONSTEXPR const_reference at(size_type row, size_type col) const {
            if (row >= rows_ or col >= cols_)
                throw std::out_of_range("row or col is out of matrix bounds");
            return (*this)(row, col);
        }

        _GLIBCXX17_CONSTEXPR size_type rows() const noexcept { return rows_; }
        _GLIBCXX17_CONSTEXPR size_type cols() const noexcept { return cols_; }
        _GLIBCXX17_CONSTEXPR size_type size() const noexcept { return rows_ * cols_; }

    public:
        void print(std::ostream &os = std::cout) const {
            int width = matrix_debug_settings::width, precision = matrix_debug_settings::precision;
            char separator = matrix_debug_settings::separator, end = matrix_debug_settings::end;
            bool is_double_end = matrix_debug_settings::is_double_end;

            for (size_type row = 0; row != rows_; ++row) {
                for (size_type col = 0; col != cols_; ++col) {
                    os << std::setw(width) << std::setprecision(precision) << (*this)(row, col) << separator;
                }
                os << end;
            }

            if (is_double_end)
                os << end;
        }

    public:
        template<typename UnaryOperation>
        _GLIBCXX17_CONSTEXPR void transform(UnaryOperation &&op) {
            std::transform(begin(), end(), begin(), std::forward<UnaryOperation>(op));
        }

        template<typename BinaryOperation>
        void transform(const static_matrix &other, BinaryOperation &&op) {
            std::transform(begin(), end(), other.begin(), begin(), std::forward<BinaryOperation>(op));
        }

        template<typename Operation>
        void generate(Operation &&op) {
            std::generate(begin(), end(), std::forward<Operation>(op));
        }

        static_matrix &fill(const value_type &number) {
            std::fill(begin(), end(), number);
        }

        static_matrix &fill_random(const value_type &left, const value_type &right) {
            using namespace std::chrono;

            std::default_random_engine re(system_clock::now().time_since_epoch().count());
            auto distribution = typename std::conditional<std::is_integral<T>::value,
                    std::uniform_int_distribution<T>,
                    std::uniform_real_distribution<T>>::type(left, right);

            generate([&]() {
                return distribution(re);
            });

            return *this;
        }

        static_matrix &to_round() {
            transform([](const value_type &item) { return std::round(item); });
            return *this;
        }

         static_matrix round() const {
            static_matrix m(*this);
            std::transform(m.begin(), m.end(), m.begin(), [](const value_type &item) { return std::round(item); });
            return m;
        }

        static_matrix &to_floor() {
            transform([](const value_type &item) { return std::floor(item); });
            return *this;
        }

        static_matrix floor() const {
            static_matrix m(*this);
            std::transform(m.begin(), m.end(), m.begin(), [](const value_type &item) { return std::floor(item); });
            return m;
        }

        static_matrix &to_ceil() {
            transform([](const value_type &item) { return std::ceil(item); });
            return *this;
        }

        static_matrix ceil() const {
            static_matrix m(*this);
            std::transform(m.begin(), m.end(), m.begin(), [](const value_type &item) { return std::ceil(item); });
            return m;
        }

        static_matrix &to_zero() {
            generate([]() { return value_type{}; });
            return *this;
        }

        _GLIBCXX17_CONSTEXPR static_matrix zero() const {
            return static_matrix<T, Rows, Cols>();
        }

#if __cplusplus > 201703L
        static_matrix &to_identity() requires(Rows == Cols) {
#else
        static_matrix &to_identity() {
            static_assert(Rows == Cols, "Matrix must be square");
#endif // C++ <= 201703L
            for (size_type row = 0; row != rows_; ++row)
                for (size_type col = 0; col != cols_; ++col)
                    (*this)(row, col) = row == col ? value_type{1} : value_type{};

            return *this;
        }

#if __cplusplus > 201703L
        _GLIBCXX17_CONSTEXPR static_matrix identity() const requires(Rows == Cols) {
#else
        _GLIBCXX17_CONSTEXPR static_matrix identity() const {
            static_assert(Rows == Cols, "Matrix must be square");
#endif // C++ <= 201703L
            static_matrix<T, Rows, Cols> identity;
            _GLIBCXX17_CONSTEXPR value_type one = value_type{1};
            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols; ++col)
                    if (row == col)
                        identity(row, col) = one;

            return identity;
        }

        static_matrix &mul(const value_type &value) {
            transform([&value](const value_type &item) { return item * value; });
            return *this;
        }

        static_matrix &add(const value_type &value) {
            transform([&value](const value_type &item) { return item + value; });
            return *this;
        }

        static_matrix &sub(const value_type &value) {
            transform([&value](const value_type &item) { return item - value; });
            return *this;
        }

        static_matrix &div(const value_type &value) {
            transform([&value](const value_type &item) { return item / value; });
            return *this;
        }

#if __cplusplus > 201703L
        template<fundamental U, size_type Rows2, size_type Cols2>
        requires(non_zero_dimension<Rows2, Cols2> and std::convertible_to<U, T> and Cols == Rows2)
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols2> mul(const static_matrix<U, Rows2, Cols2> &rhs) const {
#else
        template<typename U, size_type Rows2, size_type Cols2>
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols2> mul(const static_matrix<U, Rows2, Cols2> &rhs) const {
            static_assert(Rows2 != 0 and Cols2 != 0 and std::is_convertible<U, T>::value and Cols == Rows2);
#endif // C++ <= 201703L
            static_matrix<T, Rows, Cols2> multiplied;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols2; ++col)
                    for (size_type k = 0; k != Cols; ++k)
                        multiplied(row, col) += (*this)(row, k) * rhs(k, col);

            return multiplied;
        }

#if __cplusplus > 201703L
        template<fundamental U>
        requires(std::convertible_to<U, T>)
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> add(const static_matrix<U, Rows, Cols> &rhs) const {
#else
        template<typename U>
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> add(const static_matrix<U, Rows, Cols> &rhs) const {
            static_assert(std::is_convertible<U, T>::value, "Container::value_type must be convertible to T");
#endif // C++ <= 201703L
            static_matrix<T, Rows, Cols> addition;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols; ++col)
                    addition(row, col) = (*this)(row, col) + rhs(row, col);

            return addition;
        }

#if __cplusplus > 201703L
        template<fundamental U>
        requires(std::convertible_to<U, T>)
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> sub(const static_matrix<U, Rows, Cols> &rhs) const {
#else
        template<typename U>
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> sub(const static_matrix<U, Rows, Cols> &rhs) const {
            static_assert(std::is_convertible<U, T>::value, "Container::value_type must be convertible to T");
#endif // C++ <= 201703L
            static_matrix<T, Rows, Cols> substraction;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols; ++col)
                    substraction(row, col) = (*this)(row, col) - rhs(row, col);

            return substraction;
        }

#if __cplusplus > 201703L
        template<fundamental U>
        requires(std::convertible_to<U, T>)
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> div_by_element(const static_matrix<U, Rows, Cols> &rhs) const {
#else
        template<typename U>
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> div_by_element(const static_matrix<U, Rows, Cols> &rhs) const {
            static_assert(std::is_convertible<U, T>::value, "Container::value_type must be convertible to T");
#endif // C++ <= 201703L
            static_matrix<T, Rows, Cols> division;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols; ++col)
                    division(row, col) = (*this)(row, col) / rhs(row, col);

            return division;
        }

#if __cplusplus > 201703L
        template<fundamental U>
        requires(std::convertible_to<U, T>)
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> mul_by_element(const static_matrix<U, Rows, Cols> &rhs) const {
#else
        template<typename U>
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> mul_by_element(const static_matrix<U, Rows, Cols> &rhs) const {
            static_assert(std::is_convertible<U, T>::value, "Container::value_type must be convertible to T");
#endif // C++ <= 201703L
            static_matrix<T, Rows, Cols> multpipled;

            for (size_type row = 0; row != Rows; ++row)
                for (size_type col = 0; col != Cols; ++col)
                    multpipled(row, col) = (*this)(row, col) * rhs(row, col);

            return multpipled;
        }

        _GLIBCXX17_CONSTEXPR value_type sum() const {
            return std::accumulate(begin(), end(), value_type{});
        }

    public:
        _GLIBCXX17_CONSTEXPR static_matrix<T, Cols, Rows> transpose() const {
            static_matrix<T, Cols, Rows> transposed;

            for (size_type row = 0; row != rows_; ++row)
                for (size_type col = 0; col != cols_; ++col)
                    transposed(col, row) = (*this)(row, col);

            return transposed;
        }

#if __cplusplus > 201703L
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows - 1, Cols - 1> minor(size_type row, size_type col) const requires (non_zero_dimension<Rows - 1, Cols - 1>) {
#else
        _GLIBCXX17_CONSTEXPR static_matrix<T, Rows - 1, Cols - 1> minor(size_type row, size_type col) const {
#endif // C++ <= 201703L
            static_matrix<T, Rows - 1, Cols - 1> minored;

            size_type skip_row = 0, skip_col = 0;
            for (size_type r = 0; r != minored.rows(); ++r) {
                if (row == r) skip_row = 1;
                skip_col = 0;
                for (size_type c = 0; c != minored.cols(); ++c) {
                    if (col == c) skip_col = 1;
                    minored(r, c) = (*this)(r + skip_row, c + skip_col);
                }
            }

            return minored;
        }


        _GLIBCXX17_CONSTEXPR value_type minor_item(size_type row, size_type col) const {
            return minor(row, col).determinant();
        }

#if __cplusplus > 201703L
        _GLIBCXX17_CONSTEXPR value_type determinant() const requires(Rows == Cols) {
#else
        _GLIBCXX17_CONSTEXPR value_type determinant() const {
            static_assert(Rows == Cols, "Matrix must be square");
#endif // C++ <= 201703L
            value_type determinant_value{};
            int sign = 1;

#if __cplusplus > 201703L
            if _GLIBCXX17_CONSTEXPR (Rows == 1 and Cols == 1)
                determinant_value = (*this)(0, 0);
            else if _GLIBCXX17_CONSTEXPR (Rows == 2 and Cols == 2)
                determinant_value = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
#else
            if (Rows == 1 and Cols == 1)
                determinant_value = (*this)(0, 0);
            else if (Rows == 2 and Cols == 2)
                determinant_value = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
#endif // C++ <= 201703L
            else {
                for (size_type col = 0; col != Cols; ++col) {
                    static_matrix<value_type, Rows - 1, Cols - 1> minored = this->minor(0, col);
                    determinant_value += sign * (*this)(0, col) * minored.determinant();
                    sign = -sign;
                }
            }

            return determinant_value;
        }

#if __cplusplus > 201703L
        _GLIBCXX17_CONSTEXPR static_matrix calc_complements() const requires(Rows == Cols) {
#else
        _GLIBCXX17_CONSTEXPR static_matrix calc_complements() const {
            static_assert(Rows == Cols, "Matrix must be square");
#endif // C++ <= 201703L
            static_matrix<value_type, Rows, Cols> complements;
            for (size_type row = 0; row != Rows; ++row) {
                for (size_type col = 0; col != Cols; ++col) {
                    complements(row, col) = minor_item(row, col);
                    if ((row + col) % 2 != 0) complements(row, col) = -complements(row, col);
                }
            }

            return complements;
        }

#if __cplusplus > 201703L
        _GLIBCXX17_CONSTEXPR static_matrix inverse() const requires(Rows == Cols) {
#else
        _GLIBCXX17_CONSTEXPR static_matrix inverse() const {
            static_assert(Rows == Cols, "Matrix must be square");
#endif // C++ <= 201703L
            value_type det = determinant();

            if (det != value_type{})
                return calc_complements().transpose().mul_by_element(static_matrix<T, Rows, Cols>(1 / determinant()));

            return zero();
        }

#if __cplusplus > 201703L
        _GLIBCXX17_CONSTEXPR value_type trace() const requires(Rows == Cols) {
#else
        _GLIBCXX17_CONSTEXPR value_type trace() const {
            static_assert(Rows == Cols, "Matrix must be square");
#endif // C++ <= 201703L
            value_type tr{};
            for (size_type i = 0; i != Rows; ++i)
                tr += (*this)(i, i);
            return tr;
        }

    public:
#if __cplusplus > 201703L

        template<fundamental U = T>
        requires(std::convertible_to<U, T>)
        _GLIBCXX17_CONSTEXPR std::array<U, Rows * Cols> to_array() const {
#else
        template <typename U = T>
        _GLIBCXX17_CONSTEXPR std::array<U, Rows * Cols> to_array() const {
            static_assert(std::is_fundamental<U>::value, "Template parameter U must be fundamental");
            static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
            std::array<U, Rows * Cols> arr;

            size_type current = 0;
            for (size_type row = 0; row != rows_; ++row)
                for (size_type col = 0; col != cols_; ++col)
                    arr[current++] = (*this)(row, col);

            return arr;
        }

#if __cplusplus > 201703L
        template<fundamental U>
        requires(std::convertible_to<U, T>)
        _GLIBCXX17_CONSTEXPR static_matrix<U, Rows, Cols> convert_to() const {
#else
            template <typename U>
            _GLIBCXX17_CONSTEXPR static_matrix<U, Rows, Cols> convert_to() const {
                static_assert(std::is_fundamental<U>::value, "Template parameter U must be fundamental");
                static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
            static_matrix<U, Rows, Cols> converted;

            for (size_type row = 0; row != rows_; ++row)
                for (size_type col = 0; col != cols_; ++col)
                    converted(row, col) = (*this)(row, col);

            return converted;
        }

    public:
        _GLIBCXX17_CONSTEXPR bool equal_to(const static_matrix &rhs) const {
            T epsilon;
            _GLIBCXX17_CONSTEXPR bool is_bool = std::is_same<bool, T>::value;

#if __cplusplus >= 201703L
            if _GLIBCXX17_CONSTEXPR (!is_bool)
#else
            if (!is_bool)
#endif // C++ <= 201703L
                epsilon = matrix_epsilon<T>::epsilon;

            for (size_type row = 0; row != Rows; ++row) {
                for (size_type col = 0; col != Cols; ++col) {
                    value_type left = (*this)(row, col), right = rhs(row, col);

#if __cplusplus >= 201703L
                    if _GLIBCXX17_CONSTEXPR (is_bool) {
#else
                    if (is_bool) {
#endif // C++ <= 201703L
                        if (left != right)
                            return false;
                    } else {
                        if (left < 0) left = -left;
                        if (right < 0) right = -right;

                        if (left - right > epsilon)
                            return false;
                    }
                }
            }

            return true;
        }

    private:
        size_type rows_ = Rows, cols_ = Cols;
        value_type data_[Rows * Cols]{};
    };

#if __cplusplus > 201703L
    template<fundamental T, std::size_t Rows, std::size_t Cols>
    std::ostream &operator<<(std::ostream &out, const static_matrix<T, Rows, Cols> &rhs) {
#else
    template <typename T, std::size_t Rows, std::size_t Cols>
    std::ostream &operator<<(std::ostream &out, const static_matrix<T, Rows, Cols> &rhs) {
#endif // C++ <= 201703L
        rhs.print(out);
        return out;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator+(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator+(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        static_matrix<T, Rows, Cols> addition = lhs.add(static_matrix<T, Rows, Cols>(value));
        return addition;
    }

#if __cplusplus > 201703L
    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Rows1 == Rows2 and Cols1 == Cols2)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows1, Cols1> operator+(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs) {
#else
    template <typename T, typename U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows1, Cols1> operator+(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
        static_assert(Rows1 == Rows2 and Cols1 == Cols2, "Matrix sizes must be same");
#endif // C++ <= 201703L
        static_matrix<T, Rows1, Cols1> addition = lhs.add(rhs);
        return addition;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator+=(static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    static_matrix<T, Rows, Cols> &operator+=(static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        lhs.add(value);
        return lhs;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator-(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator-(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        static_matrix<T, Rows, Cols> substract = lhs.sub(static_matrix<T, Rows, Cols>(value));
        return substract;
    }

#if __cplusplus > 201703L
    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Rows1 == Rows2 and Cols1 == Cols2)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows1, Cols1> operator-(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs) {
#else
    template <typename T, typename U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows1, Cols1> operator-(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
        static_assert(Rows1 == Rows2 and Cols1 == Cols2, "Matrix sizes must be same");
#endif // C++ <= 201703L
        static_matrix<T, Rows1, Cols1> substract = lhs.sub(rhs);
        return substract;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator-=(static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    static_matrix<T, Rows, Cols> &operator-=(static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        lhs.sub(value);
        return lhs;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator*(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator*(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        static_matrix<T, Rows, Cols> multiplication = lhs.mul_by_element(static_matrix<T, Rows, Cols>(value));
        return multiplication;
    }

#if __cplusplus > 201703L
    template <fundamental T, fundamental U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    requires (std::convertible_to<U, T> and Cols1 == Rows2)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows1, Cols2> operator*(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs) {
#else
    template <typename T, typename U, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows1, Cols2> operator*(const static_matrix<T, Rows1, Cols1> &lhs, const static_matrix<U, Rows2, Cols2> &rhs) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
        static_assert(Cols1 == Rows2, "Cols1 must be equal Rows2");
#endif // C++ <= 201703L
        static_matrix<T, Rows1, Cols2> multiplication = lhs.mul(rhs);
        return multiplication;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator*=(static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    static_matrix<T, Rows, Cols> &operator*=(static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        lhs.mul(value);
        return lhs;
    }

#if __cplusplus > 201703L
    template<fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator/(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
#else
    template<typename T, typename U, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR static_matrix<T, Rows, Cols> operator/(const static_matrix<T, Rows, Cols> &lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        static_matrix<T, Rows, Cols> division = lhs.div_by_element(static_matrix<T, Rows, Cols>(value));
        return division;
    }

#if __cplusplus > 201703L
    template <fundamental T, fundamental U, std::size_t Rows, std::size_t Cols>
    requires (std::convertible_to<U, T>)
    static_matrix<T, Rows, Cols> &operator/=(static_matrix<T, Rows, Cols>&lhs, const U &value) {
#else
    template <typename T, typename U, std::size_t Rows, std::size_t Cols>
    static_matrix<T, Rows, Cols> &operator/=(static_matrix<T, Rows, Cols>&lhs, const U &value) {
        static_assert(std::is_convertible<U, T>::value, "U must be convertible to T");
#endif // C++ <= 201703L
        lhs.div(value);
        return lhs;
    }

#if __cplusplus > 201703L
    template <fundamental T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR bool operator==(const static_matrix<T, Rows, Cols> &lhs, const static_matrix<T, Rows, Cols> &rhs) {
#else
    template <typename T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR bool operator==(const static_matrix<T, Rows, Cols> &lhs, const static_matrix<T, Rows, Cols> &rhs) {
#endif // C++ <= 201703L
        return lhs.equal_to(rhs);
    }

#if __cplusplus > 201703L
    template <fundamental T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR bool operator!=(const static_matrix<T, Rows, Cols> &lhs, const static_matrix<T, Rows, Cols> &rhs) {
#else
    template <typename T, std::size_t Rows, std::size_t Cols>
    [[__nodiscard__]] _GLIBCXX17_CONSTEXPR bool operator!=(const static_matrix<T, Rows, Cols> &lhs, const static_matrix<T, Rows, Cols> &rhs) {
#endif // C++ <= 201703L
        return !(lhs == rhs);
    }

#if __cplusplus <= 201703L
    template <typename T>
    class static_matrix<T, 0, 0> {
    public:
        T determinant() { return T{}; }
        static_matrix<T, 0, 0> minor(std::size_t, std::size_t) { return static_matrix<T, 0, 0>{}; };

        std::size_t rows() const noexcept { return 0; }
        std::size_t cols() const noexcept { return 0; }

        T &operator()(std::size_t, std::size_t) { return value_; }
        T operator()(std::size_t, std::size_t) const { return value_; }
    public:
        T value_;
    };
#endif // C++ <= 201703L
}

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_H
