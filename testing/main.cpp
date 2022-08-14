#include <iostream>

#include <DynamicArray.hpp>
#include <LinkedList.hpp>

int main()
{
    float num1 = 1.0;
    float num2 = 2.0;
    
    DataStructLib::SingleNode<float> node1(num1);
    DataStructLib::SingleNode<float> node2(num2);
    
    node1.setNextPtr(&node2);
    
    std::cout << node1.getValue() << std::endl;
}
