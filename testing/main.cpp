#include <iostream>

#include "../include/HashTable.hpp"
#include <string>

class MyHashFunctor : public datastructlib::HashFunctor<unsigned int>
{
public:
    unsigned int operator()(const unsigned int& key, const unsigned int& arrLength)
    {
        return (key*key + 3) % arrLength;
    }
};

int main() 
{
    MyHashFunctor hashFunc;
    datastructlib::LinearProbeFunctor probeFunc(3, 0);
    
    //datastructlib::HashTable_DynamicArrayInterface<unsigned int, std::string> interface;
    datastructlib::HashTable_SinglyLinkedListInterface<unsigned int, std::string> interface;

    datastructlib::HashTable_SeperateChaining< unsigned int, std::string, datastructlib::SinglyLinkedList< datastructlib::KeyValPair< unsigned int, std::string >* > > ht(10, &interface, &hashFunc);

    ht.insert(25, "Maths");
    ht.insert(41, "Chemistry");
    ht.insert(10, "Physics");
    ht.insert(12, "Maths");
    ht.insert(81, "Chemistry");
    ht.insert(46, "Physics");
    ht.insert(42, "Maths");
    ht.insert(39, "Chemistry");
    ht.insert(92, "Physics");
    ht.insert(4, "Maths");
    ht.insert(15, "Chemistry");
    ht.insert(61, "Physics");
    
    datastructlib::HashTable_SearchResult<unsigned int, std::string> result = ht.find(25);
    std::cout << result.m_kvpPtr << std::endl;
    std::cout << result.m_kvpPtr->m_val << std::endl;
    std::cout << std::endl;

    ht.display();
}