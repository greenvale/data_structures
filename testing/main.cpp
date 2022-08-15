#include <iostream>

#include <DynamicArray.hpp>
#include <LinkedList.hpp>

int main()
{
    float num1 = 1.0;
    float num2 = 2.0;
    float num3 = 3.0;
    
    DataStructLib::SingleNode<float> node1(num1);
    DataStructLib::SingleNode<float> node2(num2);
    DataStructLib::SingleNode<float> node3(num3);
    
    DataStructLib::SingleLinkList<float> list;
    
    list.insertHead(&node1);
    list.insertHead(&node2);
    
    std::cout << (list.getHeadPtr())->getValue() << std::endl;
}
