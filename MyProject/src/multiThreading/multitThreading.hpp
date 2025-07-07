#include <thread>
#include <iostream>
#include <mutex>


struct Account
{
    double deposit;
    std::mutex mtx;
};

namespace multiThreading
{
    
}