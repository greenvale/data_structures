#pragma once

#include <iostream>
#include <assert.h>

namespace DataStructLib
{
    template <class T>
    class DynamicArray
    {
    private:
        T* m_staticArray;
        unsigned int m_length;
        unsigned int m_staticArraySize;
        unsigned int m_defaultStaticArraySize = 16;
        
    public:
        // creates empty dynamic array
        DynamicArray();

        // creates empty dynamic array with a custom default array size
        DynamicArray(
            const unsigned int& defaultStaticArraySize
        );

        // returns value at existing index
        T get(
            const unsigned int& index
        );

        // changes value at existing index
        void set(
            const unsigned int& index, 
            const T& value
        );

        // adds value to the end of the array (creates new index and increases size if necessary)
        void add(
            const T& value
        );

        // removes value at existing index
        void remove(
            const unsigned int& index
        );

        // clears all elements from the dynamic array
        void clear();

        // gets indexes of elements in dynamic array with a given value
        DynamicArray<unsigned int> getIndexes(
            const T& value
        );
        
        // get length
        unsigned int getLength();
       
        // print values to output
        void print();
        
        // reallocate static array (useful for changing static array size)
        void reallocateStaticArray();

    };

    // =============================================================================

    template <class T>
    DynamicArray<T>::DynamicArray()
    {
        m_staticArraySize = m_defaultStaticArraySize; // no array size provided, therefore set to default size
        m_staticArray = new T[m_staticArraySize]; // initialise static array

        m_length = 0; // set length to zero
    }

    template <class T>
    DynamicArray<T>::DynamicArray(
        const unsigned int& defaultStaticArraySize
    )
    {
        m_defaultStaticArraySize = defaultStaticArraySize; // set array size

        m_staticArraySize = m_defaultStaticArraySize; // no array size provided, therefore set to default size
        m_staticArray = new T[m_staticArraySize]; // initialise static array

        m_length = 0; // set length to zero as dynamic array is empty
    }

    template <class T>
    T DynamicArray<T>::get(
        const unsigned int& index
    )
    {
        assert(index < m_length); // check index does not exceed dynamic array length
        return m_staticArray[index];
    }

    template <class T>
    void DynamicArray<T>::set(
        const unsigned int& index, 
        const T& value
    )
    {
        assert(index < m_length); // check index does not exceed dynamic array length
        m_staticArray[index] = value;
    }

    template <class T>
    void DynamicArray<T>::add(
        const T& value
    )
    {
        if (m_length + 1 > m_staticArraySize) // check if static array needs to be made bigger
        {
            m_staticArraySize *= 2;
            reallocateStaticArray(); // double the static array size
        }

        m_length++; // increase length of dynamic array and add value
        m_staticArray[m_length - 1] = value;
    }

    template <class T>
    void DynamicArray<T>::remove(
        const unsigned int& index
    )
    {
        assert(index < m_length); // check index does not exceed dynamic array length

        for (int i = index + 1; i < m_length; ++i) 
        {
            m_staticArray[i - 1] = m_staticArray[i]; // shift RH values to left by one, thereby removing target value
        }
        
        m_staticArray[m_length - 1] = 0; // set end value to be nil and reduce length
        m_length--;

        // check if array can be downsized -> length <= arraySize / 2
        // only if arraySize is greater than defaultArraySize
        if ((m_length <= m_staticArraySize / 2) && (m_staticArraySize > m_defaultStaticArraySize))
        {
            m_staticArraySize /= 2;
            reallocateStaticArray();
        }
    }
    
    template <class T>
    void DynamicArray<T>::reallocateStaticArray()
    {
        T* temp_staticArray = new T[m_staticArraySize]; // create temp static array
        
        for (int i = 0; i < m_length; ++i)
        {
            temp_staticArray[i] = m_staticArray[i]; // copy values
        }
        
        delete[] m_staticArray; // clear contents of static array then set it to temp static array
        m_staticArray = temp_staticArray;
    }

    template <class T>
    void DynamicArray<T>::clear()
    {
        delete[] m_staticArray;
        m_staticArraySize = m_defaultStaticArraySize; // reset dynamic array length to default length
        m_staticArray = new T[m_staticArraySize];
    }

    template <class T>
    DynamicArray<unsigned int> DynamicArray<T>::getIndexes(
        const T& value
    )
    {
        DynamicArray<unsigned int> indexes; // create dynamic array to store indexes
        
        for (unsigned int i = 0; i < m_length; ++i)
        {
            if (m_staticArray[i] == value)
            {
                indexes.add(i); // if element has same value, add its index to indexes array
            }
        }
        
        return indexes;
    }
    
    template <class T>
    unsigned int DynamicArray<T>::getLength()
    {
        return m_length;
    }
    
    template <class T>
    void DynamicArray<T>::print()
    {
        for (int i = 0; i < m_length; ++i)
        {
            std::cout << "(" << i << "): " << m_staticArray[i] << std::endl;
        }
    }
}
