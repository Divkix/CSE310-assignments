#ifndef QUEUE_CHAUHAN_HPP
#define QUEUE_CHAUHAN_HPP

#include <vector>
#include <stdexcept>

class Queue
{
private:
    std::vector<int> data;

public:
    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
};

#endif // QUEUE_CHAUHAN_HPP
