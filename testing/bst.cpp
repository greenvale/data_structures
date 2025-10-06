#include <iostream>
#include <BinarySearchTree.hpp>

using namespace datastructlib;

int main() {
    BinarySearchTree<int> tree;

    std::cout << "=== Insertion Test ===" << std::endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.display();

    std::cout << "\n=== Duplicate Insert Test ===" << std::endl;
    bool result = tree.insert(30); // should fail
    std::cout << "Insert duplicate (30) -> " << (result ? "Success" : "Failed (duplicate)") << std::endl;

    std::cout << "\n=== Find Test ===" << std::endl;
    auto found = tree.find(70);
    if (found.m_ptr)
        std::cout << "Found 70 at node with value: " << found.m_ptr->m_val << std::endl;
    else
        std::cout << "Did not find 70" << std::endl;

    auto notFound = tree.find(999);
    if (notFound.m_ptr)
        std::cout << "Found 999 (unexpected)" << std::endl;
    else
        std::cout << "Correctly did not find 999" << std::endl;

    std::cout << "\n=== Removal Tests ===" << std::endl;

    std::cout << "Removing leaf node 20..." << std::endl;
    tree.remove(20);
    tree.display();

    std::cout << "Removing node with one child (60)..." << std::endl;
    tree.remove(60);
    tree.display();

    std::cout << "Removing node with two children (50, root)..." << std::endl;
    tree.remove(50);
    tree.display();

    std::cout << "\n=== Final Tree State ===" << std::endl;
    tree.display();

    std::cout << "\nAll tests completed!" << std::endl;
    return 0;
}