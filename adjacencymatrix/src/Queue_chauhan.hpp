//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 4/6/2024
//
// Description: This file contains the declaration of the class Queue.
//              The class has been implemented to represent a queue using a linked list.
//              The class has been implemented to support the following operations:
//              1. Enqueue an element to the queue
//              2. Dequeue an element from the queue
//              3. Peek the front element of the queue
//              4. Check if the queue is empty
//              5. Get the size of the queue
//              This file has been used from a previous project 'StupidOS' as told in the assignment spec.
//

#ifndef QUEUE_CHAUHAN_HPP
#define QUEUE_CHAUHAN_HPP

// import stdexcept library to use runtime_error
#include <stdexcept>

// define the class Queue
template <typename T>
class Queue
{
    // define the private members of the class
private:
    // struct Node to store the data and the next pointer
    struct Node
    {
        T data;                                      // data of the node
        Node *next;                                  // pointer to the next node
        Node(const T &d) : data(d), next(nullptr) {} // constructor
    };

    Node *front; // pointer to the front of the queue
    Node *rear;  // pointer to the rear of the queue
    int size;    // size of the queue

    // define the public members of the class
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {} // default constructor

    // destructor
    ~Queue()
    {
        // dequeue all the elements in the queue while it is not empty
        while (!isEmpty())
        {
            // call the dequeue function
            dequeue();
        }
    }

    // enqueue function to add an element to the queue
    void enqueue(const T &item)
    {
        // create a new node with the data
        Node *newNode = new Node(item);

        // check if the queue is empty
        if (isEmpty())
        {
            // set the front and rear to the new node
            front = rear = newNode;
        }
        else
        // if the queue is not empty
        {
            // set the next pointer of the rear to the new node
            rear->next = newNode;
            // set the rear to the new node
            rear = newNode;
        }

        // increment the size of the queue
        size++;
    }

    // dequeue function to remove an element from the queue
    T dequeue()
    {
        // check if the queue is empty
        if (isEmpty())
        {
            // throw a runtime error
            throw std::runtime_error("Queue is empty. Cannot dequeue.");
        }

        Node *temp = front;  // create a temporary node and set it to the front
        T data = temp->data; // get the data of the front node
        front = front->next; // set the front to the next node
        delete temp;         // delete the temporary node
        size--;              // decrement the size of the queue

        // check if the queue is empty
        if (isEmpty())
        {
            // set the rear to null
            rear = nullptr;
        }

        // return the data of the front node
        return data;
    }

    // peek function to get the data of the front node
    T &peek() const
    {
        // check if the queue is empty, if so, throw a runtime error
        if (isEmpty())
        {
            // we throw the runtime error here
            throw std::runtime_error("Queue is empty. Cannot peek.");
        }

        // return the data of the front node
        return front->data;
    }

    // isEmpty function to check if the queue is empty
    bool isEmpty() const
    {
        // return true if the size is 0, false otherwise
        return size == 0;
    }

    // getSize function to get the size of the queue
    int getSize() const
    {
        // return the size of the queue
        return size;
    }
};

#endif // QUEUE_CHAUHAN_HPP
