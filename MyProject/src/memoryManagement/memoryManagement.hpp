#include <iostream>
#include <memory>


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

    void useUniquePointer()
    {
        std::cout << "using smart pointer: unique" << "\n";

        auto myUniqueArray = std::make_unique<std::array<int,5>>();

        std::cout << "the second element of my array is " << (*myUniqueArray)[1] << std::endl;

        std::cout << "the unique pointer will release the resources correctly" << std::endl;
    }

}