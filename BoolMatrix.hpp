#include <vector>

class BoolMatrix
{
public:
  BoolMatrix (uint8_t numberOfRows,uint8_t numberOfColumns);
  BoolMatrix (uint8_t numberOfRows,uint8_t numberOfColumns, const std::vector<bool>& data); 
  explicit BoolMatrix(const std::initializer_list<std::initializer_list<bool>>& initializationList);
    
  uint8_t rows() const;
  uint8_t cols() const;
    
  bool operator()(uint8_t row, uint8_t column) const;
    
private:
  std::vector<bool> _data;
  uint8_t _numberOfRows;
  uint8_t _numberOfColumns;
};
