#include <iostream>

#include <DynamicArray.hpp>
#include <LinkedList.hpp>

int main()
{
    float num1 = 1.0;
    float num2 = 2.0;
    float num3 = 3.0;
    
    DataStructLib::DoubleNode<float> node1(num1);
    DataStructLib::DoubleNode<float> node2(num2);
    DataStructLib::DoubleNode<float> node3(num3);
    
    node1.setNextPtr(&node2);
    
    node2.setPrevPtr(&node1);
    node2.setNextPtr(&node3);
    
    node3.setPrevPtr(&node2);
    
}
