#include <iostream>

#include <BinaryHeap.hpp>

int main()
{
    datastructlib::MinCompareFunctor<double> compareFunctor;
    datastructlib::BinaryHeap<double> bh(&compareFunctor);

    bh.insert(1.0);
    bh.insert(0.4);
    bh.insert(0.6);
    bh.insert(1.4);
    bh.insert(1.1);
    bh.insert(1.5);
    bh.insert(0.2);
    bh.insert(0.5);
    bh.insert(0.1);

    bh.print();

    bh.removeByVal(0.5);
    
    std::cout << std::endl << std::endl;

    bh.print();
}
