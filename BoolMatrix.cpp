#include <BoolMatrix.hpp>


BoolMatrix::BoolMatrix (uint8_t numberOfRows,uint8_t numberOfColumns) : 
_numberOfRows (numberOfRows), 
_numberOfColumns (numberOfColumns)
{
  _data.resize(_numberOfRows*_numberOfColumns);
}
    
BoolMatrix::BoolMatrix(const std::initializer_list<std::initializer_list<bool>>& matrixAsList) 
{
  _numberOfRows = matrixAsList.size();
  _numberOfColumns = matrixAsList.begin()->size();
  for (auto row : matrixAsList)
  {
    std::copy(row.begin(), row.end(), std::back_inserter(_data));
  }
}
    
uint8_t BoolMatrix::rows() const
{
  return _numberOfRows;
}
    
uint8_t BoolMatrix::cols() const
{
  return _numberOfColumns;
}
    
bool BoolMatrix::operator()(uint8_t row, uint8_t column) const
{
  if (row >= _numberOfRows || column>= _numberOfColumns)
  {
    throw std::out_of_range("matrix indices out of range");
  }
  return _data[_numberOfColumns*row + column];
}