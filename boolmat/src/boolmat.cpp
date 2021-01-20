#include <boolmat.hpp>

#include <algorithm>
#include <iostream>

namespace boolmat {

Matrix::Matrix (uint8_t rows, uint8_t cols) : 
_rows(rows), 
_cols(cols),
_data(std::vector<bool>(_rows*_cols,0))
{}

Matrix::Matrix (uint8_t rows, uint8_t cols, const std::vector<bool>& data) : 
_rows(rows), 
_cols(cols),
_data(data)
{
  if(_rows*_cols != _data.size())
  {
    throw std::out_of_range("Matrix indices and the data vector are not compatible");
  }
}

Matrix::Matrix(const Matrix& rhs) :
  _rows(rhs._rows),
  _cols(rhs._cols),
  _data(rhs._data)
{}

bool Matrix::operator()(uint8_t row, uint8_t column) const
{
  if (row >= _rows || column>= _cols)
  {
    throw std::out_of_range("Matrix indices out of range");
  }
  return _data[_cols*row + column];
}

uint8_t Matrix::rows() const
{
  return _rows;
}
    
uint8_t Matrix::cols() const
{
  return _cols;
}

std::vector<bool> Matrix::data() const
{
  return _data;
}

Matrix Matrix::operator+(const Matrix& rhs) const
{     
  if (rhs._rows != _rows || rhs._cols != _cols)
  {
    throw std::range_error("Matrices have not the same size");
  }

  std::vector<bool> data(_rows*_cols);
  std::transform(_data.cbegin(), _data.cend(), rhs._data.cbegin(), data.begin(), std::plus<bool>());
  
  return Matrix(_rows,_cols,data); 
}

Matrix Matrix::operator*(const Matrix& rhs) const
{     
  if (rhs._rows != _rows || rhs._cols != _cols)
  {
    throw std::range_error("Matrices have not the same size");
  }

  std::vector<bool> data(_rows*_cols);
  std::transform(_data.cbegin(), _data.cend(), rhs._data.cbegin(), data.begin(), std::multiplies<bool>());
  
  return Matrix(_rows,_cols,data); 
}

Matrix Matrix::operator+(const bool& rhs) const
{     
  std::vector<bool> data(_rows*_cols);
  std::transform(_data.cbegin(),_data.cend(),data.begin(),[&rhs](const auto& dataValue){return dataValue+rhs;});

  return Matrix(_rows,_cols,data); 
}

Matrix Matrix::operator*(const bool& rhs) const
{     
  std::vector<bool> data(_rows*_cols);
  std::transform(_data.cbegin(),_data.cend(),data.begin(),[&rhs](const auto& dataValue){return dataValue*rhs;});

  return Matrix(_rows,_cols,data); 
}

Matrix Matrix::operator!() const
{
  std::vector<bool> data(_rows*_cols);
  std::transform(_data.cbegin(),_data.cend(),data.begin(),[](const auto& dataValue){return !dataValue;});

  return Matrix(_rows,_cols,data); 
}

Matrix Matrix::transpose() const
{
  std::vector<bool> data(_rows*_cols);
  for (uint8_t i = 0; i < _cols; ++i)
  {
    for (uint8_t j = 0; j < _rows; ++j)
    {
      data[j+_rows*i] = _data[_cols*j + i];
    }
  }
  return Matrix(_cols,_rows,data); 
}

Matrix multiply(const Matrix& lhs, const Matrix& rhs)
{
  if (lhs.cols() != rhs.rows())
  {
    throw std::range_error("Matrices have incompatible size");
  }
  std::vector<bool> data(lhs.rows()*rhs.cols());

  for (uint8_t i = 0; i < lhs.rows(); ++i)
  {
    for (uint8_t j = 0; j < rhs.cols(); ++j)
    {
      for (uint8_t k = 0; k < rhs.rows(); ++k)
      {
        data[j+lhs.rows()*i] = data[j+lhs.rows()*i] + lhs(i,k)*rhs(k,j);
      }
    }
  }
  return Matrix(lhs.rows(),rhs.cols(),data); 
}

std::ostream& operator<< (std::ostream &os, const Matrix& rhs)
{ 
  os << std::endl;
  for (uint8_t i = 0; i < rhs.rows(); ++i)
  {
    for (uint8_t j = 0; j < rhs.cols(); ++j)
    {
      os <<  rhs(i,j);
      if(j != (rhs.cols() - 1))
      {
        os << " ";
      }
    }
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