/* Binary search tree - by W Denny
    - every parent has at most two children
    - IMPORTANT: template class must support <, >, == comparison operators
    - each subtree to the left must have a value <, and to the right must have value >
    - same values are not supported
*/
#pragma once

#include <DynamicArray.hpp>
#include <vector>

namespace datastructlib
{

/* class for node in binary tree */
template <class T>
class BinaryTreeNode
{
public:
    T m_val;
    BinaryTreeNode<T>* m_lhs;
    BinaryTreeNode<T>* m_rhs;
};

/* search results from find operation use this struct:
    - contains ptr of node that is being searched for
    - contains ptr to the parent node's ptr to the node - the ptr pointed to usually needs editting
*/
template <class T>
class BinarySearchTreeResult
{
public:
    BinaryTreeNode<T>* m_ptr;
    BinaryTreeNode<T>** m_ptrPtr;
};

/********************************************************************************************************************/
/* BINARY SEARCH TREE CLASS */

template <class T>
class BinarySearchTree
{
private:
    DynamicArray<BinaryTreeNode<T>*> m_nodePtrArr;
public:
    BinarySearchTree();
    BinarySearchTreeResult<T> find(const T& val);
    bool insert(const T& val);
    bool remove(const T& val);
    void display();
};

/* ctor */
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    m_nodePtrArr = {};
}

/* returns the ptr to a node and ptr to the ptr of the parent node's link to the node of a particular value if it is present in the tree */
template <class T>
BinarySearchTreeResult<T> BinarySearchTree<T>::find(const T& val)
{
    if (this->m_nodePtrArr.length() == 0)
    {
        BinarySearchTreeResult<T> result;
        result.m_ptr = nullptr;
        result.m_ptrPtr = nullptr;
        return result;
    }
    BinaryTreeNode<T>* ptr = this->m_nodePtrArr.get(0);
    BinaryTreeNode<T>** ptrPtr = nullptr; // keep track of parent node's ptr to the current node
    while (true)
    {
        if (ptr != nullptr)
        {
            if (val < ptr->m_val)
            {
                ptrPtr = &ptr->m_lhs;
                ptr = ptr->m_lhs;
            }
            else if (val == ptr->m_val)
            {
                BinarySearchTreeResult<T> result;
                result.m_ptr = ptr;
                result.m_ptrPtr = ptrPtr;
                return result;
            }
            else if (val > ptr->m_val)
            {
                ptrPtr = &ptr->m_rhs;
                ptr = ptr->m_rhs;
            }
        }
        else
        {
            BinarySearchTreeResult<T> result;
            result.m_ptr = nullptr;
            result.m_ptrPtr = nullptr;
            return result;
        }
    }
}

/* insertion 
    - if graph empty, insert root node and add ptr to array
    - if graph not empty, start at root and traverse graph until found correct empty position, create new node
    - each node has child ptrs, keep track of the prev child ptr ptr to link with new node when required
*/
template <class T>
bool BinarySearchTree<T>::insert(const T& val)
{
    // handle case for first node seperately
    if (this->m_nodePtrArr.length() == 0)
    {
        BinaryTreeNode<T>* nodePtr = new BinaryTreeNode<T>;
        nodePtr->m_val = val;
        m_nodePtrArr.append(nodePtr);
    }
    else
    {
        BinaryTreeNode<T>* ptr = this->m_nodePtrArr.get(0); // set to root, as it already exists
        BinaryTreeNode<T>** ptrPtr = nullptr; // track the ptr to the child ptr for the previous ptr for case where null pointer is encountered
        bool stop = false;
        while (stop == false)
        {
            if (ptr != nullptr)
            {
                if (val < ptr->m_val)
                {
                    ptrPtr = &ptr->m_lhs; // keep track of the ptr ptr to change it when required
                    ptr = ptr->m_lhs;
                }
                else if (val == ptr->m_val)
                {
                    return false; // equality not supported in this tree
                }
                else if (val > ptr->m_val)
                {
                    ptrPtr = &ptr->m_rhs; // keep track of the ptr ptr to change it when required
                    ptr = ptr->m_rhs;
                }
            }
            else // ptr is nullptr, must create new node
            {
                BinaryTreeNode<T>* nodePtr = new BinaryTreeNode<T>;
                nodePtr->m_val = val;
                *ptrPtr = nodePtr; // link with the prev node's child ptr by dereferencing ptrPtr
                m_nodePtrArr.append(nodePtr);
                stop = true;
            }
        }
    }
    return true;
}

