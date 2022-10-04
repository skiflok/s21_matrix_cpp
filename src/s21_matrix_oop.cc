#include "s21_matrix_oop.h"

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <utility>

namespace s21_matrix_oop {

S21Matrix::S21Matrix() { SetZeroMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  this->CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->CreateMatrix();
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, this->matrix_);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  this->SetZeroMatrix();
  std::swap(this->rows_, other.rows_);
  std::swap(this->cols_, other.cols_);
  std::swap(this->matrix_, other.matrix_);
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    this->RemoveMatrix();
    this->SetZeroMatrix();
  }
}
// some operators overloads

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::logic_error("different matrix dimensions");
  S21Matrix res(this->rows_, this->cols_);
  for (int i = 0; i < res.GetRows(); ++i) {
    for (int j = 0; j < res.GetCols(); ++j) {
      res[i][j] = (*this)[i][j] + other[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::logic_error("different matrix dimensions");
  S21Matrix res(this->rows_, this->cols_);
  for (int i = 0; i < res.GetRows(); ++i) {
    for (int j = 0; j < res.GetCols(); ++j) {
      res[i][j] = (*this)[i][j] - other[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if (this->rows_ != other.cols_ || this->cols_ != other.rows_)
    throw std::length_error("different matrix dimensions");
  S21Matrix res(this->rows_, other.cols_);

  for (int i = 0; i < res.GetRows(); i++)
    for (int j = 0; j < res.GetCols(); j++)
      for (int k = 0; k < this->cols_; k++)
        res[i][j] += (*this)[i][k] * other[k][j];
  return res;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix res(this->rows_, this->cols_);
  for (int i = 0; i < res.GetRows(); ++i) {
    for (int j = 0; j < res.GetCols(); ++j) {
      res[i][j] = (*this)[i][j] * number;
    }
  }
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;
  for (int i = 0; i < this->GetRows(); i++)
    for (int j = 0; j < this->GetCols(); j++)
      if (std::fabs((*this)[i][j] - other[i][j]) > 1e-07) return false;
  return true;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) { return *this == other; }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->CopyMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  this->MoveMatrix(std::move(other));
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (this->rows_ != other.cols_ || this->cols_ != other.rows_)
    throw std::length_error("different matrix dimensions");

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      (*this)[i][j] += other[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (this->rows_ != other.cols_ || this->cols_ != other.rows_)
    throw std::length_error("different matrix dimensions");

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      (*this)[i][j] -= other[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  S21Matrix res(this->rows_, other.cols_);
  res = *this * other;
  *this = std::move(res);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double number) {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      (*this)[i][j] = (*this)[i][j] * number;
    }
  }
  return *this;
}

void S21Matrix::SumMatrix(const S21Matrix &other) { *this += other; }

void S21Matrix::SubMatrix(const S21Matrix &other) { *this -= other; }

void S21Matrix::MulNumber(double num) { *this *= num; }

void S21Matrix::MulMatrix(const S21Matrix &other) { *this *= other; }

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) res[j][i] = (*this)[i][j];
  return res;
}

double S21Matrix::Determinant() {
  if (this->rows_ != this->cols_ || this->rows_ <= 0)
    throw std::length_error("the matrix is not square");

  if (this->rows_ == 1) return (*this)[0][0];
  if (this->rows_ == 2) {
    return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);
  }

  S21Matrix tmp(*this);

  double multiplier = 0;
  double determinant = 1;
  double result = 0;

  for (int j = 0; j < this->cols_ - 1; j++) {    // collums
    for (int i = 1 + j; i < this->rows_; i++) {  // rows
      if (tmp[j][j] == 0) {
        // try swap string
        if (!tmp.SwapRows(j)) {
          result = 0;
          return result;
        } else {
          determinant *= -1;
          continue;
        }
      }
      multiplier = tmp[i][j] / tmp[j][j];
      tmp = tmp.SubRowMultByMultiplier(i, j, multiplier);
    }
  }

  for (int i = 0; i < tmp.rows_; i++) {
    determinant *= tmp[i][i];
  }
  result = determinant;

  // need del tmp?

  return result;
}

bool S21Matrix::SwapRows(int position) {
  bool status = false;

  for (int i = position + 1; i < this->rows_; i++) {
    if ((*this)[i][position] != 0) {
      status = true;
      double temp = 0;
      for (int j = 0; j < this->cols_; j++) {
        temp = (*this)[position][j];
        (*this)[position][j] = (*this)[i][j];
        (*this)[i][j] = temp;
      }
      break;
    }
  }
  return status;
}

S21Matrix S21Matrix::SubRowMultByMultiplier(int originRow, int subRow,
                                            double multiplier) {
  for (int i = 0; i < this->cols_; i++) {
    (*this)[originRow][i] -= (*this)[subRow][i] * multiplier;
  }
  return *this;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_ || this->rows_ <= 0)
    throw std::length_error("the matrix is not square");

  S21Matrix res(this->rows_, this->cols_);

  res = this->MinorMatrix();

  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      res[i][j] *= pow(-1, i + j);
    }
  }

  return res;
}

