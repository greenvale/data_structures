#include <iostream>

#include <DynamicArray.hpp>
#include <SinglyLinkedList.hpp>

int main()
{
    datastructlib::DynArray<datastructlib::SingNode<float>> nodes;
    
    for (int i = 0; i < 5; ++i)
    {
        datastructlib::SingNode<float> node;
        node.setValue((float) i + 1.0);
        
        nodes.add(node);
    }

    datastructlib::SingLinkList<float> list;
    
    for (int i = 0; i < 5; i+=2)
    {
        list.insertHead(nodes.getPtr(i));
    }
    list.insert(1, nodes.getPtr(3));
    list.insert(3, nodes.getPtr(1));
    
    list.removeHead();
    
    datastructlib::SingNode<float> newNode(4.5);
    
    list.insertTail(&newNode);
    
    for (int i = 0; i < 5; ++i)
    {
        std::cout << list.getValue(i) << std::endl;
    }
    
    std::cout << "Head value: " << list.getHeadValue() << std::endl;
    std::cout << "Tail value: " << list.getTailValue() << std::endl;
}
