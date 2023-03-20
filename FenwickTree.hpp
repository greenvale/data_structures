/* Fenwick Tree - W Denny
    - supports range queries on arrays
    - supports point updates
    - construction linear time
    - point updates/range sum queries/range series are logarithmic time
    - cannot add elements or entirely remove elements
    - cells store sums over a number of elements given by the least significant bit of their index (starting at 1)
    - e.g. cell 8 stores the sum over cells 1 - 8 in the original array
*/
#pragma once
#include <vector>

namespace datastructlib
{

template <class T>
class FenwickTree
{
private:
    unsigned int m_length;
    T* m_data;
public:
    /* ctor 
        - copies data from input vector into array
        - performs summation for tree nodes in linear time
    */
    FenwickTree(const std::vector<T>& input)
    {
        this->m_length = input.size();
        this->m_data = new T[this->m_length];
        for (unsigned int i = 1; i < this->m_length + 1; ++i)
            this->m_data[i - 1] = input[i - 1]; // copy input values into array
        
        for (unsigned int i = 1; i < this->m_length + 1; ++i)
        {
            unsigned int ind = i + this->lsb(i);
            if (ind <= this->m_length)
                this->m_data[ind - 1] += this->m_data[i - 1]; // calculate totals accumulated by each parent by propagating values
        }
    }

    /* returns least significant bits 
        - used for determining the number of children dependent on a cell of given index n
    */
    unsigned int lsb(const unsigned int& n)
    {
        unsigned int result = 1;
        while ((n & result) != result)
        {
            result = result << 1;
        }
        return result;
    }

    /* range query 
        - obtains the sums [1, a) and [1, b] and takes the difference to get [a, b]
        - note the first sum for a is not inclusive but exclusive as we want the value at a
        - sum obtained by cascading down indexes and escalating up the tree adding sums over exponentially more elements
    */
    T rangeQuery(const unsigned int& a, const unsigned int& b)
    {
        // get sum [1, a]
        T result_a = T(0);
        unsigned int ind_a = a - 1;
        while (ind_a > 0)
        {
            result_a += this->m_data[ind_a - 1];
            ind_a -= this->lsb(ind_a);
        }

        // get sum [1, b]
        T result_b = T(0);
        unsigned int ind_b = b;
        while (ind_b > 0)
        {
            result_b += this->m_data[ind_b - 1];
            ind_b -= this->lsb(ind_b);
        }

        return result_b - result_a;
    }

    /* point update
        - propagates up the difference in the cell
        - 
    */
    void pointUpdate(const unsigned int& n, const T& dif)
    {
        unsigned int ind = n;
        while (ind <= this->m_length)
        {
            this->m_data[ind - 1] += dif;
            ind += this->lsb(ind);
        }
    }
};

}