// MIT License  - Copyright (c) 2021 Donato Di Paola

#pragma once

#include <vector>
#include <algorithm>
#include <ostream>


namespace logical {

class Matrix
{
public:
  Matrix (uint8_t rows, uint8_t cols) : 
    _rows(rows), 
    _cols(cols),
    _data(std::vector<bool>(_rows*_cols,0))
  {}

  Matrix (uint8_t rows, uint8_t cols, const std::vector<bool>& data) : 
    _rows(rows), 
    _cols(cols),
    _data(data)
  {
    if(_rows*_cols != _data.size()){
      throw std::out_of_range("Matrix indices and the data vector are not compatible");
    }
  }

  Matrix(const Matrix& rhs) :
    _rows(rhs._rows),
    _cols(rhs._cols),
    _data(rhs._data)
  {}

  bool operator()(uint8_t row, uint8_t column) const {
    if (row >= _rows || column>= _cols) {
      throw std::out_of_range("Matrix indices out of range");
    }
    return _data[_cols*row + column];
  }

  uint8_t rows() const {
    return _rows;
  }

  uint8_t cols() const {
    return _cols;
  }

  std::vector<bool> data() const {
    return _data;
  }

  Matrix operator+=(const Matrix& rhs) const {     
    if (rhs._rows != _rows || rhs._cols != _cols){
      throw std::range_error("Matrices have not the same size");
    }

    std::vector<bool> data(_rows*_cols);
    std::transform(_data.cbegin(), _data.cend(), rhs._data.cbegin(), data.begin(), std::plus<bool>());
    
    return Matrix(_rows,_cols,data); 
  }

  Matrix operator*=(const Matrix& rhs) const {     
    if (rhs._rows != _rows || rhs._cols != _cols) {
      throw std::range_error("Matrices have not the same size");
    }

    std::vector<bool> data(_rows*_cols);
    std::transform(_data.cbegin(), _data.cend(), rhs._data.cbegin(), data.begin(), std::multiplies<bool>());
    
    return Matrix(_rows,_cols,data); 
  }

  Matrix operator+=(const bool& rhs) const {     
    std::vector<bool> data(_rows*_cols);
    std::transform(_data.cbegin(),_data.cend(),data.begin(),[&rhs](const auto& dataValue){return dataValue+rhs;});

    return Matrix(_rows,_cols,data); 
  }

  Matrix operator*=(const bool& rhs) const {     
    std::vector<bool> data(_rows*_cols);
    std::transform(_data.cbegin(),_data.cend(),data.begin(),[&rhs](const auto& dataValue){return dataValue*rhs;});

    return Matrix(_rows,_cols,data); 
  }
  
  Matrix operator~() const {
    std::vector<bool> data(_rows*_cols);
    std::transform(_data.cbegin(),_data.cend(),data.begin(),[](const auto& dataValue){return !dataValue;});

    return Matrix(_rows,_cols,data); 
  }

  Matrix operator*(const Matrix& rhs) const {
  if (_cols != rhs.rows()) {
    throw std::range_error("Matrices have incompatible size");
  }
  std::vector<bool> data(_rows*rhs.cols(),0);

  for (uint8_t i = 0; i < _rows; ++i) {
    for (uint8_t j = 0; j < rhs.cols(); ++j) {
      for (uint8_t k = 0; k < rhs.rows(); ++k) {
        if(_data[k + _cols*i]  && rhs(k,j)) {
          data[j + _rows*i] = 1;
          break;
        }
      }
    }
  }
  return Matrix(_rows,rhs.cols(),data); 
}

  Matrix transpose() const {
    std::vector<bool> data(_rows*_cols);
    for (uint8_t i = 0; i < _cols; ++i) {
      for (uint8_t j = 0; j < _rows; ++j) {
        data[j + _rows*i] = _data[i + _cols*j];
      }
    }
    return Matrix(_cols,_rows,data); 
  }

private:
  const uint8_t _rows;
  const uint8_t _cols;
  const std::vector<bool> _data;
};

std::ostream& operator<<(std::ostream &ostream, const Matrix& rhs) { 
  ostream << std::endl;
  for (uint8_t i = 0; i < rhs.rows(); ++i) {
    for (uint8_t j = 0; j < rhs.cols(); ++j) {
      ostream <<  rhs(i,j);
      if(j != (rhs.cols() - 1)) {
        ostream << " ";
      }
    }
    ostream << std::endl;
  }
  return ostream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
  return  (lhs.rows() == rhs.rows()) and
          (lhs.cols() == rhs.cols()) and
          (lhs.data() == rhs.data());
}

}
