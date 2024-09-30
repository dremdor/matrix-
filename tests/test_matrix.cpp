#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, SizeConstructor) {
  S21Matrix matrix(4, 4);
  EXPECT_EQ(matrix.GetRows(), 4);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix1(4, 4);
  S21Matrix matrix(matrix1);
  EXPECT_EQ(matrix.GetRows(), 4);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix1(4, 4);
  S21Matrix matrix(std::move(matrix1));
  EXPECT_EQ(matrix.GetRows(), 4);
  EXPECT_EQ(matrix.GetCols(), 4);

  EXPECT_EQ(matrix1.GetRows(), 0);
  EXPECT_EQ(matrix1.GetCols(), 0);
  EXPECT_EQ(matrix1.GetMatrixPtr(), nullptr);
}

TEST(S21MatrixTest, EqMatrix) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
  EXPECT_EQ(matrix2.EqMatrix(matrix1), true);
  S21Matrix matrix3(2, 2);
  S21Matrix matrix4(3, 3);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  EXPECT_EQ(matrix3.EqMatrix(matrix4), false);
  EXPECT_EQ(matrix4.EqMatrix(matrix3), false);
}

TEST(S21MatrixTest, SumMatrix) {
  double values[] = {1, 2, 3, 4};
  double answer[] = {2, 4, 6, 8};
  S21Matrix matrix1(2, 2);
  matrix1.Fill(values);
  S21Matrix matrix2(matrix1);
  matrix1.SumMatrix(matrix2);
  S21Matrix ans(2, 2);
  ans.Fill(answer);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

TEST(S21MatrixTest, SubMatrix) {
  double values[] = {2, 4, 6, 8};
  double values2[] = {1, 2, 3, 4};
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  matrix1.SubMatrix(matrix2);
  S21Matrix ans(2, 2);
  ans.Fill(values2);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

TEST(S21MatrixTest, MulNumber) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {2, 4, 6, 8};
  S21Matrix matrix1(2, 2);
  matrix1.Fill(values);
  matrix1.MulNumber(2);
  S21Matrix ans(2, 2);
  ans.Fill(values2);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

TEST(S21MatrixTest, MulMatrix) {
  double values[] = {5, 2, 3, 1};
  double values2[] = {4, 6, 5, 2};
  double answer[] = {30, 34, 17, 20};

  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  matrix1.MulMatrix(matrix2);
  S21Matrix ans(2, 2);
  ans.Fill(answer);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

TEST(S21MatrixTest, MulMatrix2) {
  double values[] = {1, 2, 2, 3, 1, 1};
  double values2[] = {4, 2, 3, 1, 1, 5};
  double answer[] = {12, 14, 16, 12};
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  matrix1.MulMatrix(matrix2);
  S21Matrix ans(2, 2);
  ans.Fill(answer);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

TEST(S21MatrixTest, TransposeMatrix) {
  double values[] = {1, 2, 3, 4, 5, 6};
  double answer[] = {1, 4, 2, 5, 3, 6};
  S21Matrix matrix1(2, 3);
  matrix1.Fill(values);
  S21Matrix matrix2 = matrix1.Transpose();
  S21Matrix ans(3, 2);
  ans.Fill(answer);
  EXPECT_EQ(matrix2.EqMatrix(ans), true);
}

TEST(S21MatrixTest, CalcComplements) {
  double values[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double answer[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  S21Matrix matrix1(3, 3);
  matrix1.Fill(values);
  S21Matrix matrix2 = matrix1.CalcComplements();
  S21Matrix ans(3, 3);
  ans.Fill(answer);
  EXPECT_EQ(matrix2.EqMatrix(ans), true);
}

TEST(S21MatrixTest, Determinant) {
  double values[] = {11, -3, -15, -2};
  S21Matrix matrix1(2, 2);
  matrix1.Fill(values);
  double result = matrix1.Determinant();
  EXPECT_EQ(result, -67);
}

TEST(S21MatrixTest, InverseMatrix) {
  double values[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double answer[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  S21Matrix matrix1(3, 3);
  matrix1.Fill(values);
  S21Matrix matrix2 = matrix1.InverseMatrix();
  S21Matrix ans(3, 3);
  ans.Fill(answer);
  EXPECT_EQ(matrix2.EqMatrix(ans), true);
}

TEST(S21MatrixTest, ExcSum) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTest, ExcSub) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTest, ExcMul) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTest, ExcCalc) {
  S21Matrix matrix1(3, 2);
  ASSERT_THROW(matrix1.CalcComplements(), std::invalid_argument);
}

TEST(S21MatrixTest, ExcDet) {
  S21Matrix matrix1(3, 2);
  ASSERT_THROW(matrix1.Determinant(), std::invalid_argument);
}

TEST(S21MatrixTest, ExcInverse) {
  S21Matrix matrix1(3, 2);
  ASSERT_THROW(matrix1.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, Exc2Inverse) {
  S21Matrix matrix1(2, 2);
  double values[] = {0, 0, 0, 0};
  matrix1.Fill(values);
  ASSERT_THROW(matrix1.InverseMatrix(), std::runtime_error);
}

TEST(S21MatrixTest, PlusMinusOp) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {2, 4, 6, 8};
  double values3[] = {3, 6, 9, 12};
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  S21Matrix matrix3 = matrix1 + matrix2;
  S21Matrix matrix4 = matrix2 - matrix1;
  S21Matrix ans(2, 2);
  S21Matrix ans2(2, 2);
  ans.Fill(values3);
  ans2.Fill(values);
  EXPECT_EQ(matrix3.EqMatrix(ans), true);
  EXPECT_EQ(matrix4.EqMatrix(ans2), true);
}

TEST(S21MatrixTest, ExcPlusMinusOp) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(S21Matrix matrix5 = matrix1 + matrix2;, std::invalid_argument);
  S21Matrix matrix3(3, 3);
  S21Matrix matrix4(2, 2);
  ASSERT_THROW(S21Matrix matrix6 = matrix3 - matrix4;, std::invalid_argument);
}

TEST(S21MatrixTest, EqOp) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {2, 4, 6, 8};
  double values3[] = {3, 6, 9, 12};
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  S21Matrix ans(2, 2);
  S21Matrix ans2(2, 2);
  ans.Fill(values3);
  ans2.Fill(values);
  EXPECT_EQ(matrix1 == matrix2, false);
  EXPECT_EQ(ans == (matrix1 + matrix2), true);
}

TEST(S21MatrixTest, PlusMinusEqOp) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {2, 4, 6, 8};
  double values3[] = {3, 6, 9, 12};
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix matrix3(2, 2);
  S21Matrix matrix4(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  matrix3.Fill(values3);
  matrix4.Fill(values);
  matrix1 += matrix2;
  EXPECT_EQ(matrix1 == matrix3, true);
  matrix3 -= matrix2;
  EXPECT_EQ(matrix4 == matrix3, true);
}

TEST(S21MatrixTest, ResizeMatrixIncrease) {
  double values[] = {1, 2, 3, 4};
  S21Matrix matrix(2, 2);
  matrix.Fill(values);
  matrix.SetRows(3);
  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
  double expected[] = {1, 2, 0, 3, 4, 0, 0, 0, 0};
  S21Matrix expected_matrix(3, 3);
  expected_matrix.Fill(expected);
  EXPECT_TRUE(matrix.EqMatrix(expected_matrix));
}

TEST(S21MatrixTest, ResizeMatrixDecrease) {
  double values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
  matrix.Fill(values);
  matrix.SetRows(2);
  matrix.SetCols(2);
  double expected[] = {1, 2, 4, 5};
  S21Matrix expected_matrix(2, 2);
  expected_matrix.Fill(expected);
  EXPECT_TRUE(matrix.EqMatrix(expected_matrix));
}

TEST(S21MatrixTest, ParentTest) {
  double values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  S21Matrix matrix(3, 3);
  matrix.Fill(values);
  EXPECT_EQ(matrix(0, 0), 1);
  EXPECT_EQ(matrix(0, 1), 2);
  EXPECT_EQ(matrix(0, 2), 3);
  EXPECT_EQ(matrix(1, 0), 4);
  EXPECT_EQ(matrix(1, 1), 5);
  EXPECT_EQ(matrix(1, 2), 6);
  EXPECT_EQ(matrix(2, 0), 7);
  EXPECT_EQ(matrix(2, 1), 8);
  EXPECT_EQ(matrix(2, 2), 9);
  EXPECT_THROW(matrix(4, 3), std::out_of_range);
  EXPECT_THROW(matrix(3, 4), std::out_of_range);
  EXPECT_THROW(matrix(-1, 3), std::out_of_range);
  EXPECT_THROW(matrix(3, -1), std::out_of_range);
}

TEST(S21MatrixTest, MulMatrixOp) {
  double values[] = {5, 2, 3, 1};
  double values2[] = {4, 6, 5, 2};
  double answer[] = {30, 34, 17, 20};

  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  S21Matrix matrix3 = matrix1 * matrix2;
  S21Matrix ans(2, 2);
  ans.Fill(answer);
  EXPECT_EQ(matrix3.EqMatrix(ans), true);
}

TEST(S21MatrixTest, ExcMulOp) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(S21Matrix matrix3 = matrix1 * matrix2, std::invalid_argument);
}

TEST(S21MatrixTest, MulAssMatrixOp) {
  double values[] = {5, 2, 3, 1};
  double values2[] = {4, 6, 5, 2};
  double answer[] = {30, 34, 17, 20};

  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1.Fill(values);
  matrix2.Fill(values2);
  matrix1 *= matrix2;
  S21Matrix ans(2, 2);
  ans.Fill(answer);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

TEST(S21MatrixTest, ExcAssMulOp) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(matrix1 *= matrix2, std::invalid_argument);
}

TEST(S21MatrixTest, MulNumberOp) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {2, 4, 6, 8};
  S21Matrix matrix1(2, 2);
  matrix1.Fill(values);
  S21Matrix matrix3 = matrix1 * 2;
  S21Matrix ans(2, 2);
  ans.Fill(values2);
  EXPECT_EQ(matrix3.EqMatrix(ans), true);
}

TEST(S21MatrixTest, MulAssNumberOp) {
  double values[] = {1, 2, 3, 4};
  double values2[] = {2, 4, 6, 8};
  S21Matrix matrix1(2, 2);
  matrix1.Fill(values);
  matrix1 *= 2;
  S21Matrix ans(2, 2);
  ans.Fill(values2);
  EXPECT_EQ(matrix1.EqMatrix(ans), true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
