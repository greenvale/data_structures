#include <iostream>

#include <BinarySearchTree.hpp>

int main() 
{
    datastructlib::BinarySearchTree<double> bst;
    bst.insert(10.0);
    bst.insert(8.0);
    bst.insert(12.0);
    bst.insert(7.0);
    bst.insert(9.0);
    bst.insert(11.0);
    bst.insert(13.0);
    bst.insert(6.5);
    bst.insert(7.5);
    bst.insert(8.5);
    bst.insert(9.5);
    bst.insert(10.5);
    bst.insert(11.5);
    bst.insert(12.5);
    bst.insert(13.5);

    bst.remove(13.0);

    bst.display();
}