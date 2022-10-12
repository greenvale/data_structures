#pragma once

#include <assert.h>

namespace datastructlib
{

/* Singly linked node */    
template <class T> 
class SingleNode
{
private:
    T m_val;
    SingleNode* m_nextPtr;
public:
    SingleNode();
    SingleNode(const T& val);
    SingleNode(SingleNode* nextPtr);
    SingleNode(const T& val, SingleNode* nextPtr);      
    
    T getVal() const;
    void setVal(const T& val);
    
    SingleNode* getNextPtr() const;
    void setNextPtr(SingleNode* nextPtr);
};

/* Singly linked list */
template <class T>
class SinglyLinkedList
{
private:
    SingleNode<T>* m_headPtr;
    SingleNode<T>* m_tailPtr;
    unsigned int m_length;
public:
    SinglyLinkedList();
    
    SingleNode<T>* headPtr() const;
    SingleNode<T>* tailPtr() const;
    SingleNode<T>* getPtr(const unsigned int& index) const;
    unsigned int length() const;
    
    void insertHead(SingleNode<T>* nodePtr);
    void insertTail(SingleNode<T>* nodePtr);
    void insert(const unsigned int& index, SingleNode<T>* nodePtr);
    
    void removeHead();
    void removeTail();
    void remove(const unsigned int& index);
    void clear();
};

/* default ctor */
template <class T>
SingleNode<T>::SingleNode()
{
}

/* ctor with val */
template <class T>
SingleNode<T>::SingleNode(const T& val)
{
    this->m_val = val;
}

/* ctor with next ptr */
template <class T>
SingleNode<T>::SingleNode(SingleNode* nextPtr)
{
    this->m_nextPtr = nextPtr;
}

/* ctor with val and next ptr */
template <class T>
SingleNode<T>::SingleNode(const T& val, SingleNode* nextPtr)
{
    this->m_val = val;
    this->m_nextPtr = nextPtr;
}

/* returns val */
template <class T>
T SingleNode<T>::getVal() const 
{ 
    return this->m_val; 
}

/* sets val */
template <class T>
void SingleNode<T>::setVal(const T& val) 
{ 
    this->m_val = val; 
} 

/* returns linked node ptr */
template <class T>
SingleNode<T>* SingleNode<T>::getNextPtr() const 
{ 
    return this->m_nextPtr; 
}

/* sets linked node ptr */
template <class T>
void SingleNode<T>::setNextPtr(SingleNode* nextPtr) 
{ 
    this->m_nextPtr = nextPtr; 
}

/* default ctor */
template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    this->m_headPtr = nullptr;
    this->m_tailPtr = nullptr;
    this->m_length = 0;
}

/* returns head ptr */
template <class T>
SingleNode<T>* SinglyLinkedList<T>::headPtr() const
{
    return m_headPtr;
}

/* returns tail ptr */
template <class T>
SingleNode<T>* SinglyLinkedList<T>::tailPtr() const
{
    return m_tailPtr;
}

/* returns ptr at given index position */
template <class T>
SingleNode<T>* SinglyLinkedList<T>::getPtr(const unsigned int& index) const
{
    assert((index >= 0) && (index < this->m_length)); // do not use with head or tail
    
    SingleNode<T>* travPtr = this->m_headPtr; // initialise traverse pointer
    SingleNode<T>* travNextPtr;
    unsigned int dist = 0;
    while (dist < index)
    {
        travNextPtr = travPtr->getNextPtr();
        assert(travNextPtr != nullptr); // should not encounter null ptr
        
        travPtr = travNextPtr; // traverse to next ptr
        dist++;
    }
    return travPtr;
}

/* returns length */
template <class T>
unsigned int SinglyLinkedList<T>::length() const
{ 
    return this->m_length; 
}

/* insert new head */
template <class T>
void SinglyLinkedList<T>::insertHead(SingleNode<T>* nodePtr)
{
    if (this->m_length == 0)
    {
        // for empty list also set to tail ptr
        this->m_tailPtr = nodePtr;
        nodePtr->setNextPtr(nullptr);
    }
    else
    {
        nodePtr->setNextPtr(this->m_headPtr);
    }
    this->m_headPtr = nodePtr;
    this->m_length++;
}

/* insert new tail */
template <class T>
void SinglyLinkedList<T>::insertTail(SingleNode<T>* nodePtr)
{
    if (this->m_length == 0)
    {
        // for empty list also set to head ptr
        this->m_headPtr = nodePtr;
    }
    else
    {
        this->m_tailPtr->setNextPtr(nodePtr);
    }
    this->m_tailPtr = nodePtr;
    nodePtr->setNextPtr(nullptr);
    this->m_length++;
}

/* insert node at given index */
template <class T>
void SinglyLinkedList<T>::insert(const unsigned int& index, SingleNode<T>* nodePtr)
{
    assert(this->m_length > 2);
    assert((index > 0) && (index < this->m_length));
    
    SingleNode<T>* prevPtr = this->getPtr(index - 1);
    
    nodePtr->setNextPtr(prevPtr->getNextPtr());
    prevPtr->setNextPtr(nodePtr);
    this->m_length++;
}

/* removes head */
template <class T>
void SinglyLinkedList<T>::removeHead()
{
    assert(this->m_length > 0);
    
    if (this->m_length == 1)
    {
        this->m_headPtr = nullptr; // no more elements in list
        this->m_tailPtr = nullptr;
    }
    else if (this->m_length == 2)
    {
        this->m_headPtr = this->m_tailPtr; // set head to be current tail - forget old head
    }
    else
    {
        this->m_headPtr = m_headPtr->getNextPtr(); // set head to be next ptr from old head
    }
    this->m_length--;
}

/* removes tail */
template <class T>
void SinglyLinkedList<T>::removeTail()
{
    assert(this->m_length > 0);
    
    if (this->m_length == 1)
    {
        this->m_headPtr = nullptr; // no more elements in list
        this->m_tailPtr = nullptr;
    }
    else if (this->m_length == 2)
    {
        this->m_tailPtr = this->m_headPtr; // set tail to be current head - forget old tail
        this->m_headPtr->setNextPtr(nullptr);
    }
    else
    {
        SingleNode<T>* prevNode = getPtr(this->m_length - 2); // get node before tail - make this tail
        prevNode->setNextPtr(nullptr);
        this->m_tailPtr = prevNode;
    }
    this->m_length--;
}

/* removes an element at given index */
template <class T>
void SinglyLinkedList<T>::remove(const unsigned int& index)
{
    assert(this->m_length > 2);
    assert((index > 0) && (index < this->m_length));
    
    SingleNode<T>* prevNode = this->getPtr(index - 1);
    SingleNode<T>* thisNode = prevNode->getNextPtr();
    prevNode->setNextPtr(thisNode->getNextPtr());
    this->m_length--;
}

/* clears entire linked list */
template <class T>
void SinglyLinkedList<T>::clear()
{
    unsigned int length = m_length;
    for (int i = 0; i < length; ++i) 
    {
        this->removeHead();
    }
}
}
