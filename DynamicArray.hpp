/* Dynamic array by W Denny */

#pragma once

#include <iostream>
#include <assert.h>

namespace datastructlib
{
    
template <class T>
class DynamicArray
{
private:
    T* m_staticArr;
    unsigned int m_length;
    unsigned int m_staticArrLength; // this grows/shrinks as elements added/removed
    unsigned int m_defaultStaticArrLength = 16;
    
public:
    DynamicArray();
    DynamicArray(const unsigned int& defaultStaticArrLength);
    DynamicArray(const DynamicArray&);
    T get(const unsigned int& ind) const;
    T* getPtr(const unsigned int& ind) const; // returns ptr of element in array
    void set(const unsigned int& ind, const T& val);
    void insert(const unsigned int& ind, const T& val);
    void append(const T& val);
    void remove(const unsigned int& ind);
    void removeVal(const T& val);
    void clear();
    DynamicArray<unsigned int> valIndArr(const T& val) const; // returns dynamic array of indexes to elements in this array with a given value
    bool contains(const T& val) const;
    unsigned int length() const;
    void print();

private:
    void reallocStaticArr(); // reallocate stat array - to be used once the static array length has been changed and new space to be allocated/old space to be deallocated
};

/* default ctor */
template <class T>
DynamicArray<T>::DynamicArray()
{
    this->m_staticArrLength = this->m_defaultStaticArrLength; // no array size provided, therefore set to default size
    this->m_staticArr = new T[this->m_staticArrLength]; // initialise stat array
    this->m_length = 0; // set length to zero
}

/* ctor with custom default static array size */
template <class T>
DynamicArray<T>::DynamicArray(const unsigned int& defaultStaticArrLength)
{
    this->m_defaultStaticArrLength = defaultStaticArrLength; // set array size
    this->m_staticArrLength = this->m_defaultStaticArrLength; // no array size provided, therefore set to default size
    this->m_staticArr = new T[this->m_staticArrLength]; // initialise stat arr
    this->m_length = 0; // set length to zero as dynamic arr is empty
}

/* copy ctor */
template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArr)
{
    this->m_staticArrLength = this->m_defaultStaticArrLength;
    this->m_staticArr = new T[this->m_staticArrLength];
    this->m_length = dynamicArr.length();
    for (unsigned int i = 0; i < dynamicArr.length(); ++i)
    {
        this->m_staticArr[i] = dynamicArr.get(i);
    }
    //std::cout << "Copy constructor called" << std::endl;
}

/* returns value given index */
template <class T>
T DynamicArray<T>::get(const unsigned int& ind) const
{
    assert(ind < this->m_length); // check index does not exceed dynamic array length
    return this->m_staticArr[ind];
}

/* returns ptr of value given index */
template <class T>
T* DynamicArray<T>::getPtr(const unsigned int& ind) const
{
    assert(ind < this->m_length);
    return &(this->m_staticArr[ind]);
}

/* returns length of array */
template <class T>
unsigned int DynamicArray<T>::length() const
{
    return this->m_length;
}

/* sets value given index */
template <class T>
void DynamicArray<T>::set(const unsigned int& ind, const T& value)
{
    assert(ind < this->m_length); // check index does not exceed dynamic array length
    this->m_staticArr[ind] = value;
}

/* appends array with new element of given value to the end */
template <class T>
void DynamicArray<T>::append(const T& value)
{
    if (this->m_length + 1 > this->m_staticArrLength) // check if stat array needs to be made bigger
    {
        this->m_staticArrLength *= 2;
        this->reallocStaticArr(); // double the stat array size
    }
    this->m_length++; // increase length of dynamic array and add value
    this->m_staticArr[this->m_length - 1] = value;
}

/* inserts an element given index into array */
template <class T>
void DynamicArray<T>::insert(const unsigned int& ind, const T& val)
{
    assert(ind <= this->m_length);
    if (this->m_length + 1 > this->m_staticArrLength) // check if stat array needs to be made bigger
    {
        this->m_staticArrLength *= 2;
        this->reallocStaticArr(); // double the stat array size
    }
    for (unsigned int i = ind; i < this->m_length; ++i)
    {
        this->m_staticArr[i + 1] = this->m_staticArr[i]; // shift values after and including position ind to the right
    }
    this->m_staticArr[ind] = val; // set value
    this->m_length++;
}

/* removes an element given index from array */
template <class T>
void DynamicArray<T>::remove(const unsigned int& ind)
{
    assert(ind < this->m_length); // check index does not exceed dynamic array length
    for (unsigned int i = ind + 1; i < this->m_length; ++i) 
    {
        this->m_staticArr[i - 1] = this->m_staticArr[i]; // shift RH values to left by one, thereby removing target value
    }
    this->m_staticArr[this->m_length - 1] = 0; // set end value to be nil and reduce length
    this->m_length--;

    // check if array can be downsized -> length <= arrSize / 2
    // only if arraySize is greater than defaultArrSize
    if ((this->m_length <= this->m_staticArrLength / 2) && (this->m_staticArrLength > this->m_defaultStaticArrLength))
    {
        this->m_staticArrLength /= 2;
        this->reallocStaticArr();
    }
}

/* remove any elements in array that have a given value */
template <class T>
void DynamicArray<T>::removeVal(const T& val)
{
    unsigned int found = 0;
    unsigned int initLength = this->m_length;
    for (unsigned int i = 0; i < initLength; ++i)
    {
        if (found > 0)
            this->m_staticArr[i - found] = this->m_staticArr[i];
        if (this->m_staticArr[i] == val)
        {
            found++;
            this->m_length--;
        }
    }

    // check if array can be downsized -> length <= arrSize / 2
    // only if arraySize is greater than defaultArrSize
    if ((this->m_length <= this->m_staticArrLength / 2) && (this->m_staticArrLength > this->m_defaultStaticArrLength))
    {
        this->m_staticArrLength /= 2;
        this->reallocStaticArr();
    }
}

/* clears the whole array */
template <class T>
void DynamicArray<T>::clear()
{
    delete[] this->m_staticArr;
    this->m_staticArrLength = this->m_defaultStaticArrLength; // reset dynamic array length to default length
    this->m_staticArr = new T[this->m_staticArrLength];
    this->m_length = 0;
}

/* returns dynamic array containing indexes of all elements with given value */
template <class T>
DynamicArray<unsigned int> DynamicArray<T>::valIndArr(const T& value) const
{
    DynamicArray<unsigned int> indArr; // create dynamic array to store indexes
    for (unsigned int i = 0; i < this->m_length; ++i)
    {
        if (this->m_staticArr[i] == value)
        {
            indArr.append(i); // if element has same value, add its index to indexes array
        }
    }
    return indArr;
}

/* O(n) scan through array returning true if value present */
template <class T>
bool DynamicArray<T>::contains(const T& value) const
{
    for (unsigned int i = 0; i < this->m_length; ++i)
    {
        if (this->m_staticArr[i] == value)
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
    for (unsigned int i = 0; i < this->m_length; ++i)
    {
        std::cout << "(" << i << "): " << this->m_staticArr[i] << std::endl;
    }
}

/* used to reallocate to array when the array size has grown or shrunk */
template <class T>
void DynamicArray<T>::reallocStaticArr()
{
    T* tmp = new T[this->m_staticArrLength]; // create temp stat array
    for (unsigned int i = 0; i < this->m_length; ++i)
    {
        tmp[i] = this->m_staticArr[i]; // copy values
    }
    delete[] this->m_staticArr; // clear contents of stat array then set it to temp stat array
    this->m_staticArr = tmp;
}

} // namespace datastructlib
