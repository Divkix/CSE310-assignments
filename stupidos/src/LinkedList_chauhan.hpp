//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 2/10/2024
//
// Description: This file contains the implementation of a LinkedList class and a ListNode class.
//              The LinkedList class is a singly linked list that is sorted in ascending order.
//              The ListNode class is a node for the LinkedList class.

// LinkedList_chauhan.hpp
#ifndef LINKEDLIST_CHAUHAN_HPP
#define LINKEDLIST_CHAUHAN_HPP

// import the necessary libraries
#include <iostream>

// Node class for the LinkedList
template <typename T> // T is a generic type this is a template class
class ListNode        // Node class for the LinkedList
{
public:
    // Properties
    T data;         // Data of the node
    ListNode *next; // Pointer to the next node

    //  Default constructor
    ListNode(T data, ListNode *next = nullptr) : data(data), next(next) {}
};

// LinkedList class
template <typename T> // T is a generic type this is a template class
class LinkedList      // LinkedList class
{

    // Methods
public:
    ListNode<T> *head; // Pointer to the head of the list
    // Default constructor
    LinkedList() : head(nullptr) {}

    // Destructor
    ~LinkedList()
    {
        clear(); // Clears the list
    }

    // Begin function
    ListNode<T> *begin() const
    {
        return head;
    }

    // End function
    ListNode<T> *end() const
    {
        return nullptr;
    }

    // Inserts data into the linked list in a sorted manner
    void sortedInsert(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data); // Create a new node

        // if the head is null or the head's data is greater than or equal to the data
        if (head == nullptr || head->data >= data)
        {
            // the new node's next pointer is the head
            newNode->next = head;
            // and the head is the new node
            head = newNode;
        }
        else
        // else, traverse the list to find the right place to insert the new node
        {
            ListNode<T> *current = head; // Start at the head

            // while the current node's next pointer is not
            // null and the next node's data is less than the data
            while (current->next != nullptr && current->next->data < data)
            {
                // move to the next node
                current = current->next;
            }

            // the new node's next pointer is the current node's next pointer
            newNode->next = current->next;
            // and the current node's next pointer is the new node
            current->next = newNode;
        }
    }

    // Utility method to clear the list
    void clear()
    {
        ListNode<T> *current = head; // Start at the head

        // while the current node is not null
        while (current != nullptr)
        {
            // the next node is the current node's next pointer
            ListNode<T> *next = current->next;
            // delete the current node
            delete current;
            // the current node is the next node
            current = next;
        }
        // the head is null
        head = nullptr;
    }

    // Utility method to print the list - for verification and testing
    void printList() const
    {
        ListNode<T> *current = head; // Start at the head
        // while the current node is not null
        while (current != nullptr)
        {
            // the current node is the next node
            current = current->next;
        }
        // print NULL
        // std::cout << "NULL" << std::endl;
    }

    // size of the list
    int size() const
    {
        int count = 0;               // Start at 0
        ListNode<T> *current = head; // Start at the head
        // while the current node is not null
        while (current != nullptr)
        {
            // increment the count
            count++;
            // the current node is the next node
            current = current->next;
        }
        // return the count
        return count;
    }

    // Method to delete a node
    void deleteNode(const T &value)
    {
        ListNode<T> *current = head; // Start at the head
        ListNode<T> *prev = nullptr; // Start at the head
        // while the current node is not null
        while (current != nullptr)
        {
            // if the current node's data is equal to the value
            if (current->data == value)
            {
                // if the previous node is null
                if (prev == nullptr)
                {
                    // the head is the current node's next pointer
                    head = current->next;
                }
                // else, the previous node's next pointer is the current node's next pointer
                else
                {
                    // the previous node's next pointer is the current node's next pointer
                    prev->next = current->next;
                }
                // delete the current node
                delete current;
                return;
            }

            // the previous node is the current node
            prev = current;

            // the current node is the next node
            current = current->next;
        }
    }
};

#endif // LINKEDLIST_CHAUHAN_HPP