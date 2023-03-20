/* Hash table - W Denny
    - uses functors for hashing function and probing function
    - supports seperate-chaining and open-addressing collision resolution methods
    - seperate-chaining is flexible for different data structure objects by means of an interface class object
    - this interface class object must be defined for a given datatype - currently defined for own-made DynamicArray and SinglyLinkedList data structure classes
    - upon creating seperate-chaining object you pass the interface derived class for the required data type
*/
#pragma once

#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
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
        std::cout << "Error in hash functor derivation" << std::endl;
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
    //LinearProbeFunctor() = delete;
    LinearProbeFunctor(const unsigned int& a, const unsigned int& b)
    {
        assert(a > 0);
        //assert(a % 2 != 0); // a must not be even - this is because array length in hash table will always be even
        this->m_a = a;
        this->m_b = b;
    }
    void reset()
    {
        this->m_x = 0;
    }
    unsigned int increment(const unsigned int& arrLength)
    {
        //assert(arrLength % m_a != 0); // ensure that a and array size are relatively prime
        this->m_x += 1;
        return m_a*this->m_x + m_b;
    }
};

/* Quadratic probing function */
class QuadraticProbeFunctor : public ProbeFunctor
{
private:
    unsigned int m_x;
    unsigned int m_a;
    unsigned int m_b;
    unsigned int m_c;
public:
    //LinearProbeFunctor() = delete;
    QuadraticProbeFunctor(const unsigned int& a, const unsigned int& b, const unsigned int& c)
    {
        //assert(a > 0);
        //assert(a % 2 != 0); // a must not be even - this is because array length in hash table will always be even
        this->m_a = a;
        this->m_b = b;
        this->m_c = c;
    }
    void reset()
    {
        this->m_x = 0;
    }
    unsigned int increment(const unsigned int& arrLength)
    {
        //assert(arrLength % m_a != 0); // ensure that a and array size are relatively prime
        this->m_x += 1;
        return m_a*this->m_x*this->m_x + m_b*this->m_x + this->m_c;
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
    bool m_tombstone = false;
    KeyValPair() {}
    KeyValPair(const T& key, const U& val)
    {
        this->m_key = key;
        this->m_val = val;
    }
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
    double loadFactor() const
    {
        return ((double) this->m_numEntries) / ((double) this->m_arrLength);
    }
};

/********************************************************************************************************************/
/* HASH TABLE WITH SEPERATE CHAINING CLASS */

/* every data structure used for seperate chaining will have different insertion/removal calling functions - this is a general interface functor that generalises these 
this is the base class from which each data structure will have a derived functor class
*/
template <class T, class U>
class HashTable_DataStructInterface
{
public:
    HashTable_DataStructInterface() {}
    virtual U get(const T& ds, const unsigned int& ind) {
        std::cout << "Error in data struct interface derivation" << std::endl;
        return U(0);
    }
    virtual void append(T& ds, U kvpPtr) {std::cout << "Error in data struct interface derivation" << std::endl;}
    virtual void remove(T& ds, const unsigned int& ind) {std::cout << "Error in data struct interface derivation" << std::endl;}
    virtual unsigned int length(const T& ds) {
        std::cout << "Error in data struct interface derivation" << std::endl;
        return 0;
    }
};

/* interface for dynamic array class */
template <class T, class U>
class HashTable_DynamicArrayInterface : virtual public HashTable_DataStructInterface< DynamicArray<KeyValPair<T, U>*>, KeyValPair<T, U>* >
{
public:
    KeyValPair<T, U>* get(const DynamicArray<KeyValPair<T, U>*>& ds, const unsigned int& ind)
    {
        return ds.get(ind);
    }
    void append(DynamicArray<KeyValPair<T, U>*>& ds, KeyValPair<T, U>* kvpPtr)
    {
        ds.append(kvpPtr);
    }

