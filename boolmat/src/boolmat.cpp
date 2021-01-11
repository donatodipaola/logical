#include <boolmat.hpp>


namespace boolmat {

Matrix::Matrix (uint8_t numberOfRows, uint8_t numberOfColumns) : 
_numberOfRows (numberOfRows), 
_numberOfColumns (numberOfColumns)
{
  _data.resize(_numberOfRows*_numberOfColumns);
}

Matrix::Matrix (uint8_t numberOfRows, uint8_t numberOfColumns, const std::vector<bool>& data) : 
_numberOfRows (numberOfRows), 
_numberOfColumns (numberOfColumns),
_data(data)
{
  if(_numberOfRows*_numberOfColumns != _data.size())
  {
    throw std::out_of_range("Matrix indices and the data vector are not compatible");
  }
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<bool>>& initializationList) 
{
  _numberOfRows = initializationList.size();
  _numberOfColumns = initializationList.begin()->size();
  for (auto row : initializationList)
  {
    std::copy(row.begin(), row.end(), std::back_inserter(_data));
  }
}

Matrix::Matrix(const Matrix& matrix) 
{
  _numberOfRows = matrix._numberOfRows;
  _numberOfColumns = matrix._numberOfColumns;
  _data = matrix._data;
};

uint8_t Matrix::rows() const
{
  return _numberOfRows;
}
    
uint8_t Matrix::cols() const
{
  return _numberOfColumns;
}

std::vector<bool> Matrix::data() const
{
  return _data;
}
    
bool Matrix::operator()(uint8_t row, uint8_t column) const
{
  if (row >= _numberOfRows || column>= _numberOfColumns)
  {
    throw std::out_of_range("matrix indices out of range");
  }
  return _data[_numberOfColumns*row + column];
}

std::ostream& operator<< (std::ostream &os, const Matrix& matrix) 
{
    for (uint8_t i = 0; i < matrix.rows(); ++i)
    {
        for (uint8_t j = 0; j < matrix.cols(); ++j)
            os <<  matrix(i,j) << " ";
        os << std::endl;
    }
    return os;
}

bool operator== (const Matrix& lhs, const Matrix& rhs) 
{
    return  (lhs.rows() == rhs.rows()) and
            (lhs.cols() == rhs.cols()) and
            (lhs.data() == rhs.data());
}

}