#include <iostream>
#include "tensor.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;
    try{
        Tensor<int, 3, 3, 3> MyTensor(0);
        int element =  MyTensor(3,0,0);

    }
    catch(std::out_of_range& exception)
    {
        std::cout << "caught an exception!!"<< std::endl;
        std::cout << "Error: " << exception.what() << std::endl;
    }
    return 0;
}