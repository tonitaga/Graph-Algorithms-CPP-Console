#ifndef GRAPHALGORITHMS_MATRIX_H
#define GRAPHALGORITHMS_MATRIX_H

#include <cctype>
#include <vector>
#include <type_traits>

namespace ng {
    template <typename T>
    class Matrix final {
        static_assert(std::is_fundamental<T>::value, "Template parameter T must be fundamental");
    public:
        using size_type = std::size_t;
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;

    public:
        Matrix() noexcept = default;
        Matrix(size_type rows, size_type cols, value_type fill = value_type {});
        Matrix(size_type square, value_type fill = value_type {});

        size_type getRows() const noexcept { return rows_; }
        size_type getCols() const noexcept { return cols_; }
        size_type getElementCount() const noexcept { return rows_ * cols_; }

        void setRows(size_type rows);
        void setCols(size_type cols);

        void Fill(value_type fill = value_type {});

        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        bool operator==(const Matrix &other) const {
            return rows_ == other.rows_ and cols_ == other.cols_ and data_ == other.data_;
        }

    private:
        size_type rows_ {}, cols_ {};
        std::vector<value_type> data_;
    };

    template <typename T>
    constexpr T kInf = std::numeric_limits<T>::max();

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs);
}

#include "matrix.tpp"

#endif //GRAPHALGORITHMS_MATRIX_H
