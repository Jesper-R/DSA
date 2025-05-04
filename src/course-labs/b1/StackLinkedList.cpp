#include "StackLinkedList.h"

#include <iostream>
#include <ostream>

int main(int argc, char* argv[])
{
    StackLinkedList<int> stack;
    stack.push(1);
    std::cout << stack.peek() << std::endl;
    stack.push(2);
    std::cout << stack.peek() << std::endl;
    stack.push(3);
    std::cout << stack.peek() << std::endl;

    std::cout << "Pop: " << stack.pop() << std::endl;
    std::cout << stack.peek() << std::endl;
    std::cout << "Pop: " << stack.pop() << std::endl;
    std::cout << "Pop: " << stack.pop() << std::endl;
    std::cout << stack.peek() << std::endl;
}
