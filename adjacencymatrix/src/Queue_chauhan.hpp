#ifndef QUEUE_CHAUHAN_HPP
#define QUEUE_CHAUHAN_HPP

#include <stdexcept>

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &d) : data(d), next(nullptr) {}
    };

    Node *front;
    Node *rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    void enqueue(const T &item)
    {
        Node *newNode = new Node(item);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty. Cannot dequeue.");
        }
        Node *temp = front;
        T data = temp->data;
        front = front->next;
        delete temp;
        size--;
        if (isEmpty())
        {
            rear = nullptr;
        }
        return data;
    }

    T &peek() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty. Cannot peek.");
        }
        return front->data;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }
};

#endif // QUEUE_CHAUHAN_HPP