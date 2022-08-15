#include <iostream>

#include <DynamicArray.hpp>
#include <LinkedList.hpp>

int main()
{
    DataStructLib::DynamicArray<DataStructLib::SingleNode<float>> nodes;
    
    for (int i = 0; i < 5; ++i)
    {
        DataStructLib::SingleNode<float> node;
        node.setValue((float) i + 1.0);
        
        nodes.add(node);
    }

    DataStructLib::SingleLinkList<float> list;
    
    for (int i = 0; i < 5; i+=2)
    {
        list.insertHead(nodes.getPtr(i));
    }
    list.insertMid(1, nodes.getPtr(3));
    list.insertMid(3, nodes.getPtr(1));
    
    list.removeHead();
    
    DataStructLib::SingleNode<float> newNode(4.5);
    
    list.insertTail(&newNode);
    
    for (int i = 0; i < 5; ++i)
    {
        std::cout << list.getValue(i) << std::endl;
    }
    
    std::cout << "Head value: " << list.getHeadValue() << std::endl;
    std::cout << "Tail value: " << list.getTailValue() << std::endl;
}
