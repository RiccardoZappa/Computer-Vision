#include <iostream>
#include <thread>
#include "tensor.hpp"
#include "memoryManagement/memoryManagement.hpp"
#include "multiThreading/multiThreading.hpp"

template<int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0>{
    static const int value = 1;
};

constexpr long long factorial(int n)
{
    if (n <= 1)
        return 1;
    return n * factorial(n-1);
}

int main()
{
    std::cout << "Hello world!" << std::endl;
    try{

        Account a1{40.0};
        Account a2{30.0};


        std::thread t1(multiThreading::transfer, std::ref(a1), std::ref(a2), 40.0);
        std::thread t2(multiThreading::transfer, std::ref(a2), std::ref(a1), 20.0);

        t1.join();
        t2.join();

        std::cout << "the two account balances are " << a1.balance << ", " << a2.balance << "\n";


        memoryManagement::useRawPointer();

        memoryManagement::useUniquePointer();

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