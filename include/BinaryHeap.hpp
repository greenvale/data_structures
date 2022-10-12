/* Binary heap class
    - binary tree that supports the heap invariant
    - uses canonical method to represent binary tree - an array
    - uses functor for comparison to satisfy heap invariance
    - requires DynamicArray class
*/
#pragma once

#include <DynamicArray.hpp>
#include <math.h>

namespace datastructlib
{

/* Base class for functor for maintaining heap condition: used to compare parent & child nodes to control sink/swim operations */
template <class T>
class CompareFunctor
{
public:
    CompareFunctor()
    {

    }
    virtual bool operator()(const T& parent, const T& child) const
    {
        return false;
    }
};

/* Derived class for Min heap condition: parent node <= child node for satisfying heap invariance */
template <class T>
class MinCompareFunctor : public CompareFunctor<T>
{
public:
    bool operator()(const T& parent, const T& child) const
    {
        if (parent <= child)
            return true;
        else
            return false;
    }
};

/* Derived class for Max heap condition: parent node >= child node for satisfying heap invariance */
template <class T>
class MaxCompareFunctor : public CompareFunctor<T>
{
public:
    bool operator()(const T& parent, const T& child) const
    {
        if (parent >= child)
            return true;
        else
            return false;
    }
};

/********************************************************************************************************************/
/* BINARY HEAP CLASS */

template <class T> 
class BinaryHeap
{
private:
    DynamicArray<T> m_arr;
    CompareFunctor<T> m_compare; // functor for comparison between parent and node
public:
    BinaryHeap();
    BinaryHeap(const CompareFunctor<T>& compare);
    bool checkHeapInvar(); // returns true if heap invariant is satisfied
    void swim(const unsigned int& index);
    void sink(const unsigned int& index);
    void insert(const T& val);
    T poll();
    void removeByVal(const T& val);
    void print() const;
};

/* default ctor */
template <class T>
BinaryHeap<T>::BinaryHeap()
{

}

/* ctor with functor for comparison */
template <class T>
BinaryHeap<T>::BinaryHeap(const CompareFunctor<T>& compare)
{
    m_compare = compare;
}

/* returns true if heap invariant is satisfied */ 
template <class T>
bool BinaryHeap<T>::checkHeapInvar() 
{
    for (unsigned int i = 0; i < this->m_arr.length(); ++i)
    {
        if (2*i + 1 < this->m_arr.length())
        {
            if (m_compare(this->m_arr.get(i), this->m_arr.get(2*i + 1)) == false)
                return false;
            if (m_compare(this->m_arr.get(i), this->m_arr.get(2*i + 1)) == false)
                return false;
        }
    }
    return true;
}

/* recursively swap given node with parent nodes that fail the invariant condition functor */
template <class T>
void BinaryHeap<T>::swim(const unsigned int& index) 
{
    //assert(this->m_comparePtr != nullptr);
    unsigned int childIndex = index;
    unsigned int parentIndex;
    bool stop = false;
    while (stop == false)
    {
        parentIndex = (unsigned int) floor(((double) childIndex - 1.0) / 2.0);
        
        if ((childIndex != 0) && (m_compare(this->m_arr.get(parentIndex), this->m_arr.get(childIndex)) == false))
        {
            // if parent val > child val and not at top node, then bubble up child
            T tmp = this->m_arr.get(parentIndex);
            this->m_arr.set(parentIndex, this->m_arr.get(childIndex));
            this->m_arr.set(childIndex, tmp);
            childIndex = parentIndex;
        }
        else
        {
            stop = true;
        }
    }
}

/* recursively swap given node with child nodes that fail the invariant condition functor */
template <class T>
void BinaryHeap<T>::sink(const unsigned int& index) 
{
    //assert(this->m_comparePtr != nullptr);
    unsigned int parentIndex = index;
    unsigned int childIndex_lhs;
    unsigned int childIndex_rhs;
    bool stop = false;
    while (stop == false)
    {
        childIndex_lhs = 2 * parentIndex + 1;
        childIndex_rhs = childIndex_lhs + 1;

        // if lhs child index is valid and its value does not satisfy the heap invariant, swap the two values
        if ((childIndex_lhs < this->m_arr.length()) && (m_compare(this->m_arr.get(parentIndex), this->m_arr.get(childIndex_lhs)) == false))
        {
            T tmp = this->m_arr.get(childIndex_lhs);
            this->m_arr.set(childIndex_lhs, this->m_arr.get(parentIndex));
            this->m_arr.set(parentIndex, tmp);
            parentIndex = childIndex_lhs;
        }
        // if rhs child index is valid and its value does not satisfy the heap invariant, swap the two values
        else if ((childIndex_rhs < this->m_arr.length()) && (m_compare(this->m_arr.get(parentIndex), this->m_arr.get(childIndex_rhs)) == false))
        {
            T tmp = this->m_arr.get(childIndex_rhs);
            this->m_arr.set(childIndex_rhs, this->m_arr.get(parentIndex));
            this->m_arr.set(parentIndex, tmp);
            parentIndex = childIndex_rhs;
        }
        else
        {
            stop = true;
        }
    }
}

/* inserts new element 
    - automatically places at the next available space
    - bubbles up in while loop until heap invariant is satisfied
*/
template <class T>
void BinaryHeap<T>::insert(const T& val)
{
    this->m_arr.append(val);
    unsigned int childIndex = this->m_arr.length() - 1;
    this->swim(childIndex);
}

template <class T>
T BinaryHeap<T>::poll() 
{
    assert(this->m_arr.length() > 0);
    T first = this->m_arr.get(0);
    T last = this->m_arr.get(this->m_arr.length() - 1);
    this->m_arr.remove(this->m_arr.length() - 1); // remove last element from dynamic array, O(1)
    if (this->m_arr.length() > 0) // check that the top element that was removed was not the only element
    {
        this->m_arr.set(0, last);
        this->sink(0); // O(log(n))
    }
    return first;
}

/* removes element
    - you swap the removed element with 
*/
template <class T>
void BinaryHeap<T>::removeByVal(const T& val) 
{
    // search for index of val to remove O(n)
    unsigned int ind;
    bool found = false;
    for (unsigned int i = 0; i < this->m_arr.length(); ++i)
    {
        if (this->m_arr.get(i) == val)
        {
            ind = i;
            found = true;
        }
    }

    // if val has been found, remove it by swapping with last term
    if (found == true)
    {
        T last = this->m_arr.get(this->m_arr.length() - 1);
        this->m_arr.remove(this->m_arr.length() - 1);
        if (this->m_arr.length() > 0) // check that the val element that was removed was not the only element
        {
            this->m_arr.set(ind, last);
            if (this->m_compare(val, last) == true) // 'val' is prioritised above 'last' - therefore only consider sinking
            {
                this->sink(ind);
            }
            else // 'val' is not prioritised above 'last' - therefore only consider swimming
            {
                this->swim(ind);
            }
        }
    }
}

/* prints out binary heap in cascading format */
template <class T>
void BinaryHeap<T>::print() const
{
    bool stop = false;
    unsigned int ind = 0;
    int rowLim = 1;
    int turnInd = rowLim;

    while (stop == false)
    {
        if (ind >= turnInd)
        {
            std::cout << std::endl;
            rowLim *= 2;
            turnInd = ind + rowLim;
        }
        std::cout << this->m_arr.get(ind) << "\t";
        ind++;
        if (ind == this->m_arr.length())
        {
            stop = true;
        }
    }
    std::cout << std::endl;
}

}