#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#define DEFAULT_SIZE 3

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  void Create();
  void Free();
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  void* GetMatrixPtr();
  void Fill(const double values[]);
  // double GetValue(int i, int j);
  // void Print() const;

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix Minor(int row, int col);
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double& other) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double& other);
  double& operator()(int i, int j);
};
