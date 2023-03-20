#pragma once

#include <iostream>

#include <SinglyLinkedList.hpp>

namespace datastructlib
{
    template <class T>
    class Stack
    {
    private:
        SinglyLinkedList<T> m_stackList;
        unsigned int m_length;
    public:
        Stack();
        
        void push(const T& value);
        T peek();
        T pop();
    };
    
    // =============================================================================
    // =============================================================================
    
    template <class T>
    Stack<T>::Stack()
    {
        m_stackList = SinglyLinkedList<T>();
        m_length = 0;
    }
    
    template <class T>
    void Stack<T>::push(const T& value)
    {   
        SingleNode<T>* newNodePtr = new SingleNode<T>(value); // create singly linked node on heap (not stack)
        m_stackList.insertHead(newNodePtr);
        m_length++;
    }
    
    template <class T>
    T Stack<T>::peek()
    {
        return (m_stackList.headPtr())->getValue();
    }
    
    template <class T>
    T Stack<T>::pop()
    {
        assert(m_length > 0);
        
        T value = peek();
        m_stackList.removeHead();
        m_length--;
        
        return value;
    }
}
