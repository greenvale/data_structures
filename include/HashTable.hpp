/* Hash table - W Denny
*/
#pragma once

#include <DynamicArray.hpp>
#include <assert.h>

namespace datastructlib
{

/********************************************************************************************************************/
/* HASH FUNCTOR CLASS */

/* Base Functor for hashing function 
    - takes key with type T (should be immutable) as input
    - returns index to array
*/
template <class T>
class HashFunctor
{
public:
    HashFunctor()
    {
    }
    virtual unsigned int operator()(const T& key, const unsigned int& arrLength)
    {
        return 0;
    }
};

/********************************************************************************************************************/
/* PROBE FUNCTOR CLASS */

/* Base Functor for probing sequence
    - takes input x - usually a natural number??
    - the probing function must be able to map onto every index in the array
*/

class ProbeFunctor
{
public:
    ProbeFunctor()
    {

    }
    virtual void reset()
    {

    }
    virtual unsigned int increment(const unsigned int& arrLength)
    {
        return 0;
    }
};

/* Linear probing function */
class LinearProbeFunctor : public ProbeFunctor
{
private:
    unsigned int m_x;
    unsigned int m_a;
    unsigned int m_b;
public:
    LinearProbeFunctor() = delete;
    LinearProbeFunctor(const unsigned int& a, const unsigned int& b)
    {
        assert(a % 2 != 0); // a must not be even - this is because array length in hash table will always be even
        this->m_a = a;
        this->m_b = b;
    }
    void reset()
    {
        this->m_x = 0;
    }
    unsigned int increment(const unsigned int& arrLength)
    {
        assert(arrLength % m_a != 0); // ensure that a and array size are relatively prime
        this->m_x += 1;
        return m_a*this->m_x + m_b;
    }
};

/********************************************************************************************************************/
/* KEY-VALUE PAIR CLASS */

/* 
    - stores key value pair with key as immutable type T and value as type U
    - the key should be unique between objects
*/
template <class T, class U>
class KeyValPair
{
public:
    T m_key;
    U m_val;
};

/********************************************************************************************************************/
/* HASH TABLE SEARCH RESULT */

/* data structure for search results in the hash table */
template <class T, class U>
class HashTable_SearchResult
{
public:
    unsigned int m_hashedKey;
    unsigned int m_sepChainInd; // index in the seperate chain if this is used in the hash table
    KeyValPair<T, U>* m_kvpPtr; // ptr to the key value pair object
};

/********************************************************************************************************************/
/* HASH TABLE BASE CLASS */

template <class T, class U>
class HashTable 
{
protected:
    unsigned int m_arrLength;
    unsigned int m_numEntries;
    HashFunctor<T>* m_hashFunctionPtr;
public:
    double loadFactor()
    {
        return ((double) this->m_numEntries) / ((double) this->m_arrLength);
    }
};

/********************************************************************************************************************/
/* HASH TABLE WITH SEPERATE CHAINING CLASS */

template <class T, class U>
class HashTable_SeperateChaining : public HashTable<T, U>
{
private:
    DynamicArray<KeyValPair<T, U>>* m_data;
public:
    HashTable_SeperateChaining() = delete;
    HashTable_SeperateChaining(const unsigned int& length, HashFunctor<T>* hashFunctionPtr);
    ~HashTable_SeperateChaining();
    HashTable_SearchResult<T, U> find(const T& key);
    void insert(const T& key, const U& val);
    bool remove(const T& key);
};

/* ctor */
template <class T, class U>
HashTable_SeperateChaining<T, U>::HashTable_SeperateChaining(const unsigned int& length, HashFunctor<T>* hashFunctionPtr)
{
    this->m_arrLength = length;
    this->m_data = new DynamicArray<KeyValPair<T, U>>[length];
    this->m_hashFunctionPtr = hashFunctionPtr;
    this->m_numEntries = 0;
}

/* dtor */
template <class T, class U>
HashTable_SeperateChaining<T, U>::~HashTable_SeperateChaining()
{
    delete[] this->m_data;
}

/* returns the pointer to a key value pair given key */
template <class T, class U>
HashTable_SearchResult<T, U> HashTable_SeperateChaining<T, U>::find(const T& key)
{  
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    for (unsigned int i = 0; i < this->m_data[hashedKey].length(); ++i)
    {
        if (this->m_data[hashedKey].get(i).m_key == key)
        {
            // found
            HashTable_SearchResult<T, U> result;
            result.m_hashedKey = hashedKey;
            result.m_sepChainInd = i;
            result.m_kvpPtr = this->m_data[hashedKey].getPtr(i); // no copying of key-value, just a ptr to the object in the hash table
            return result;
        }
    }
    // not found
    HashTable_SearchResult<T, U> result;
    result.m_kvpPtr = nullptr;
    return result;
}

/* inserts new entry into hash table */
template <class T, class U>
void HashTable_SeperateChaining<T, U>::insert(const T& key, const U& val)
{
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    std::cout << "Insertion : Key " << key << " maps onto index " << hashedKey << "\t";
    std::cout << "Dynamic array @ index " << hashedKey << " has " << this->m_data[hashedKey].length() << " existing entry/entries" << std::endl;
    KeyValPair<T, U> kvp; // copies the key and value into new key-value pair object
    kvp.m_key = key;
    kvp.m_val = val;
    this->m_data[hashedKey].append(kvp); // copies the key-value pair object into the array
    this->m_numEntries++;
}

/* remove entry from hash table by key */
template <class T, class U>
bool HashTable_SeperateChaining<T, U>::remove(const T& key)
{
    HashTable_SearchResult<T, U> result = this->find(key);
    if (result.m_kvpPtr == nullptr)
    {
        return false; // object not found inside hash table
    }
    this->m_data[result.m_hashedKey].remove(result.m_sepChainInd);
    std::cout << "Removal : Key " << key << " and value pair removed from dynamic array @ index " << result.m_hashedKey << std::endl;
    this->m_numEntries--;
}

/********************************************************************************************************************/
/* HASH TABLE WITH OPEN ADDRESSING */

template <class T, class U>
class HashTable_OpenAddressing : public HashTable<T, U>
{
private:
    ProbeFunctor* m_probeFunctionPtr;
    KeyValPair<T, U>** m_data; // array of pointers to key-val pairs
    double m_maxLoadFactor;
public:
    HashTable_OpenAddressing() = delete;
    HashTable_OpenAddressing(const unsigned int& length, HashFunctor<T>* hashFunctionPtr, ProbeFunctor* probeFunctionPtr, const double& maxLoadFactor);
    ~HashTable_OpenAddressing();
    HashTable_SearchResult<T, U> find(const T& key);
    void insert(const T& key, const U& val);
    bool remove(const T& key);
};

/* ctor */
template <class T, class U>
HashTable_OpenAddressing<T, U>::HashTable_OpenAddressing(const unsigned int& length, HashFunctor<T>* hashFunctionPtr, ProbeFunctor* probeFunctionPtr, const double& maxLoadFactor)
{
    assert(length % 2 == 0); // array length must be even, to ensure probing function gcd = 1
    this->m_arrLength = length;
    this->m_data = new KeyValPair<T, U>*[length]; // allocate key value pairs on the heap - this is so they can be deleted when removed
    this->m_hashFunctionPtr = hashFunctionPtr;
    this->m_probeFunctionPtr = probeFunctionPtr;
    this->m_numEntries = 0;
    this->m_maxLoadFactor = maxLoadFactor;
}

/* dtor */
template <class T, class U>
HashTable_OpenAddressing<T, U>::~HashTable_OpenAddressing()
{
    delete[] this->m_data;
}

/* returns the pointer to a key value pair given key */
template <class T, class U>
HashTable_SearchResult<T, U> HashTable_OpenAddressing<T, U>::find(const T& key)
{  
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    if (this->m_data[hashedKey]->m_key == key)
    {
        // found
        HashTable_SearchResult<T, U> result;
        result.m_hashedKey = hashedKey;
        result.m_kvpPtr = this->m_data[hashedKey];
        return result;
    }
    // not found
    HashTable_SearchResult<T, U> result;
    result.m_kvpPtr = nullptr;
    return result;
}

/* inserts new entry into hash table */
template <class T, class U>
void HashTable_OpenAddressing<T, U>::insert(const T& key, const U& val)
{
    // calculate projected load factor to check if array size must increase
    double projLoadFactor = (double) (this->m_numEntries + 1) / (double) (this->m_arrLength);
    std::cout << "Projected load factor: " << projLoadFactor << std::endl;
    if (projLoadFactor > this->m_maxLoadFactor)
    {
        this->m_arrLength *= 2;
        std::cout << "Array size must increase to: " << this->m_arrLength << std::endl;
    }

    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    std::cout << "Insertion : Key " << key << " maps onto index " << hashedKey << std::endl;
    KeyValPair<T, U>* kvpPtr = new KeyValPair<T, U>; // copies the key and value
    kvpPtr->m_key = key;
    kvpPtr->m_val = val;
    this->m_probeFunctionPtr->reset(); // reset probe function ptr to base value
    unsigned int ind = hashedKey;
    while (this->m_data[ind] != nullptr)
    {
        std::cout << "\t Hash collision @ index " << ind << std::endl;
        ind = (hashedKey + this->m_probeFunctionPtr->increment(this->m_arrLength)) % this->m_arrLength;
    }
    std::cout << "\t Final index: " << ind << std::endl;
    this->m_data[ind] = kvpPtr;
    this->m_numEntries++;
}

/* remove entry from hash table by key */
template <class T, class U>
bool HashTable_OpenAddressing<T, U>::remove(const T& key)
{
    HashTable_SearchResult<T, U> result = this->find(key);
    if (result.m_kvpPtr == nullptr)
    {
        return false; // object not found inside hash table
    }
    delete result.m_kvpPtr;
    std::cout << "Removal : Key " << key << " and value pair removed from dynamic array @ index " << result.m_hashedKey << std::endl;
    this->m_numEntries--;
}

}; // namespace datastructlib