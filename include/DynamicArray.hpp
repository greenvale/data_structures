#pragma once

#include <iostream>
#include <assert.h>

namespace DataStructLib
{
    template <typename T>
    class DynamicArray
    {
    private:
        T* array;
        unsigned int length;
        unsigned int arraySize;
        unsigned int defaultArraySize = 16;
    public:
        // creates empty dynamic array
        DynamicArray();

        // creates 
        DynamicArray(
            const unsigned int& init_arraySize
        );

        // get length
        unsigned int getLength();

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

        // gets indexes of elements in dynamic array with given value
        void getIndex(
            const T& value
        );

    };

    // =============================================================================

    template <typename T>
    DynamicArray<T>::DynamicArray()
    {
        // no array size provided, therefore set to default size
        arraySize = defaultArraySize;

        // initialise static array
        array = new T[arraySize];

        // set length to zero
        length = 0;
    }

    template <typename T>
    DynamicArray<T>::DynamicArray(
        const unsigned int& init_defaultArraySize
    )
    {
        // set array size
        defaultArraySize = init_defaultArraySize;

        // no array size provided, therefore set to default size
        arraySize = defaultArraySize;

        // initialise static array
        array = new T[arraySize];

        // set length to zero
        length = 0;
    }

    template <typename T>
    unsigned int DynamicArray<T>::getLength()
    {
        return length;
    }

    template <typename T>
    T DynamicArray<T>::get(
        const unsigned int& index
    )
    {
        // check index does not exceed dynamic array length
        assert(index < length);

        return array[index];
    }

    template <typename T>
    void DynamicArray<T>::set(
        const unsigned int& index, 
        const T& value
    )
    {
        // check index does not exceed dynamic array length
        assert(index < length);

        array[index] = value;
    }

    template <typename T>
    void DynamicArray<T>::add(
        const T& value
    )
    {
        // check if new length will exceed array size
        if (length + 1 > arraySize)
        {
            // double array size
            arraySize *= 2;

            //std::cout << "Array size changed to be " << arraySize << std::endl;

            // create new array
            T* newArray = new T[arraySize];

            // copy across existing values
            for (int i = 0; i < length; ++i)
            {
                newArray[i] = array[i];
            }

            // change array to newArray with larger size
            array = newArray;
        }

        // increase length of dynamic array
        length++;

        array[length - 1] = value;
    }

    template <typename T>
    void DynamicArray<T>::remove(
        const unsigned int& index
    )
    {
        // check index does not exceed dynamic array length
        assert(index < length);

        // shift RH values to the left by one, thereby removing our value
        for (int i = index + 1; i < length; ++i)
        {
            array[i - 1] = array[i];
        }
        
        // set end value to be nil
        array[length - 1] = NULL;

        // reduce length
        length--;

        // check if array can be downsized -> length <= arraySize / 2
        // only if arraySize is greater than defaultArraySize
        if ((length <= arraySize / 2) && (arraySize > defaultArraySize))
        {
            // half array size
            arraySize /= 2;

            //std::cout << "Array size changed to be " << arraySize << std::endl;

            // create new array
            T* newArray = new T[arraySize];

            // copy across existing values
            for (int i = 0; i < length; ++i)
            {
                newArray[i] = array[i];
            }

            // change array to newArray with larger size
            array = newArray;
        }
    }

    template <typename T>
    void DynamicArray<T>::clear()
    {
        // delete array and its contents
        delete[] array;

        // reset array size to default size
        arraySize = defaultArraySize;

        // create new empty array
        array = new T[arraySize];
    }

    template <typename T>
    void DynamicArray<T>::getIndex(
        const T& value
    )
    {
        
    }
}
