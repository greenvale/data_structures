#include <HashTable.hpp>
using namespace datastructlib;

class IntHash : public HashFunctor<int> {
public:
    unsigned int operator()(const int& key, const unsigned int& arrLength) override {
        return key % arrLength;
    }
};

int main() {
    IntHash hashFunc;
    HashTable_DynamicArrayInterface<int, int> interface;
    HashTable_SeperateChaining<int, int, DynamicArray<KeyValPair<int, int>*>> ht(5, &interface, &hashFunc);

    ht.insert(1, 100);
    ht.insert(6, 200);
    ht.insert(11, 300);
    ht.display();

    ht.remove(6);
    ht.display();

    return 0;
}