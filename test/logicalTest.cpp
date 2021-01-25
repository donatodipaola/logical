#include <gtest/gtest.h>

#include <logical.hpp>


namespace logical { namespace test {

TEST(LogicalTestSuite, NullMatricConstructor_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> expecteData{0,0,0,0,0,0};

  Matrix A(rows,cols);

  ASSERT_EQ(
    rows,
    A.rows());
  
  ASSERT_EQ(
    cols,
    A.cols());
  
  ASSERT_EQ(
    expecteData,
    A.data());
}

TEST(LogicalTestSuite, DataMatrixConstructor_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  std::vector<bool> data{1,0,1,0};

  Matrix A(rows,cols,data);

  ASSERT_EQ(
    rows,
    A.rows());
  
  ASSERT_EQ(
    cols,
    A.cols());
  
  ASSERT_EQ(
    data,
    A.data());
}

TEST(LogicalTestSuite, DataMatrixConstructor_ThrowsOutOfRange)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  std::vector<bool> data{1,0,1,0,1,0,1,0,1,0,1,0};

  ASSERT_THROW(
    Matrix A(rows,cols,data),
    std::out_of_range);
}

TEST(LogicalTestSuite, CopyConstructor_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  std::vector<bool> data{1,0,1,0};

  Matrix A(rows,cols,data);
  Matrix B(A);

  ASSERT_EQ(
    rows,
    B.rows());
  
  ASSERT_EQ(
    cols,
    B.cols());
  
  ASSERT_EQ(
    data,
    B.data());
}

TEST(LogicalTestSuite, FunctionCallOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});

  ASSERT_EQ(
    0,
    A(0,0));
  
  ASSERT_EQ(
    1,
    A(0,1));
}

TEST(LogicalTestSuite, GetNumberOfRows_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> data = {0,1,1,0,1,0};
  Matrix A(rows,cols,data);

  ASSERT_EQ(
    rows,
    A.rows());
}

TEST(LogicalTestSuite, GetNumberOfColumns_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> data = {0,1,1,0,1,0};
  Matrix A(rows,cols,data);

  ASSERT_EQ(
    cols,
    A.cols());
}

TEST(LogicalTestSuite, GetData_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> data = {0,1,1,0,1,0};
  Matrix A(rows,cols,data);

  ASSERT_EQ(
    data,
    A.data());
}

TEST(LogicalTestSuite, AdditionOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});
  Matrix B(rows,cols,{1,0,0,1});

  Matrix C(rows,cols,{1,1,1,1});

  ASSERT_EQ(
    C,
    A += B);
}

TEST(LogicalTestSuite, AdditionOperator_ThrowsOutOfRange)
{
  Matrix A(2,2);
  Matrix B(3,3);

  ASSERT_THROW(
    A += B,
    std::range_error);
}

TEST(LogicalTestSuite, MultiplyOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});
  Matrix B(rows,cols,{1,0,0,1});

  Matrix C(rows,cols);

  ASSERT_EQ(
    C,
    A *= B);
}

TEST(LogicalTestSuite, MultiplyOperator_ThrowsOutOfRange)
{
  Matrix A(2,2);
  Matrix B(3,3);

  ASSERT_THROW(
    A *= B,
    std::range_error);
}

TEST(LogicalTestSuite, ElementAddOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});
  bool value = 1;

  Matrix C(rows,cols,{1,1,1,1});

  ASSERT_EQ(
    C,
    A += value);
}

TEST(LogicalTestSuite, ElementMultplyOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});
  bool value = 1;

  Matrix C(rows,cols,{0,1,1,0});

  ASSERT_EQ(
    C,
    A *= value);
}

TEST(LogicalTestSuite, ComplementOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});

  Matrix C(rows,cols,{1,0,0,1});

  ASSERT_EQ(
    C,
    ~A);
}

TEST(LogicalTestSuite, DeMorgansLaws_Success)
{
  Matrix P(3,3,{0,0,1,0,1,1,1,0,0});
  Matrix Q(3,3,{1,0,1,0,0,0,1,1,1});
  
  
  ASSERT_TRUE((~(P+=Q)) == ((~P) *= (~Q)));
  ASSERT_TRUE((~(P*=Q)) == ((~P) += (~Q)));
}


TEST(LogicalTestSuite, Multiply_Success)
{
  uint8_t rowsA = 2;
  uint8_t colsA = 3;
  Matrix A(rowsA,colsA,{1,0,0,1,0,0});
  
  uint8_t rowsB = 3;
  uint8_t colsB = 2;
  Matrix B(rowsB,colsB,{1,0,1,1,0,1});

  Matrix C(rowsA,colsB,{1,0,1,0});
  
  ASSERT_EQ(
    C,
    A * B);
}

TEST(LogicalTestSuite, TransposeVector_Success)
{
  uint8_t rowsA = 1;
  uint8_t colsA = 4;
  Matrix A(rowsA,colsA,{1,0,1,0});
  
  uint8_t rowsB = 4;
  uint8_t colsB = 1;
  Matrix B(rowsB,colsB,{1,0,1,0});
  
  ASSERT_EQ(
    B,
    A.transpose());
}

TEST(LogicalTestSuite, TransposeSquare_Success)
{
  uint8_t rowsA = 2;
  uint8_t colsA = 2;
  Matrix A(rowsA,colsA,{1,0,1,0});
  
  uint8_t rowsB = 2;
  uint8_t colsB = 2;
  Matrix B(rowsB,colsB,{1,1,0,0});
  
  ASSERT_EQ(
    B,
    A.transpose());
}

TEST(LogicalTestSuite, Transpose_Success)
{
  uint8_t rowsA = 2;
  uint8_t colsA = 3;
  Matrix A(rowsA,colsA,{1,0,0,1,0,1});
  
  uint8_t rowsB = 3;
  uint8_t colsB = 2;
  Matrix B(rowsB,colsB,{1,1,0,0,0,1});
  
  ASSERT_EQ(
    B,
    A.transpose());
}

TEST(LogicalTestSuite, TransposeProperty_Success)
{
  Matrix A(3,3,{0,0,1,0,1,1,1,0,0});
  Matrix B(3,3,{1,0,1,0,0,0,1,1,1});
 
  ASSERT_TRUE((A * B).transpose() == B.transpose() * A.transpose());
}

TEST(LogicalTestSuite, StreamInsertionOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});

  std::string expectedOutput("\n0 1\n1 0\n");

  std::ostringstream outputstream;
  outputstream << A;

  ASSERT_EQ(
    expectedOutput,
    outputstream.str());
}

TEST(LogicalTestSuite, EqualOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  Matrix A(rows,cols,{0,1,1,0});
  Matrix B(A);

  ASSERT_TRUE(A==B);
}

}}