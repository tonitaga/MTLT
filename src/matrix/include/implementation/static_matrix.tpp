#ifndef MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP
#define MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP

#include "static_matrix.h"

namespace ng {
    template <typename T, std::size_t Rows, std::size_t Cols>
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(value_type fill) noexcept {
        std::fill(begin(), end(), fill);
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(const Matrix<T> &other) {
        *this = other;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    template <typename Container>
    constexpr StaticMatrix<T, Rows, Cols>::StaticMatrix(const Container &container) {
        if (Rows * Cols != container.size())
            throw std::logic_error("container has more/less items than in matrix");

        if (!std::is_convertible_v<value_type, typename Container::value_type>)
            throw std::logic_error("Can't convert Container::value_type to StaticMatrix::value_type");

        std::copy(container.begin(), container.end(), begin());
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    constexpr StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::operator=(const Matrix<T> &other) {
        if (Rows != other.rows() or Cols != other.cols())
            throw std::logic_error("Can't copy data from other dimension sized matrix");

        std::copy(other.begin(), other.end(), begin());
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::reference StaticMatrix<T, Rows, Cols>::operator()(size_type row, size_type col) {
        return data_[row * cols_ + col];
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::const_reference StaticMatrix<T, Rows, Cols>::operator()(size_type row, size_type col) const {
        return data_[row * cols_ + col];
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::reference StaticMatrix<T, Rows, Cols>::at(size_type row, size_type col) {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of matrix bounds");
        return (*this)(row, col);
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::const_reference StaticMatrix<T, Rows, Cols>::at(size_type row, size_type col) const {
        if (row >= rows_ or col >= cols_)
            throw std::out_of_range("row or col is out of matrix bounds");
        return (*this)(row, col);
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::size_type StaticMatrix<T, Rows, Cols>::rows() const noexcept {
        return rows_;
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::size_type StaticMatrix<T, Rows, Cols>::cols() const noexcept {
        return cols_;
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    void StaticMatrix<T, Rows, Cols>::print(std::ostream &os, MatrixDebugSettings settings) const {
        auto [width, precision, separator, end, is_double_end] = settings;

        for (size_type row = 0; row != rows_; ++row) {
            for (size_type col = 0; col != cols_; ++col) {
                os << std::setw(width)
                   << std::setprecision(precision)
                   << (*this)(row, col)
                   << separator;
            }
            os << end;
        }

        if (is_double_end)
            os << end;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    template <typename UnaryOperation>
    void StaticMatrix<T, Rows, Cols>::transform(UnaryOperation &&op) {
        std::transform(begin(), end(), begin(), std::forward<UnaryOperation>(op));
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    template <typename BinaryOperation>
    void StaticMatrix<T, Rows, Cols>::transform(const StaticMatrix &other, BinaryOperation &&op) {
        std::transform(begin(), end(), other.begin(), begin(), std::forward<BinaryOperation>(op));
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    template <typename Operation>
    void StaticMatrix<T, Rows, Cols>::generate(Operation &&op) {
        std::generate(begin(), end(), std::forward<Operation>(op));
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::fill(const value_type &number) {
        std::fill(begin(), end(), number);
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::fill_random(const value_type &left, const value_type &right) {
        using namespace std::chrono;

        std::default_random_engine re(system_clock::now().time_since_epoch().count());
        auto distribution = std::conditional_t<std::is_integral_v<T>,
                std::uniform_int_distribution<T>,
                std::uniform_real_distribution<T>>(left, right);

        generate([&distribution, &re]() {
            return distribution(re);
        });

        return *this;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::round() {
        transform([](const value_type &item) { return std::round(item); });
        return *this;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::floor() {
        transform([](const value_type &item) { return std::floor(item); });
        return *this;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::ceil() {
        transform([](const value_type &item) { return std::ceil(item); });
        return *this;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::zero() {
        generate([]() { return value_type{}; });
        return *this;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    StaticMatrix<T, Rows, Cols> &StaticMatrix<T, Rows, Cols>::to_identity() {
        if (Rows != Cols)
            throw std::logic_error("Only square matrices can be identity");

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                (*this)(row, col) = row == col ? value_type{1} : value_type{};

        return *this;
    }

    template <typename T, std::size_t Rows, std::size_t Cols>
    typename StaticMatrix<T, Rows, Cols>::value_type StaticMatrix<T, Rows, Cols>::sum() const {
        return std::accumulate(begin(), end(), value_type{});
    }
}

#endif //MATRIX_LIBRARY_CPP_STATIC_MATRIX_TPP
