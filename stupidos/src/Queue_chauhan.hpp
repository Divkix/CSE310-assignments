//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 2/10/2024
//
// Description: This file contains the implementation of a Queue class and a Node class.
//              The Queue class is a singly linked list that is sorted in ascending order.
//              The Node class is a node for the Queue class.
//

// queue_chauhan.hpp
#ifndef QUEUE_CHAUHAN_HPP
#define QUEUE_CHAUHAN_HPP

// import the necessary libraries
#include <iostream>

// Node class for the Queue
template <typename T> // T is a generic type this is a template class
class Node            // Node class for the Queue
{
    // Properties
public:
    T data;     // Data of the node
    Node *next; // Pointer to the next node

    // Default constructor
    Node(T data) : data(data), next(nullptr) {}
};

// Queue class
template <typename T> // T is a generic type this is a template class
class Queue           // Queue class
{
    // Properties
private:
    Node<T> *frontNode; // Pointer to the front node
    Node<T> *rearNode;  // Pointer to the rear node
    int count;          // Number of items in the queue

public:
    // Default constructor
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    // Destructor
    ~Queue()
    {
        empty(); // Empties the queue
    }

    // Adds item to the queue
    void enqueue(T item)
    {
        Node<T> *newNode = new Node<T>(item); // Create a new node

        // if the rear node is null, then the front node is also null
        // else, the rear node's next pointer is the new node
        if (rearNode == nullptr)
        {
            frontNode = rearNode = newNode;
        }
        else
        {
            rearNode->next = newNode;
            rearNode = newNode;
        }

        // increment the count
        count++;
    }

    // Removes the front node of the queue
    void dequeue()
    {
        // if the front node is null, then return
        if (frontNode == nullptr)
            return;

        // otherwise, create a temporary node and set it to the front node
        Node<T> *temp = frontNode;
        frontNode = frontNode->next;

        // if the front node is null, then the rear node is also null
        if (frontNode == nullptr)
        {
            rearNode = nullptr;
        }

        // delete the temporary node
        delete temp;

        // decrement the count
        count--;
    }

    // Returns the item at the front of the queue without removal
    T front() const
    {
        // if the front node is null, then throw an exception
        if (frontNode == nullptr)
            throw std::out_of_range("Queue is empty");

        // otherwise, return the data of the front node
        return frontNode->data;
    }

    // Returns the number of items in the queue
    int size() const
    {
        return count; // return the count
    }

    // Empties the queue
    void empty()
    {
        // while the queue is not empty, remove the front node using dequeue
        while (!isEmpty())
        {
            dequeue(); // Remove the front node
        }
    }

    // Checks if the queue is empty
    bool isEmpty() const
    {
        // if the count is 0, then the queue is empty
        return count == 0;
    }
};

#endif // QUEUE_CHAUHAN_HPP
