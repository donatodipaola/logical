#include <gtest/gtest.h>

#include "boolmat.hpp"


namespace boolmat { namespace test {

TEST(BoolMatTestSuite, Success)
{
  uint8_t numberOfRows = 2;
  uint8_t numberOfColumns = 3;
  boolmat::Matrix A(numberOfRows,numberOfColumns);

  ASSERT_EQ(
    numberOfRows,
    A.rows());
  
  ASSERT_EQ(
    numberOfColumns,
    A.cols());
}


}}