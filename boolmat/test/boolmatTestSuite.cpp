#include <gtest/gtest.h>

#include <boolmat.hpp>


namespace boolmat { namespace test {

TEST(BoolMatTestSuite, NullMatricConstructor_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> expecteData{0,0,0,0,0,0};

  boolmat::Matrix A(rows,cols);

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

TEST(BoolMatTestSuite, DataMatrixConstructor_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  std::vector<bool> data{1,0,1,0};

  boolmat::Matrix A(rows,cols,data);

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

TEST(BoolMatTestSuite, DataMatrixConstructor_ThrowsOutOfRange)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  std::vector<bool> data{1,0,1,0,1,0,1,0,1,0,1,0};

  ASSERT_THROW(
    boolmat::Matrix A(rows,cols,data),
    std::out_of_range);
}

TEST(BoolMatTestSuite, CopyConstructor_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  std::vector<bool> data{1,0,1,0};

  boolmat::Matrix A(rows,cols,data);
  boolmat::Matrix B(A);

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

TEST(BoolMatTestSuite, FunctionCallOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});

  ASSERT_EQ(
    0,
    A(0,0));
  
  ASSERT_EQ(
    1,
    A(0,1));
}

TEST(BoolMatTestSuite, GetNumberOfRows_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> data = {0,1,1,0,1,0};
  boolmat::Matrix A(rows,cols,data);

  ASSERT_EQ(
    rows,
    A.rows());
}

TEST(BoolMatTestSuite, GetNumberOfColumns_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> data = {0,1,1,0,1,0};
  boolmat::Matrix A(rows,cols,data);

  ASSERT_EQ(
    cols,
    A.cols());
}

TEST(BoolMatTestSuite, GetData_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 3;
  std::vector<bool> data = {0,1,1,0,1,0};
  boolmat::Matrix A(rows,cols,data);

  ASSERT_EQ(
    data,
    A.data());
}

TEST(BoolMatTestSuite, AdditionOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});
  boolmat::Matrix B(rows,cols,{1,0,0,1});

  boolmat::Matrix C(rows,cols,{1,1,1,1});

  ASSERT_EQ(
    C,
    A + B);
}

TEST(BoolMatTestSuite, AdditionOperator_ThrowsOutOfRange)
{
  boolmat::Matrix A(2,2);
  boolmat::Matrix B(3,3);

  ASSERT_THROW(
    A + B,
    std::range_error);
}

TEST(BoolMatTestSuite, MultiplyOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});
  boolmat::Matrix B(rows,cols,{1,0,0,1});

  boolmat::Matrix C(rows,cols);

  ASSERT_EQ(
    C,
    A * B);
}

TEST(BoolMatTestSuite, MultiplyOperator_ThrowsOutOfRange)
{
  boolmat::Matrix A(2,2);
  boolmat::Matrix B(3,3);

  ASSERT_THROW(
    A * B,
    std::range_error);
}

TEST(BoolMatTestSuite, ElementAddOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});
  bool value = 1;

  boolmat::Matrix C(rows,cols,{1,1,1,1});

  ASSERT_EQ(
    C,
    A + value);
}

TEST(BoolMatTestSuite, ElementMultplyOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});
  bool value = 1;

  boolmat::Matrix C(rows,cols,{0,1,1,0});

  ASSERT_EQ(
    C,
    A * value);
}

TEST(BoolMatTestSuite, ComplementOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});

  boolmat::Matrix C(rows,cols,{1,0,0,1});

  ASSERT_EQ(
    C,
    !A);
}

TEST(BoolMatTestSuite, TransposeVector_Success)
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

TEST(BoolMatTestSuite, TransposeSquare_Success)
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

TEST(BoolMatTestSuite, Transpose_Success)
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

TEST(BoolMatTestSuite, Multiply_Success)
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
    multiply(A,B));
}


TEST(BoolMatTestSuite, StreamInsertionOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});

  std::string expectedOutput("\n0 1\n1 0\n");

  std::ostringstream outputstream;
  outputstream << A;

  ASSERT_EQ(
    expectedOutput,
    outputstream.str());
}

TEST(BoolMatTestSuite, EqualOperator_Success)
{
  uint8_t rows = 2;
  uint8_t cols = 2;
  boolmat::Matrix A(rows,cols,{0,1,1,0});
  boolmat::Matrix B(A);

  ASSERT_TRUE(A==B);
}


}}