S21Matrix S21Matrix::MinorMatrix() {
  if (this->rows_ - 1 <= 0 || this->cols_ - 1 <= 0)
    throw std::length_error("incorrect matrix size");

  S21Matrix temp(this->rows_ - 1, this->cols_ - 1);
  S21Matrix minor(this->rows_, this->cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp = this->GetDecMatrix(temp, i, j);

      minor[i][j] = temp.Determinant();
    }
  }

  return minor;
}

S21Matrix S21Matrix::GetDecMatrix(S21Matrix &other, int rowIndex,
                                  int colIndex) {
  for (int i = 0, a = 0; i < this->rows_; i++) {
    if (rowIndex != i) {
      for (int j = 0, b = 0; j < this->rows_; j++) {
        if (colIndex != j) {
          other[a][b] = (*this)[i][j];
          b++;
        }
      }
      a++;
    }
  }
  return other;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (this->rows_ != this->cols_ || this->rows_ <= 0)
    throw std::length_error("the matrix is not square");

  double det = this->Determinant();
  if (std::fabs(det) < 1e-06)
    throw std::logic_error("Determinant can't be zero to calculate inverse");

  S21Matrix tmp = this->CalcComplements().Transpose();
  S21Matrix res(this->rows_, this->cols_);

  res = tmp * (1 / det);

  return res;
}

// getters and setters

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }
double *S21Matrix::GetMatrix() const { return matrix_; }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) throw std::length_error("Array size can't be zero");

  S21Matrix tmp(new_rows, this->cols_);
  for (int i = 0; i < (new_rows < this->rows_ ? new_rows : this->rows_); ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  this->MoveMatrix(std::move(tmp));
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols <= 0) throw std::length_error("Array size can't be zero");

  S21Matrix tmp(this->rows_, new_cols);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < (new_cols < this->cols_ ? new_cols : this->cols_);
         ++j) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  this->MoveMatrix(std::move(tmp));
}

// assignment operator overload

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

double *S21Matrix::operator[](int row) const {
  if (row >= this->rows_)
    throw std::out_of_range("Incorrect input, index is out of range");
  return row * this->cols_ + this->matrix_;
}

// support function

void S21Matrix::SetZeroMatrix() {
  this->cols_ = 0;
  this->rows_ = 0;
  this->matrix_ = nullptr;
}

void S21Matrix::CreateMatrix() {
  if (this->rows_ <= 0 || this->cols_ <= 0)
    throw std::out_of_range("Incorrect input, index is out of range");
  this->matrix_ = new double[rows_ * cols_]{};
}

void S21Matrix::RemoveMatrix() { delete[] this->matrix_; }

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  if (this != &other) {
    delete[] matrix_;
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->CreateMatrix();
    std::copy(other.matrix_, other.matrix_ + rows_ * cols_, this->matrix_);
  }
}

void S21Matrix::MoveMatrix(S21Matrix &&other) {
  this->RemoveMatrix();
  this->SetZeroMatrix();
  std::swap(this->rows_, other.rows_);
  std::swap(this->cols_, other.cols_);
  std::swap(this->matrix_, other.matrix_);
}

}  // namespace s21_matrix_oop