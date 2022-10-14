#include <iostream>

#include <HashTable.hpp>
#include <string>

class MyHashFunctor : public datastructlib::HashFunctor<unsigned int>
{
public:
    unsigned int operator()(const unsigned int& key, const unsigned int& arrSize)
    {
        return (key*key + 3) % arrSize;
    }
};



int main() 
{
    MyHashFunctor hashFunc;
    datastructlib::LinearProbeFunctor probeFunc(3, 0);
    
    datastructlib::HashTable_OpenAddressing<unsigned int, std::string> ht(10, &hashFunc, &probeFunc, 1.0);

    ht.insert(25, "Maths");
    ht.insert(41, "Chemistry");
    ht.insert(10, "Physics");
    ht.insert(12, "Maths");
    ht.insert(81, "Chemistry");
    ht.insert(46, "Physics");
    
    datastructlib::HashTable_SearchResult<unsigned int, std::string> result = ht.find(25);
    std::cout << result.m_kvpPtr->m_val << std::endl;
}