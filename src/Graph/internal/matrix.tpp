#ifndef GRAPHALGORITHMS_MATRIX_TPP
#define GRAPHALGORITHMS_MATRIX_TPP

#include "matrix.h"

#include <iomanip>
#include <iostream>

namespace ng {

    ///
    ///   Implementation of Matrix class
    ///

    template<typename T>
    Matrix<T>::Matrix(size_type rows, size_type cols, value_type fill)
            : rows_(rows), cols_(cols), data_(rows_ * cols_, fill) {}

    template<typename T>
    Matrix<T>::Matrix(size_type square, value_type fill)
            : Matrix(square, square, fill) {}


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

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs) {
        for (std::size_t row = 0, rows = rhs.getRows(); row != rows; ++row) {
            for (std::size_t col = 0, cols = rhs.getCols(); col != cols; ++col) {
                if (rhs(row, col) == kInf<T>)
                    out << std::setw(4) << T{};
                else
                    out << std::setw(4) << rhs(row, col);
            }
            if (row != rows - 1)
                out << std::endl;
        }

        return out;
    }
}

#endif //GRAPHALGORITHMS_MATRIX_TPP
