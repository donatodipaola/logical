
#include <vector>
#include <iostream>


namespace boolmat {

class Matrix
{
public:
  Matrix (uint8_t numberOfRows,uint8_t numberOfColumns);
  Matrix (uint8_t numberOfRows,uint8_t numberOfColumns, const std::vector<bool>& data); 
  explicit Matrix(const std::initializer_list<std::initializer_list<bool>>& initializationList);
  Matrix(const Matrix& matrix);
  
  uint8_t rows() const;
  uint8_t cols() const;
  std::vector<bool> data() const;
    
  bool operator()(uint8_t row, uint8_t column) const;
    
private:
  std::vector<bool> _data;
  uint8_t _numberOfRows;
  uint8_t _numberOfColumns;
};

std::ostream& operator<< (std::ostream &os, const Matrix& matrix);
bool operator== (const Matrix& lhs, const Matrix& rhs);

}
