#include <iostream>
#include "<BinaryHeap.hpp>"

using namespace datastructlib;

int main() {
    MaxCompareFunctor<int> maxFunctor;
    BinaryHeap<int> maxHeap(maxFunctor);

    maxHeap.insert(10);
    maxHeap.insert(4);
    maxHeap.insert(15);
    maxHeap.insert(8);
    maxHeap.insert(2);

    std::cout << "Heap contents (by level):\n";
    maxHeap.print();

    std::cout << "\nPolling top element: " << maxHeap.poll() << std::endl;

    std::cout << "\nHeap after polling:\n";
    maxHeap.print();

    std::cout << "\nRemoving value 8...\n";
    maxHeap.removeByVal(8);
    maxHeap.print();

    std::cout << "\nHeap invariant valid? " 
              << (maxHeap.checkHeapInvar() ? "Yes" : "No") << std::endl;

}