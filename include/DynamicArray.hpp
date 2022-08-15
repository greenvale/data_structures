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
        DynamicArray();
        DynamicArray(const unsigned int& defaultStaticArraySize);
        DynamicArray(const DynamicArray&);

        T get(const unsigned int& index) const;
        T* getPtr(const unsigned int& index) const;
        void set(const unsigned int& index, const T& value);
        void add(const T& value);
        void remove(const unsigned int& index);
        void clear();

        DynamicArray<unsigned int> getValueIndexes(const T& value);
        bool contains(const T& value);
        
        unsigned int getLength() const;
       
        void print();
        
    private:
        // reallocate static array (useful for changing static array size)
        void reallocateStaticArray();
    };

    // =============================================================================
    // CTORS / DTORS
    
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
    DynamicArray<T>::DynamicArray(
        const DynamicArray<T>& dynamicArray
    )
    {
        m_staticArraySize = m_defaultStaticArraySize;
        m_staticArray = new T[m_staticArraySize];
        m_length = dynamicArray.getLength();
        
        for (unsigned int i = 0; i < dynamicArray.getLength(); ++i)
        {
            m_staticArray[i] = dynamicArray.get(i);
        }
        
        std::cout << "Copy constructor called" << std::endl;
    }
    
    // =============================================================================
    // GET FUNCTIONS

    template <class T>
    T DynamicArray<T>::get(
        const unsigned int& index
    ) const
    {
        assert(index < m_length); // check index does not exceed dynamic array length
        return m_staticArray[index];
    }
    
    template <class T>
    T* DynamicArray<T>::getPtr(const unsigned int& index) const
    {
        assert(index < m_length);
        return &(m_staticArray[index]);
    }
    
    template <class T>
    unsigned int DynamicArray<T>::getLength() const
    {
        return m_length;
    }
    
    // =============================================================================
    // SET FUNCTIONS

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
    void DynamicArray<T>::clear()
    {
        delete[] m_staticArray;
        m_staticArraySize = m_defaultStaticArraySize; // reset dynamic array length to default length
        m_staticArray = new T[m_staticArraySize];
    }
    
    // =============================================================================
    // SEARCHING

    template <class T>
    DynamicArray<unsigned int> DynamicArray<T>::getValueIndexes(
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
    bool DynamicArray<T>::contains(
        const T& value
    )
    {
        DynamicArray<unsigned int> indexes = getValueIndexes(value); // get array of indexes
        
        return indexes.getLength() > 0;
    }
    
    // =============================================================================
    // PRINTING
    
    template <class T>
    void DynamicArray<T>::print()
    {
        for (int i = 0; i < m_length; ++i)
        {
            std::cout << "(" << i << "): " << m_staticArray[i] << std::endl;
        }
    }
    
    // =============================================================================
    // INTERNAL FUNCTIONS
    
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

}
