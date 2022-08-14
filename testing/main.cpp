#include <iostream>

#include <DynamicArray.hpp>

int main()
{
    DataStructLib::DynamicArray<float> myArray(2);

    myArray.add(1.0f);
    myArray.add(2.0f);
    myArray.add(3.0f);
    myArray.add(2.0f);

    myArray.print();
    
    DataStructLib::DynamicArray<unsigned int> indexOfSame = myArray.getValueIndexes(2.0f);

    indexOfSame.print();
    std::cout << indexOfSame.getLength() << std::endl;
}