/* removal
    - finds  value from node 
*/
template <class T>
bool BinarySearchTree<T>::remove(const T& val)
{
    BinarySearchTreeResult<T> searchResult = this->find(val);
    if (searchResult.m_ptr == nullptr)
        return false;
    if ((searchResult.m_ptr->m_lhs == nullptr) && (searchResult.m_ptr->m_rhs == nullptr)) // has no sub trees
    {
        this->m_nodePtrArr.removeVal(searchResult.m_ptr);
        *searchResult.m_ptrPtr = nullptr;
    }
    else if ((searchResult.m_ptr->m_lhs != nullptr) && (searchResult.m_ptr->m_rhs == nullptr)) // only has left sub tree
    {
        BinaryTreeNode<T>* childPtr = searchResult.m_ptr->m_lhs; // obtain the new child ptr for the parent ptr's child
        this->m_nodePtrArr.removeVal(searchResult.m_ptr);
        *searchResult.m_ptrPtr = childPtr;
    }
    else if ((searchResult.m_ptr->m_lhs == nullptr) && (searchResult.m_ptr->m_rhs != nullptr)) // only has right sub tree
    {
        BinaryTreeNode<T>* childPtr = searchResult.m_ptr->m_rhs; // obtain the new child ptr for the parent ptr's child
        this->m_nodePtrArr.removeVal(searchResult.m_ptr);
        *searchResult.m_ptrPtr = childPtr;
    }
    else // both children are sub-trees
    // we replace the target node with the largest node in the LH subtree, this is because it still satisfies binary search tree criteria - it is smaller than all values in RH subtree
    // the largest node will either be the LH child of the target node, or the furthest successive RH child of the LH node - these two cases must be handled seperately
    {
        BinaryTreeNode<T>* replacePtr = searchResult.m_ptr->m_lhs;
        BinaryTreeNode<T>** ptrPtr = nullptr;
        // two cases - the LH child has a RH child or it does not
        if (searchResult.m_ptr->m_lhs->m_rhs != nullptr) // LH child has RH child
        {
            // find the largest RH child in the sub-tree by constantly traversing RH children until there are no more RH children
            while (replacePtr->m_rhs != nullptr)
            {
                ptrPtr = &replacePtr->m_rhs; // keep track of ptr to parent node's ptr to removal node
                replacePtr = replacePtr->m_rhs;
            }
            
            // two cases: terminal RH child will have a LH child or it will not
            // if has LH child then link this LH child as RH child for parent ptr to largest val ptr
            // in both cases, replace val in removal node with value in replacePtr node
            if (replacePtr->m_lhs != nullptr)
            {
                *ptrPtr = replacePtr->m_lhs;
            }
            searchResult.m_ptr->m_val = replacePtr->m_val;
            this->m_nodePtrArr.removeVal(replacePtr); // replacePtr node has become obselete, remove from graph
        }
        else // LH child does not have RH child
        {
            searchResult.m_ptr->m_val = searchResult.m_ptr->m_lhs->m_val; // replace value
            BinaryTreeNode<T>* obseletePtr = searchResult.m_ptr->m_lhs; // LH child node has become obselete, must remove from graph
            searchResult.m_ptr->m_lhs = searchResult.m_ptr->m_lhs->m_lhs; // set LH child's LH child to be the replacement LH child
            this->m_nodePtrArr.removeVal(obseletePtr);
        }
    }
    return true;
}

/* displays the graph in the output buffer */
template <class T>
void BinarySearchTree<T>::display() 
{
    for (int i = 0; i < this->m_nodePtrArr.length(); ++i)
    {
        std::cout << "Node " << i << ": value = " << this->m_nodePtrArr.get(i)->m_val << "; " << std::endl;
        BinaryTreeNode<T>* lhs = this->m_nodePtrArr.get(i)->m_lhs;
        BinaryTreeNode<T>* rhs = this->m_nodePtrArr.get(i)->m_rhs;

        std::cout << "\t links to (LHS): ";
        if (lhs != nullptr)
        {
            std::cout << lhs->m_val;
        }
        else 
        {
            std::cout << "NULLPTR";
        }
        std::cout << std::endl;
        std::cout << "\t links to (RHS): ";
        if (rhs != nullptr)
        {
            std::cout << rhs->m_val;
        }
        else 
        {
            std::cout << "NULLPTR";
        }
        std::cout << std::endl;
    }
}

} // namespace datastructlib