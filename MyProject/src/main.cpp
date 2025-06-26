#include <iostream>
#include "tensor.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;
    Tensor<int, 3, 3, 3> MyTensor(0);
    int element =  MyTensor(3,0,0);
    std::cout << "my tensor element" << 3 << "is" << element << std::endl;

    return 0;
}