    void remove(DynamicArray<KeyValPair<T, U>*>& ds, const unsigned int& ind)
    {
        ds.remove(ind);
    }
    unsigned int length(const DynamicArray<KeyValPair<T, U>*>& ds)
    {
        return ds.length();
    }
};

/* interface for singly-linked list */
template <class T, class U>
class HashTable_SinglyLinkedListInterface : virtual public HashTable_DataStructInterface< SinglyLinkedList<KeyValPair<T, U>*>, KeyValPair< T, U>* >
{
public:
    
    KeyValPair<T, U>* get(const SinglyLinkedList<KeyValPair<T, U>*>& ds, const unsigned int& ind)
    {
        SingleNode<KeyValPair<T, U>*>* nodePtr = ds.getPtr(ind);
        return nodePtr->getVal();
    }
    void append(SinglyLinkedList<KeyValPair<T, U>*>& ds, KeyValPair<T, U>* kvpPtr)
    {
        SingleNode<KeyValPair<T, U>*>* nodePtr = new SingleNode<KeyValPair<T, U>*>(kvpPtr);
        ds.insertTail(nodePtr);
    }
    void remove(SinglyLinkedList<KeyValPair<T, U>*>& ds, const unsigned int& ind)
    {
        ds.remove(ind);
    }
    unsigned int length(const SinglyLinkedList<KeyValPair<T, U>*>& ds)
    {
        return ds.length();
    }
};

/* Seperate chaining hash table 
*/
template <class T, class U, class V>
class HashTable_SeperateChaining : public HashTable<T, U>
{
private:
    V* m_data; // array of data structures of type V containing ptrs to key-value pairs
    HashTable_DataStructInterface<V, KeyValPair<T, U>*>* m_dataStructInterfacePtr; // interface for manipulating general data structure (as each type has different calling functions, they require individual interface)
public:
    HashTable_SeperateChaining() = delete;
    HashTable_SeperateChaining(const unsigned int& length, HashTable_DataStructInterface<V, KeyValPair<T, U>*>* dataStructInterfacePtr, HashFunctor<T>* hashFunctionPtr);
    ~HashTable_SeperateChaining();
    HashTable_SearchResult<T, U> find(const T& key) const;
    void insert(const T& key, const U& val);
    bool remove(const T& key);
    void display();
};

/* ctor */
template <class T, class U, class V>
HashTable_SeperateChaining<T, U, V>::HashTable_SeperateChaining(const unsigned int& length, HashTable_DataStructInterface<V, KeyValPair<T, U>*>* dataStructInterfacePtr, HashFunctor<T>* hashFunctionPtr)
{
    this->m_arrLength = length;
    this->m_data = new V[length]; // create array of data structures of type V containing ptrs to key-value pairs
    this->m_hashFunctionPtr = hashFunctionPtr;
    this->m_dataStructInterfacePtr = dataStructInterfacePtr;
    this->m_numEntries = 0;
}

/* dtor */
template <class T, class U, class V>
HashTable_SeperateChaining<T, U, V>::~HashTable_SeperateChaining()
{
    // finish this function properly
    delete[] this->m_data;
}

/* returns the pointer to a key value pair given key */
template <class T, class U, class V>
HashTable_SearchResult<T, U> HashTable_SeperateChaining<T, U, V>::find(const T& key) const
{  
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    for (unsigned int i = 0; i < this->m_dataStructInterfacePtr->length(this->m_data[hashedKey]); ++i) // traverse chain
    {
        if (this->m_dataStructInterfacePtr->get(this->m_data[hashedKey], i)->m_key == key)
        {
            std::cout << "Found" << std::endl;
            // found
            HashTable_SearchResult<T, U> result;
            result.m_hashedKey = hashedKey;
            result.m_sepChainInd = i;
            result.m_kvpPtr = this->m_dataStructInterfacePtr->get(this->m_data[hashedKey], i); // use data structure interface to get ptr from chain
            return result;
        }
    }
    // not found
    HashTable_SearchResult<T, U> result;
    result.m_kvpPtr = nullptr;
    return result;
}

/* inserts new entry into hash table */
template <class T, class U, class V>
void HashTable_SeperateChaining<T, U, V>::insert(const T& key, const U& val)
{
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    std::cout << "Insertion : Key " << key << " maps onto index " << hashedKey << "\t";
    std::cout << "Chain @ index " << hashedKey << " has " << this->m_dataStructInterfacePtr->length(this->m_data[hashedKey]) << " existing entry/entries" << std::endl;
    KeyValPair<T, U>* kvpPtr = new KeyValPair<T, U>(key, val); // copies the key and value into new key-value pair object
    this->m_dataStructInterfacePtr->append(this->m_data[hashedKey], kvpPtr); // use data structure interface to append onto the chain
    this->m_numEntries++;
}

/* remove entry from hash table by key */
template <class T, class U, class V>
bool HashTable_SeperateChaining<T, U, V>::remove(const T& key)
{
    HashTable_SearchResult<T, U> result = this->find(key);
    if (result.m_kvpPtr == nullptr)
    {
        return false; // object not found inside hash table
    }
    this->m_dataStructInterfacePtr->remove(this->m_data[result.m_hashedKey], result.m_sepChainInd); // use data structure interface to remove from the chain
    std::cout << "Removal : Key " << key << " and value pair removed from dynamic array @ index " << result.m_hashedKey << std::endl;
    this->m_numEntries--;
}

/* display 
    - note the value datatype must be defined for ostream operator
*/
template <class T, class U, class V>
void HashTable_SeperateChaining<T, U, V>::display()
{
    std::cout << "======================" << std::endl;
    for (unsigned int i = 0; i < this->m_arrLength; ++i)
    {
        std::cout << "Index (" << i << "):" << std::endl;
        for (unsigned int j = 0; j < this->m_dataStructInterfacePtr->length(this->m_data[i]); ++j)
        {
            KeyValPair<T, U>* kvpPtr = this->m_dataStructInterfacePtr->get(this->m_data[i], j);
            std::cout << "\t Key: " << kvpPtr->m_key << " -> Value: " << kvpPtr->m_val << std::endl;
        }
    }
    std::cout << "======================" << std::endl;
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
    HashTable_SearchResult<T, U> find(const T& key) const;
    void insert(const T& key, const U& val);
    bool remove(const T& key);
    void display();
    void resizeArray(const unsigned int& newLength); 
};

/* ctor */
template <class T, class U>
HashTable_OpenAddressing<T, U>::HashTable_OpenAddressing(const unsigned int& length, HashFunctor<T>* hashFunctionPtr, ProbeFunctor* probeFunctionPtr, const double& maxLoadFactor)
{
    //assert(length % 2 == 0); // array length must be even, to ensure probing function gcd = 1
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
HashTable_SearchResult<T, U> HashTable_OpenAddressing<T, U>::find(const T& key) const
{  
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    unsigned int ind = hashedKey;
    KeyValPair<T, U>* tombstonePtr = nullptr;
    this->m_probeFunctionPtr->reset(); // reset probe function ptr to base value
    while (this->m_data[ind] != nullptr)
    {
        if ((this->m_data[ind]->m_key == key) && (this->m_data[ind]->m_tombstone == false)) // if key matches and the key-value pair hasn't been marked with tombstone
        {
            // found
            HashTable_SearchResult<T, U> result;
            result.m_hashedKey = hashedKey;
            if (tombstonePtr != nullptr) // if relevent tombstone was encountered in probing, transfer data to this and delete the original key-value pair
            {
                tombstonePtr->m_key = key; 
                tombstonePtr->m_val = this->m_data[ind]->m_val;
                tombstonePtr->m_tombstone = false;
                result.m_kvpPtr = tombstonePtr;
                delete this->m_data[ind]; // delete original
                this->m_data[ind] = nullptr;
                std::cout << "Found key " << key << " and moved from index " << ind << std::endl;
            }
            else
            {
                result.m_kvpPtr = this->m_data[ind];
                std::cout << "Found key" << std::endl;
            }
            return result;
        }
        else
        {
            if ((this->m_data[ind]->m_tombstone == true) && (tombstonePtr == nullptr))
            {
                tombstonePtr = this->m_data[ind]; // keep track of first tombstone to move value to this...
            }
            ind = (hashedKey + this->m_probeFunctionPtr->increment(this->m_arrLength)) % this->m_arrLength; // increment probing sequence
        }
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
        std::cout << "Array size must increase to: " << 2 * this->m_arrLength << std::endl;
        this->resizeArray(this->m_arrLength * 2);
    }

    // proceed with inserting the new key-value pair by hashing key and probing if necessary
    unsigned int hashedKey = (*this->m_hashFunctionPtr)(key, this->m_arrLength);
    std::cout << "Insertion (" << this->m_numEntries << ") : Key " << key << " maps onto index " << hashedKey << std::endl;
    unsigned int ind = hashedKey;
    this->m_probeFunctionPtr->reset(); // reset probe function ptr to base value
    while ((this->m_data[ind] != nullptr) && (this->m_data[ind]->m_tombstone == false)) // either empty bucket or entry marked with tombstone
    {
        std::cout << "\t Hash collision @ index " << ind << std::endl;
        ind = (hashedKey + this->m_probeFunctionPtr->increment(this->m_arrLength)) % this->m_arrLength;
    }
    std::cout << "\t Final index: " << ind << std::endl;
    if ((this->m_data[ind] == nullptr)) // empty bucket
    {
        KeyValPair<T, U>* kvpPtr = new KeyValPair<T, U>(key, val); // copies the key and value
        this->m_data[ind] = kvpPtr;
        this->m_numEntries++;
    }
    else // replacing tombstone-marked entry
    {
        this->m_data[ind]->m_key = key;
        this->m_data[ind]->m_val = val;
        this->m_data[ind]->m_tombstone = false;
    }    
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
    result.m_kvpPtr->m_tombstone = true; // mark as tombstone
    std::cout << "Removal : Key " << key << " and value pair removed from dynamic array @ index " << result.m_hashedKey << ", now marked as tombstone" << std::endl;
    //this->m_numEntries--;
    return true;
}

/* display 
    - note the value datatype must be defined for ostream operator
*/
template <class T, class U>
void HashTable_OpenAddressing<T, U>::display()
{
    std::cout << "======================" << std::endl;
    for (unsigned int i = 0; i < this->m_arrLength; ++i)
    {
        std::cout << "Index (" << i << ") \t |";
        if (this->m_data[i] != nullptr)
        {
            if (this->m_data[i]->m_tombstone == false)
            {
                std::cout << "\t Key: " << this->m_data[i]->m_key << " -> Value: " << this->m_data[i]->m_val << std::endl;
            }
            else
            {
                std::cout << "\t Tombstone" << std::endl;
            }
        }
        else
        {
            //std::cout << "\t NULLPTR" << std::endl;
            std::cout << std::endl;
        }
    }
    std::cout << "======================" << std::endl;
}

/* resize array
- adjust the array to new size - new size cannot be smaller than existing number of entries
*/
template <class T, class U>
void HashTable_OpenAddressing<T, U>::resizeArray(const unsigned int& newLength)
{
    // make copy of existing data and clear array
    assert(newLength >= this->m_numEntries);
    DynamicArray<KeyValPair<T, U>*> tmp; // make a copy of the key-value pairs in a new array
    for (unsigned int i = 0; i < this->m_arrLength; ++i)
    {
        if ((this->m_data[i] != nullptr) && (this->m_data[i]->m_tombstone == false)) // check key-value pair exists and isn't marked with tombstone
        {
            KeyValPair<T, U>* kvpPtr = new KeyValPair<T, U>(this->m_data[i]->m_key, this->m_data[i]->m_val);
            tmp.append(kvpPtr);
            delete this->m_data[i];
            this->m_data[i] = nullptr;
        }
    }
    delete[] this->m_data;

    // repopulate array with data from copy
    this->m_arrLength = newLength;
    this->m_data = new KeyValPair<T, U>*[this->m_arrLength]; // create array of pointers with the new size
    this->m_numEntries = 0;
    for (unsigned int i = 0; i < tmp.length(); ++i)
    {
        this->insert(tmp.get(i)->m_key, tmp.get(i)->m_val);
        delete tmp.get(i);
    }
}

}; // namespace datastructlib