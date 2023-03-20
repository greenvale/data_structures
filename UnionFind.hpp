/* Union Find - by W Denny
    - number of nodes in graph must be provided upon construction
    - initially each node points to itself (as provided in target array)
    - union operation finds the roots for two nodes using the find operation
    - if the roots are different, the nodes are unioned
    - when roots are found, path compression is used to prevent chains of nodes leading to the root
    - supports path compression
    - a group is characterised by its root
*/
#pragma once
#include <assert.h>

namespace datastructlib
{

template <class T>
class UnionFind
{
private:
    unsigned int m_numElem;
    unsigned int* m_targetArr;
public:
    UnionFind() = delete;
    UnionFind(unsigned int numElem);
    ~UnionFind();
    bool makeUnion(const unsigned int& node0, const unsigned int& node1);
    unsigned int findRoot(const unsigned int& node); // finds root of node
};

/* only ctor allowed */
template <class T>
UnionFind<T>::UnionFind(unsigned int numElem)
{
    this->m_numElem = numElem;
    this->m_targetArr = new unsigned int[numElem];
    for (unsigned int i = 0; i < numElem; ++i)
    {
        this->m_targetArr[i] = i; // make every node point to themselves initially
    }
}

/* dtor */
template <class T>
UnionFind<T>::~UnionFind()
{
    delete[] this->m_targetArr;
}

/* returns the root node that a child ultimately points to */
template <class T>
unsigned int UnionFind<T>::findRoot(const unsigned int& node)
{  
    assert(node < this->m_numElem);

    // locate root of node
    unsigned int root;
    unsigned int child = node;
    bool stop = false;
    while (stop == false)
    {
        root = this->m_targetArr[child]; // find target that child node is pointing to
        if (root == child) // if child is pointing to itself
        {
            stop = true;
        }
        child = root;
    }

    // path compression - repeat find but set all nodes' parent to be root
    stop = false;
    unsigned int parent;
    child = node;
    while (stop == false)
    {
        parent = this->m_targetArr[child];
        this->m_targetArr[child] = root;
        if (parent == root)
        {
            stop = true;
        }
        child = parent;
    }
    return root;
}

/* makes union between two nodes by make one's root node point to another */
template <class T>
bool UnionFind<T>::makeUnion(const unsigned int& node0, const unsigned int& node1)
{
    assert(node0 < this->m_numElem);
    assert(node1 < this->m_numElem);
    unsigned int root0 = this->findRoot(node0);
    unsigned int root1 = this->findRoot(node1);
    if (root0 != root1)
    {
        this->m_targetArr[root1] = root0;
        return true;
    }
    else
    {
        return false;
    }
}

} // namespace datastructlib