#include <iostream>
#include <boolmat.hpp>

int main() {
  std::cout << "DeMorgan Law" << std::endl;
  
  boolmat::Matrix P(3,3,{0,0,1,0,1,1,1,0,0});
  boolmat::Matrix Q(3,3,{1,0,1,0,0,0,1,1,1});
  
  bool rule1 = ((!(P+Q)) == (!P) * (!Q));
  bool rule2 = ((!(P*Q)) == (!P) + (!Q));
    
  std::cout << "P =" << P << std::endl;
  std::cout << "Q =" << Q << std::endl;
  std::cout << "rule1 = " << rule1 << std::endl;
  std::cout << "rule2 = " << rule2 << std::endl << std::endl;
  
  
  std::cout << "Transpose matrix property: (AB)^T = B^T A^T" << std::endl;
  boolmat::Matrix A(3,3,{0,0,1,0,1,1,1,0,0});
  boolmat::Matrix B(3,3,{1,0,1,0,0,0,1,1,1});
  
  bool eval =
    (boolmat::multiply(A,B).transpose() == boolmat::multiply(B.transpose(),A.transpose()));
  
  std::cout << "A =" << A << std::endl;
  std::cout << "B =" << B << std::endl;
  std::cout << "eval = " << eval << std::endl;
  
  return 0;
}