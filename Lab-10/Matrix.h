#ifndef MATRIX_H_
#define MATRIX_H_

#include <array>
#include <iostream>

template<typename T, size_t H, size_t W>
class Matrix{
private:
    std::array<T, H*W> data_;
    size_t get_index(size_t row, size_t col) const;
    class Row;
public:
    Matrix(T value = 0);
    T get(size_t row, size_t column) const;
    void set(size_t row, size_t column, T value);
    void print(std::ostream& os = std::cout) const;
    Matrix& operator++();
    Matrix operator++(int);
    Row operator[](size_t row);
    const Row operator[](size_t row) const;
};

template<typename T, size_t H, size_t W>
class Matrix<T, H, W>::Row{
        friend class Matrix;
        private: 
            const Matrix& matrix_;
            size_t row_;
            Row(const Matrix& matrix, size_t row);
        public:
            T& operator[] (size_t column);
            const T& operator[] (size_t column) const;
};

template <typename T, size_t H, size_t W>
Matrix<T,H,W>::Row::Row(const Matrix& matrix, size_t row) : matrix_(matrix), row_(row){};

template <typename T, size_t H, size_t W>
T& Matrix<T,H,W>::Row::operator[](size_t column){
    return const_cast<T&>(matrix_.data_[row_ * W + column]);
};

template <typename T, size_t H, size_t W>
const T& Matrix<T, H, W>::Row::operator[] (size_t column) const{
    return matrix_.data_[row_ * W + column];
};

template <typename T, size_t H, size_t W>
typename Matrix<T,H,W>::Row Matrix<T,H,W>::operator[](size_t row){
    return Row(*this, row);
};

template <typename T, size_t H, size_t W>
const typename Matrix<T,H,W>::Row Matrix<T,H,W>::operator[](size_t row) const{
    return Row(*this, row);
}

template <typename T, size_t H, size_t W>
Matrix<T, H, W>::Matrix(T value){
    data_.fill(value);
};

template <typename T, size_t H, size_t W>
T Matrix<T, H, W>::get(size_t row, size_t column) const{
    return data_[row * W + column];
}

template <typename T, size_t H, size_t W>
void Matrix<T, H, W>::set(size_t row, size_t column, T value){
    data_[row * W + column] = value;
}

template <typename T, size_t H, size_t W>
void Matrix<T, H, W>::print(std::ostream& os) const{
    os << "[";
    for (size_t r = 0; r < H; ++r){
        os << "[";
        for (size_t c = 0; c < W; ++c){
            os << get(r,c);
            if (c != W-1)
                os << ", ";
        }
        os << "]";
        if (r != H-1)
            os << ", ";
    }
    os << "]";
}

template <typename T, size_t H, size_t W>
Matrix<T, H, W>& Matrix<T, H, W>::operator++(){
    for (auto it = data_.begin(); it != data_.end(); ++it){
        ++(*it);
    }
    return *this;
};

template <typename T, size_t H, size_t W>
Matrix<T, H, W> Matrix<T, H, W>::operator++(int){
    auto ret = Matrix<T, H, W>(*this);
    operator++();
    return ret;
};

template <typename T, size_t H, size_t W>
std::ostream& operator <<(std::ostream& os, const Matrix<T, H, W>& matrix){
    matrix.print(os);
    return os;
};

template <typename T, size_t H, size_t W>
Matrix<T, H, W> operator+(const Matrix<T, H, W>& matrix, T increment){
    auto ret = Matrix<T, H, W>(matrix);
    for (size_t r = 0; r < H; ++r) {
        for (size_t c = 0; c < W; ++c) {
            ret[r][c] += increment;
        }
    }
    return ret;
};

template <typename T, size_t H, size_t W>
Matrix<T, H, W> operator*(const Matrix<T, H, W>& matrix, T factor){
    auto ret = Matrix<T, H, W>(matrix);
    for (size_t r = 0; r < H; ++r) {
        for (size_t c = 0; c < W; ++c) {
            ret[r][c] *= factor;
        }
    }
    return ret;
};

template <typename T, size_t H, size_t W>
Matrix<T, H, W> operator+ (const Matrix<T, H, W>& matrix1, const Matrix<T,H,W>& matrix2){
    auto ret = Matrix<T, H, W>(matrix1);
    for (size_t r = 0; r < H; ++r) {
        for (size_t c = 0; c < W; ++c) {
            ret[r][c] = matrix1[r][c] + matrix2[r][c];
        }
    }
    return ret;
};

template <typename T, size_t M, size_t N, size_t O>
Matrix<T, M, O> operator*(const Matrix<T, M, N>& matrix1, const Matrix<T, N, O>& matrix2){
    auto ret = Matrix<T, M, O>();
    for (size_t r = 0; r < M; ++r) {
        for (size_t c = 0; c < O; c++) {
            for (size_t i = 0; i < N; ++i) {
                ret[r][c] += matrix1[r][i] * matrix2[i][c];
            }
        }
    }
    return ret;
};

#endif