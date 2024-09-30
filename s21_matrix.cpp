#include "s21_matrix_oop.h"

void S21Matrix::Create() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::Free() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows_ != rows) {
    S21Matrix temp(rows, cols_);

    for (int i = 0; i < std::min(rows, rows_); ++i) {
      for (int j = 0; j < cols_; ++j) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    std::swap(*this, temp);
  }
}
void S21Matrix::SetCols(int cols) {
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < std::min(cols, cols_); ++j) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    std::swap(*this, temp);
  }
}

void* S21Matrix::GetMatrixPtr() { return matrix_; }

// double S21Matrix::GetValue(int i, int j) {
//     return matrix_[i][j];
// }

void S21Matrix::Fill(const double values[]) {
  int count = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = values[count++];
    }
  }
}

// void S21Matrix::Print() const {
//     for (int i = 0; i < rows_; ++i) {
//             for (int j = 0; j < cols_; ++j) {
//                 std::cout << matrix_[i][j] << " ";
//             }
//             std::cout << std::endl;
//         }
//     std::cout << std::endl;
// }

S21Matrix::S21Matrix() : rows_(DEFAULT_SIZE), cols_(DEFAULT_SIZE) { Create(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  Create();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  Create();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { Free(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool equal = true;

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) equal = false;
      }
    }
  } else
    equal = false;

  return equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }

  S21Matrix mul(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      double sum = 0;
      for (int k = 0; k < cols_; ++k) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      mul.matrix_[i][j] = sum;
    }
  }

  *this = mul;
}

S21Matrix S21Matrix::Transpose() {
  int n = rows_;
  int m = cols_;
  S21Matrix transp(m, n);

  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      transp.matrix_[j][i] = matrix_[i][j];
    }
  }

  return transp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }

  int n = rows_;
  S21Matrix calc(n, n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int sign = (i + j) % 2 == 0 ? 1 : -1;

      S21Matrix minor = this->Minor(i, j);

      calc.matrix_[i][j] = sign * minor.Determinant();
    }
  }

  return calc;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double det = 0.0;
  int n = rows_;

  for (int j = 0; j < n; ++j) {
    int sign = pow(-1, j);

    S21Matrix sub_matrix = this->Minor(0, j);
    double sub_det = sub_matrix.Determinant();

    det += sign * matrix_[0][j] * sub_det;
  }

  return det;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  int n = rows_;
  S21Matrix minor_matrix(n - 1, n - 1);

  int shift_i = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (i == row) shift_i = 1;
    int shift_j = 0;
    for (int j = 0; j < n - 1; ++j) {
      if (j == col) shift_j = 1;
      minor_matrix.matrix_[i][j] = matrix_[i + shift_i][j + shift_j];
    }
  }

  return minor_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }

  double det = this->Determinant();
  if (det == 0) {
    throw std::runtime_error("Matrix determinant is 0.");
  }

  S21Matrix calc = this->CalcComplements();

  S21Matrix transp_calc = calc.Transpose();

  transp_calc.MulNumber(1.0 / det);

  return transp_calc;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions.");
  }

  S21Matrix res(*this);
  res.SumMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions.");
  }

  S21Matrix res(*this);
  res.SubMatrix(other);

  return res;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator*(const double& other) const {
  S21Matrix res(*this);
  res.MulNumber(other);

  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) { this->SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { this->SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { this->MulMatrix(other); }

void S21Matrix::operator*=(const double& other) { this->MulNumber(other); }

S21Matrix& S21Matrix::operator=(S21Matrix other) {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index is outside the matrix.");
  }
  return matrix_[i][j];
}
