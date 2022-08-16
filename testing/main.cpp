#include <iostream>

#include <DynamicArray.hpp>
#include <SinglyLinkedList.hpp>

int main()
{
    datastructlib::DynArray<datastructlib::SingleNode<float>> nodes;
    
    for (int i = 0; i < 5; ++i)
    {
        datastructlib::SingleNode<float> node;
        node.setValue((float) i + 1.0);
        
        nodes.add(node);
    }

    datastructlib::SinglyLinkedList<float> list;
    
    for (int i = 0; i < 5; i+=2)
    {
        list.insertHead(nodes.getPtr(i));
    }
    list.insert(1, nodes.getPtr(3));
    list.insert(3, nodes.getPtr(1));
    
    list.removeHead();
    
    datastructlib::SingleNode<float> newNode(4.5);
    
    list.insertTail(&newNode);
    
    for (int i = 0; i < 5; ++i)
    {
        std::cout << (list.getPtr(i))->getValue() << std::endl;
    }
    
    std::cout << "Head value: " << (list.getHeadPtr())->getValue() << std::endl;
    std::cout << "Tail value: " << (list.getTailPtr())->getValue() << std::endl;
    
    list.clear();
    
    std::cout << "Size: " << list.getLength() << std::endl;
}
