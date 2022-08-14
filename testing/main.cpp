#include <iostream>

#include <DynamicArray.hpp>

int main()
{
    DataStructLib::DynamicArray<float> myArray(2);

    myArray.add(1.0f);
    myArray.add(2.0f);
    myArray.add(3.0f);

    std::cout << myArray.get(0) << std::endl;

}
