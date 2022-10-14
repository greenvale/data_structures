/* Hash table - W Denny
*/
#pragma once

#include <DynamicArray.hpp>

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
    virtual unsigned int operator()(const T& key)
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
    virtual unsigned int operator()(const unsigned int& x)
    {
        return 0;
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
    unsigned int m_sepChainInd; // index in the seperate chain if this is used
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
    unsigned int ind = (*this->m_hashFunctionPtr)(key);
    for (unsigned int i = 0; i < this->m_data[ind].length(); ++i)
    {
        if (this->m_data[ind].get(i).m_key == key)
        {
            // found
            HashTable_SearchResult<T, U> result;
            result.m_hashedKey = ind;
            result.m_sepChainInd = i;
            result.m_kvpPtr = this->m_data[ind].getPtr(i);
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
    unsigned int ind = (*this->m_hashFunctionPtr)(key);
    std::cout << ind << std::endl;
    KeyValPair<T, U> kvp; // copies the key and value
    kvp.m_key = key;
    kvp.m_val = val;
    this->m_data[ind].append(kvp); // copies the key-value pair object
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
public:
    HashTable_OpenAddressing() = delete;
    HashTable_OpenAddressing(const unsigned int& length, HashFunctor<T>* hashFunctionPtr, ProbeFunctor* probeFunctionPtr);
    ~HashTable_OpenAddressing();
    HashTable_SearchResult<T, U>* find(const T& key);
    void insert(const T& key, const U& val);
    bool remove(const T& key);
};

/* ctor */
template <class T, class U>
HashTable_OpenAddressing<T, U>::HashTable_OpenAddressing(const unsigned int& length, HashFunctor<T>* hashFunctionPtr, ProbeFunctor* probeFunctionPtr)
{
    this->m_arrLength = length;
    this->m_data = new KeyValPair<T, U>*[length];
    this->m_hashFunctionPtr = hashFunctionPtr;
    this->m_probeFunctionPtr = probeFunctionPtr;
}

/* dtor */
template <class T, class U>
HashTable_OpenAddressing<T, U>::~HashTable_OpenAddressing()
{

}

/* returns the pointer to a key value pair given key */
template <class T, class U>
HashTable_SearchResult<T, U>* HashTable_OpenAddressing<T, U>::find(const T& key)
{  
    unsigned int ind = (*this->m_hashFunctionPtr)(key);
    if (this->m_data[ind]->m_key == key)
    {
        // found
        HashTable_SearchResult<T, U> result;
        result.m_hashedKey = ind;
        result.m_kvpPtr = this->m_data[ind];
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
    unsigned int ind = (*this->m_hashFunctionPtr)(key);
    KeyValPair<T, U>* kvpPtr = new KeyValPair<T, U>; // copies the key and value
    kvpPtr->m_key = key;
    kvpPtr->m_val = val;
    if (this->m_data[ind] != nullptr)
    {
        std::cout << "Hash collision - require probing sequence" << std::endl;
    }
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
    this->m_numEntries--;
}

}; // namespace datastructlib