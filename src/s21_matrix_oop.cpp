

#include "s21_matrix_oop.h"
#include <exception>
#include <utility>
#include <algorithm>
#include <cmath>

S21Matrix::S21Matrix() {
  setZeroMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  this->createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  this->setZeroMatrix();
  std::swap(this->rows, other.rows);
  std::swap(this->cols, other.cols);
  std::swap(this->matrix, other.matrix);
}

S21Matrix::~S21Matrix() {
  if (matrix != nullptr) {
    this->removeMatrix();
    this->setZeroMatrix();
  }
}
// some operators overloads

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (this->rows != other.rows || this->cols != other.cols)
    throw std::logic_error("different matrix dimensions");
  S21Matrix res(this->rows, this->cols);
  for (int i = 0; i < res.getRows(); ++i) {
    for (int j = 0; j < res.getCols(); ++j) {
      res[i][j] = (*this)[i][j] + other[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (this->rows != other.rows || this->cols != other.cols)
    throw std::logic_error("different matrix dimensions");
  S21Matrix res(this->rows, this->cols);
  for (int i = 0; i < res.getRows(); ++i) {
    for (int j = 0; j < res.getCols(); ++j) {
      res[i][j] = (*this)[i][j] - other[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {

  if (this->rows != other.cols || this->cols != other.rows)
    throw std::length_error("different matrix dimensions");
  S21Matrix res(this->rows, other.cols);

  for (int i = 0; i < res.getRows(); i++)
    for (int j = 0; j < res.getCols(); j++)
      for (int k = 0; k < this->cols; k++)
        res[i][j] += (*this)[i][k] * other[k][j];
  return res;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix res(this->rows, this->cols);
  for (int i = 0; i < res.getRows(); ++i) {
    for (int j = 0; j < res.getCols(); ++j) {
      res[i][j] = (*this)[i][j] * number;
    }
  }
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  if (this->rows != other.rows || this->cols != other.cols)
    return false;
  for (int i = 0; i < this->getRows(); i++)
    for (int j = 0; j < this->getCols(); j++)
      if (std::fabs((*this)[i][j] - other[i][j]) > 1e-07)
        return false;
  return true;
}

bool S21Matrix::eqMatrix(const S21Matrix &other) {
  return *this == other;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->copyMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  this->moveMatrix(std::move(other));
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (this->rows != other.cols || this->cols != other.rows)
    throw std::length_error("different matrix dimensions");

  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < this->cols; ++j) {
      (*this)[i][j] += other[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (this->rows != other.cols || this->cols != other.rows)
    throw std::length_error("different matrix dimensions");

  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < this->cols; ++j) {
      (*this)[i][j] -= other[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  S21Matrix res(this->rows, other.cols);
  res = *this * other;
  *this = std::move(res);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double number) {
  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < this->cols; ++j) {
      (*this)[i][j] = (*this)[i][j] * number;
    }
  }
  return *this;
}

void S21Matrix::sumMatrix(const S21Matrix &other) {
  *this += other;
}

void S21Matrix::subMatrix(const S21Matrix &other) {
  *this -= other;
}

void S21Matrix::mulNumber(double num) {
  *this *= num;
}

void S21Matrix::mulMatrix(const S21Matrix &other) {
  *this *= other;
}

S21Matrix S21Matrix::transpose() {
  S21Matrix res(this->cols, this->rows);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->cols; j++)
      res[j][i] = (*this)[i][j];
  return res;
}

double S21Matrix::determinant() {
  if (this->rows != this->cols || this->rows <= 0)
    throw std::length_error("the matrix is not square");

  if (this->rows == 1) return (*this)[0][0];
  if (this->rows == 2) {
    return ((*this)[0][0] * (*this)[1][1]) -
        ((*this)[0][1] * (*this)[1][0]);
  }

  S21Matrix tmp(*this);

  double multiplier = 0;
  double determinant = 1;
  double result = 0;

  for (int j = 0; j < this->cols - 1; j++) {  // collums
    for (int i = 1 + j; i < this->rows; i++) {  // rows
      if (tmp[j][j] == 0) {
        // try swap string
        if (!tmp.swapRows(j)) {
          result = 0;
          return result;
        } else {
          determinant *= -1;
          continue;
        }
      }
      multiplier = tmp[i][j] / tmp[j][j];
      tmp = tmp.subRowMultByMultiplier(i, j, multiplier);
    }
  }

  for (int i = 0; i < tmp.rows; i++) {
    determinant *= tmp[i][i];
  }
  result = determinant;

  // need del tmp?

  return result;
}

bool S21Matrix::swapRows(int position) {
  bool status = false;

  for (int i = position + 1; i < this->rows; i++) {
    if (*this[i][position] != 0) {
      status = true;
      double temp = 0;
      for (int j = 0; j < this->cols; j++) {
        temp = (*this)[position][j];
        (*this)[rows][j] = (*this)[i][j];
        (*this)[i][j] = temp;
      }
      break;
    }
  }
  return status;
}

S21Matrix S21Matrix::subRowMultByMultiplier(int originRow, int subRow, double multiplier) {
  for (int i = 0; i < this->cols; i++) {
    (*this)[originRow][i] -= (*this)[subRow][i] * multiplier;
  }
  return *this;
}

S21Matrix S21Matrix::calcComplements() {
  if (this->rows != this->cols || this->rows <= 0)
    throw std::length_error("the matrix is not square");

  S21Matrix res(this->rows, this->cols);

  res = this->minorMatrix();

  for (int i = 0; i < res.rows; i++) {
    for (int j = 0; j < res.cols; j++) {
      res[i][j] *= pow(-1, i + j);
    }
  }

  return res;
}

S21Matrix S21Matrix::minorMatrix() {

  if (this->rows - 1 <= 0 || this->cols - 1 <= 0)
    throw std::length_error("incorrect matrix size");

  S21Matrix temp(this->rows - 1, this->cols - 1);
  S21Matrix minor(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {

        temp = this->getDecMatrix(temp, i, j);

        minor[i][j] = temp.determinant();

      }
    }

//  s21_remove_matrix(&temp);

  return minor;
}

S21Matrix S21Matrix::getDecMatrix(S21Matrix &other, int rowIndex, int colIndex) {


  for (int i = 0, a = 0; i < this->rows; i++) {
    if (rowIndex != i) {
      for (int j = 0, b = 0; j < this->rows; j++) {
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


// getters and setters

int S21Matrix::getRows() const {
  return rows;
}
int S21Matrix::getCols() const {
  return cols;
}
double *S21Matrix::getMatrix() const {
  return matrix;
}

void S21Matrix::setRows(int new_rows) {
  if (new_rows <= 0)
    throw std::length_error("Array size can't be zero");

  S21Matrix tmp(new_rows, this->cols);
  for (int i = 0; i < (new_rows < this->rows ? new_rows : this->rows); ++i) {
    for (int j = 0; j < this->cols; ++j) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  this->moveMatrix(std::move(tmp));
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols <= 0)
    throw std::length_error("Array size can't be zero");

  S21Matrix tmp(this->rows, new_cols);
  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < (new_cols < this->cols ? new_cols : this->cols); ++j) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  this->moveMatrix(std::move(tmp));
}

// assignment operator overload

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows || col >= cols) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix[row * cols + col];
}

double *S21Matrix::operator[](int row) const {
  if (row >= this->rows)
    throw std::out_of_range("Incorrect input, index is out of range");
  return row * this->cols + this->matrix;
}

// support function

void S21Matrix::setZeroMatrix() {
  this->cols = 0;
  this->rows = 0;
  this->matrix = nullptr;
}

void S21Matrix::createMatrix() {
  this->matrix = new double[rows * cols]{};
}

void S21Matrix::removeMatrix() {
  delete[] this->matrix;
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  this->rows = other.rows;
  this->cols = other.cols;
  this->createMatrix();
  std::copy(other.matrix, other.matrix + rows * cols, this->matrix);
}

void S21Matrix::moveMatrix(S21Matrix &&other) {
  this->removeMatrix();
  this->setZeroMatrix();
  std::swap(this->rows, other.rows);
  std::swap(this->cols, other.cols);
  std::swap(this->matrix, other.matrix);
}
