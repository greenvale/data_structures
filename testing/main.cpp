#include <iostream>

#include <Queue.hpp>

int main()
{
    datastructlib::Queue<float> myQueue;
    
    myQueue.enqueue(1.0);
    myQueue.enqueue(1.5);
    
    std::cout << myQueue.peek() << std::endl;
}
