#include <iostream>


namespace memoryManagement
{
    void useRawPointer()
    {
        std::cout << "using a raw pointer" << "\n";

        int* myArray = new int[10];

        myArray[0] = 40;

        std::cout << "first element of array is " << myArray[0] << "\n";

        delete[] myArray;

        std::cout << "myarray resources has been deleted" << std::endl;
    }

}