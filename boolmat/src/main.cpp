#include <iostream>

#include <boolmat.hpp>


int main() {
    boolmat::Matrix A(3,3);
    std::cout << A << std::endl;
    
    boolmat::Matrix C(3,3,{1,0,1,0,0,0,1,1,1});
    std::cout << C << std::endl;
    
    boolmat::Matrix D(C);
    std::cout << D << std::endl;
    
    if (D==C)
    {
        std::cout << "Equal" << std::endl;
    }
    
    return 0;
}
