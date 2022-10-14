#include <iostream>

#include <HashTable.hpp>
#include <string>

class MyHashFunctor : public datastructlib::HashFunctor<unsigned int>
{
public:
    unsigned int operator()(const unsigned int& key)
    {
        return (key*key + 3) % 10;
    }
};

int main() 
{
    MyHashFunctor func;
    
    datastructlib::HashTable_SeperateChaining<unsigned int, std::string> ht(10, &func);

    ht.insert(25, "Maths");
    ht.insert(41, "Chemistry");
    ht.insert(10, "Physics");
    
    datastructlib::HashTable_SearchResult<unsigned int, std::string> result = ht.find(25);
    std::cout << result.m_kvpPtr->m_val << std::endl;
}