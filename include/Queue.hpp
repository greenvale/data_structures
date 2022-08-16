#pragma once

#include <iostream>

#include <SinglyLinkedList.hpp>

namespace datastructlib
{
    template <class T>
    class Queue
    {
    private:
        SinglyLinkedList<T> m_queueList;
        unsigned int m_length;
    public:
        Queue();
        
        void enqueue();
        
    };
}
