#include <iostream>

#include "../include/FenwickTree.hpp"
#include <string>


int main() 
{
    std::vector<int> input = {3, 4, -2, 7, 3, 11, 5, -8, -9, 2, 4, -8};
    datastructlib::FenwickTree<int> ft(input);

    ft.pointUpdate(4, -10);
    std::cout << ft.rangeQuery(4, 8) << std::endl;
}