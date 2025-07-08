#include <thread>
#include <iostream>
#include <mutex>


struct Account
{
    double balance;
    std::mutex mtx;
};

namespace multiThreading
{
    void transfer(Account& from, Account& to, double amount)
    {
        std::scoped_lock(from.mtx, to.mtx);

        if (from.balance >= amount)
        {
            from.balance -= amount;
            to.balance += amount;
            std::cout << "transfered " << amount << "\n";
        }
        else std::cout << "the balance is insufficient!" << std::endl;
    }
}