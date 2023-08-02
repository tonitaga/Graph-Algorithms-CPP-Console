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

    private:
        size_type rows_ {}, cols_ {};
        std::vector<value_type> data_;
    };


    ///
    ///   Implementation of Matrix class
    ///


    template<typename T>
    Matrix<T>::Matrix(size_type rows, size_type cols, value_type fill)
        : rows_(rows), cols_(cols), data_(rows_ * cols_, fill)
    {
    }

    template<typename T>
    Matrix<T>::Matrix(size_type square, value_type fill)
        : Matrix(square, square, fill)
    {
    }


    template<typename T>
    typename Matrix<T>::reference Matrix<T>::operator()(size_type row, size_type col) {
        return data_[row * cols_ + col];
    }

    template<typename T>
    typename Matrix<T>::const_reference Matrix<T>::operator()(size_type row, size_type col) const {
        return data_[row * cols_ + col];
    }

    template <typename T>
    void Matrix<T>::setRows(size_type rows) {
        if (rows == rows_)
            return;
        rows_ = rows;
        data_.resize(rows_ * cols_);
    }

    template <typename T>
    void Matrix<T>::setCols(size_type cols) {
        if (cols == cols_)
            return;
        cols_ = cols;
        data_.resize(rows_ * cols_);
    }

    template <typename T>
    void Matrix<T>::Fill(value_type fill) {
        std::fill(data_.begin(), data_.end(), fill);
    }
}

#endif //GRAPHALGORITHMS_MATRIX_H
