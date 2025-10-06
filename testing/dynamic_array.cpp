#include <iostream>
#include <DynamicArray.hpp>

using namespace datastructlib;

int main() {
    DynamicArray<int> arr;

    // append some values into the dynamic array
    arr.append(5);
    arr.append(10);
    arr.append(15);

    std::cout << "Initial array:" << std::endl;
    arr.print();

    // insert a value at index 1
    arr.insert(1, 7);

    std::cout << "\nAfter inserting 7 at index 1:" << std::endl;
    arr.print();

    // remove an element
    arr.remove(2);

    std::cout << "\nAfter removing element at index 2:" << std::endl;
    arr.print();

    std::cout << "\nContains 10? " << (arr.contains(10) ? "Yes" : "No") << std::endl;

    arr.append(7);
    auto indices = arr.valIndArr(7);
    std::cout << "\nIndexes of value 7:" << std::endl;
    indices.print();

}