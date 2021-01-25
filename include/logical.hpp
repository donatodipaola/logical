// MIT License  - Copyright (c) 2021 Donato Di Paola

#pragma once

#include <vector>
#include <ostream>


namespace logical {

class Matrix
{
public:
  Matrix(const uint8_t rows, const uint8_t cols);
  Matrix(const uint8_t rows, const uint8_t cols, const std::vector<bool>& data); 
  Matrix(const Matrix& rhs);

  bool operator()(uint8_t row, uint8_t column) const;

  uint8_t rows() const;
  uint8_t cols() const;
  std::vector<bool> data() const;

  Matrix operator+=(const Matrix& rhs) const;
  Matrix operator*=(const Matrix& rhs) const;
  Matrix operator+=(const bool& rhs) const;
  Matrix operator*=(const bool& rhs) const;
  Matrix operator~() const;

  Matrix operator*(const Matrix& rhs) const;
  Matrix transpose() const;

private:
  const uint8_t _rows;
  const uint8_t _cols;
  const std::vector<bool> _data;
};

Matrix multiply(const Matrix& lhs, const Matrix& rhs);

std::ostream& operator<<(std::ostream &os, const Matrix& rhs);
bool operator==(const Matrix& lhs, const Matrix& rhs);

}
