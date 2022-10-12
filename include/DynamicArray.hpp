#pragma once

#include <iostream>
#include <assert.h>

namespace datastructlib
{
    
template <class T>
class DynamicArray
{
private:
    T* m_statArr;
    unsigned int m_length;
    unsigned int m_statArrSize; // this grows/shrinks as elements added/removed
    unsigned int m_defaultStatArrSize = 16;
    
public:
    DynamicArray();
    DynamicArray(const unsigned int& defaultStatArrSize);
    DynamicArray(const DynamicArray&);

    T get(const unsigned int& index) const;
    T* getPtr(const unsigned int& index) const;
    void set(const unsigned int& index, const T& value);
    void append(const T& value);
    void remove(const unsigned int& index);
    void clear();

    DynamicArray<unsigned int> valIndexArr(const T& value);
    bool contains(const T& value);
    
    unsigned int length() const;

    void print();
    
private:
    // reallocate stat array (useful for changing stat arr size)
    void reallocateStatArr();
};

/* default ctor */
template <class T>
DynamicArray<T>::DynamicArray()
{
    this->m_statArrSize = this->m_defaultStatArrSize; // no array size provided, therefore set to default size
    this->m_statArr = new T[this->m_statArrSize]; // initialise stat array
    this->m_length = 0; // set length to zero
}

/* ctor with custom default static array size */
template <class T>
DynamicArray<T>::DynamicArray(const unsigned int& defaultStatArrSize)
{
    this->m_defaultStatArrSize = defaultStatArrSize; // set array size
    this->m_statArrSize = this->m_defaultStatArrSize; // no array size provided, therefore set to default size
    this->m_statArr = new T[this->m_statArrSize]; // initialise stat arr
    this->m_length = 0; // set length to zero as dynamic arr is empty
}

/* copy ctor */
template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArr)
{
    this->m_statArrSize = this->m_defaultStatArrSize;
    this->m_statArr = new T[this->m_statArrSize];
    this->m_length = dynamicArr.length();
    for (unsigned int i = 0; i < dynamicArr.length(); ++i)
    {
        this->m_statArr[i] = dynamicArr.get(i);
    }
    std::cout << "Copy constructor called" << std::endl;
}

/* returns value given index */
template <class T>
T DynamicArray<T>::get(const unsigned int& index) const
{
    assert(index < this->m_length); // check index does not exceed dynamic array length
    return this->m_statArr[index];
}

/* returns ptr of value given index */
template <class T>
T* DynamicArray<T>::getPtr(const unsigned int& index) const
{
    assert(index < this->m_length);
    return &(this->m_statArr[index]);
}

/* returns length of array */
template <class T>
unsigned int DynamicArray<T>::length() const
{
    return this->m_length;
}

/* sets value given index */
template <class T>
void DynamicArray<T>::set(const unsigned int& index, const T& value)
{
    assert(index < this->m_length); // check index does not exceed dynamic array length
    this->m_statArr[index] = value;
}

/* appends array with new element of given value to the end */
template <class T>
void DynamicArray<T>::append(const T& value)
{
    if (this->m_length + 1 > this->m_statArrSize) // check if stat array needs to be made bigger
    {
        this->m_statArrSize *= 2;
        this->reallocateStatArr(); // double the stat array size
    }

    this->m_length++; // increase length of dynamic array and add value
    this->m_statArr[this->m_length - 1] = value;
}

/* removes an element given index from array */
template <class T>
void DynamicArray<T>::remove(const unsigned int& index)
{
    assert(index < this->m_length); // check index does not exceed dynamic array length
    for (int i = index + 1; i < this->m_length; ++i) 
    {
        this->m_statArr[i - 1] = this->m_statArr[i]; // shift RH values to left by one, thereby removing target value
    }
    
    this->m_statStat[this->m_length - 1] = 0; // set end value to be nil and reduce length
    this->m_length--;

    // check if array can be downsized -> length <= arrSize / 2
    // only if arraySize is greater than defaultArrSize
    if ((this->m_length <= this->m_statArrSize / 2) && (this->m_statArrSize > this->m_defaultStatArrSize))
    {
        this->m_statArrSize /= 2;
        this->reallocateStatArr();
    }
}

/* clears the whole array */
template <class T>
void DynamicArray<T>::clear()
{
    delete[] this->m_statArr;
    this->m_statArrSize = this->m_defaultStatArrSize; // reset dynamic array length to default length
    this->m_statArr = new T[this->m_statArrSize];
}

/* returns dynamic array containing indexes of all elements with given value */
template <class T>
DynamicArray<unsigned int> DynamicArray<T>::valIndexArr(const T& value)
{
    DynamicArray<unsigned int> indexes; // create dynamic array to store indexes
    for (unsigned int i = 0; i < this->m_length; ++i)
    {
        if (this->m_statArr[i] == value)
        {
            indexes.append(i); // if element has same value, add its index to indexes array
        }
    }
    return indexes;
}

/* O(n) scan through array returning true if value present */
template <class T>
bool DynamicArray<T>::contains(
    const T& value
)
{
    for (unsigned int i = 0; i < this->m_length; ++i)
    {
        if (this->m_statArr[i] == value)
        {
            return true;
        }
    }
    return false;
}

/* prints dynamic array */
template <class T>
void DynamicArray<T>::print()
{
    for (int i = 0; i < this->m_length; ++i)
    {
        std::cout << "(" << i << "): " << this->m_statArr[i] << std::endl;
    }
}

/* used to reallocate to array when the array size has grown or shrunk */
template <class T>
void DynamicArray<T>::reallocateStatArr()
{
    T* temp_statArr = new T[this->m_statArrSize]; // create temp stat array
    for (int i = 0; i < this->m_length; ++i)
    {
        temp_statArr[i] = this->m_statArr[i]; // copy values
    }
    delete[] this->m_statArr; // clear contents of stat array then set it to temp stat array
    this->m_statArr = temp_statArr;
}

} // namespace datastructlib
