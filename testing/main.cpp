#include <iostream>

#include <Stack.hpp>

int main()
{
    datastructlib::Stack<float> myStack;
    
    myStack.push((float) 1.0);
    
    myStack.push((float) 2.0);
    myStack.push((float) 3.0);
    
    std::cout << myStack.peek() << std::endl;
    
    float tmp = myStack.pop();
    
    std::cout << myStack.pop() << std::endl;
}
