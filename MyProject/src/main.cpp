#include <iostream>
#include "tensor.hpp"

template<int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0>{
    static const int value = 1;
};

int main()
{
    std::cout << "Hello world!" << std::endl;
    try{
        Tensor<int, 3, 3, 3> MyTensor(0);
        int element =  MyTensor(3,0,0);
        const auto data = MyTensor.getData();
    }
    catch(const std::out_of_range& exception)
    {
        std::cout << "caught an exception!!"<< std::endl;
        std::cout << "Error: " << exception.what() << std::endl;
    }
    return 0;
}