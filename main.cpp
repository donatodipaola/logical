#include <iostream>

#include <BoolMatrix.hpp>

std::ostream& operator<< (std::ostream &os, const BoolMatrix& iMatrix) 
{
    for (uint8_t i = 0; i < iMatrix.rows(); ++i)
    {
        for (uint8_t j = 0; j < iMatrix.cols(); ++j)
            os <<  iMatrix(i,j) << " ";
        os << std::endl;
    }
    return os;
}



int main() {
    BoolMatrix A(3,3);
    std::cout << A << std::endl;
    
    BoolMatrix B({{1,0,0},{1,0,1}});
    std::cout << B << std::endl;
    
    BoolMatrix C(3,3,{1,0,1,0,0,0,1,1,1});
    std::cout << C << std::endl;
    
    return 0;
}
