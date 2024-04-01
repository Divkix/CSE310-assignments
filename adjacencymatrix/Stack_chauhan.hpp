#ifndef STACK_CHAUHAN_HPP
#define STACK_CHAUHAN_HPP

#include <vector>
#include <stdexcept>

class Stack
{
private:
    std::vector<int> data;

public:
    void push(int value);
    int pop();
    bool isEmpty() const;
};

#endif // STACK_CHAUHAN_HPP
