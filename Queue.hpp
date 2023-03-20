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
        
        void enqueue(const T& value);
        T peek();
        T dequeue();
    };
    
    // =============================================================================
    // =============================================================================
    
    template <class T>
    Queue<T>::Queue()
    {
        m_queueList = SinglyLinkedList<T>();
        m_length = 0;
    }
    
    template <class T>
    void Queue<T>::enqueue(const T& value)
    {   
        SingleNode<T>* newNodePtr = new SingleNode<T>(value); // create singly linked node on heap (not stack)
        m_queueList.insertTail(newNodePtr);
        m_length++;
    }
    
    template <class T>
    T Queue<T>::peek()
    {
        return (m_queueList.getHeadPtr())->getValue();
    }
    
    template <class T>
    T Queue<T>::dequeue()
    {
        assert(m_length > 0);
        
        T value = peek();
        m_queueList.removeHead();
        m_length--;
        
        return value;
    }
}
