// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 2/2/2024
//
// Description:
// This assignment is based on using the pointer function to add and delete the items from the class grabbag
// that is been created and it also uses throw excepetion if the bag is empty and  this assignment uses
// constructors and destructors and also uses get function. and uses random for random generation of
// number linked to the seed
//
// Note:
// I have also condensed the code for speed and efficiency

// include the necessary libraries
#include <iostream>
#include <ctime>
#include <random>

// BagNode class for the nodes in the grab bag
template <typename T>
class BagNode
{
private:
    T item;           // Item stored in the node
    BagNode<T> *next; // Pointer to the next node

public:
    // Constructor to initialize the node with its item and next pointer
    BagNode(T item) : item(item), next(nullptr) {}

    // Method to get the item from the node
    // this is a getter function, returns the item
    T getItem()
    {
        return item;
    }

    // Method to get the next node pointer
    // this is a getter function, returns the next node
    BagNode<T> *getNext()
    {
        return next;
    }

    // Method to set the next node pointer
    // this is a setter function, sets the next node
    void setNext(BagNode<T> *nextNode)
    {
        next = nextNode;
    }
};

// GrabBag class for managing a collection of items
template <typename T>
class GrabBag
{
    // Private data members and methods
    // these only accessible by the class
private:
    int counter;              // Counter for the number of items in the bag
    unsigned int randomSeed;  // Seed for random number generation
    BagNode<T> *firstItem;    // Pointer to the front of the bag
    std::minstd_rand randgen; // Random number generator

    // Public data members and methods
    // these are accessible by the class and the main function
public:
    // Constructor to initialize the GrabBag with a random seed
    GrabBag()
    {
        randomSeed = static_cast<unsigned int>(time(NULL)); // Get the current time as the seed
        counter = 0;                                        // Counter initialized to 0
        firstItem = nullptr;                                // First item has been initialized as a null pointer
        randgen.seed(randomSeed);                           // Seed the random number generator
    }

    // Constructor to initialize the GrabBag with a specific seed
    GrabBag(unsigned int newRandomSeed)
    {
        randomSeed = newRandomSeed;  // declaring the seed to new seed
        counter = 0;                 // again initialize count to 0
        firstItem = nullptr;         // declaring first as nullptr
        randgen.seed(newRandomSeed); // Seed the random number generator with the specified seed
    }

    // Method to get the current size of the bag
    int getCurrentSize()
    {
        return counter; // Return the current size of the bag
    }

    // Method to check if the bag is empty
    bool isEmpty()
    {
        return counter == 0; // If the count is zero, then the bag is empty
    }

    // Method to add an item to the bag
    void add(T item)
    {
        BagNode<T> *newNode = new BagNode<T>(item); // Create a new node for the item

        // if the bag is empty
        // Set the new node as the front
        // else
        // Set the next pointer of the new node to the current front
        if (firstItem == nullptr)
        {
            firstItem = newNode; // Set the new node as the front
        }
        else
        {
            newNode->setNext(firstItem); // Set the next pointer of the new node to the current front
            firstItem = newNode;         // Update the front to the new node
        }

        // Increment the count of items in the bag
        counter++;
    }

    // Destructor to delete all dynamically allocated nodes
    ~GrabBag()
    {
        empty(); // Ensures all dynamically allocated nodes are deleted.
    }

    // Method to randomly grab and remove an item from the bag
    T grab()
    {
        // if the bag is empty
        // Throw an error
        if (isEmpty())
        {
            throw std::out_of_range("The bag is empty"); // Throw an error if the bag is empty
        }

        std::uniform_int_distribution<int> dist(0, counter - 1); // Create a uniform distribution for random index
        int randomIndexNum = dist(randgen);                      // Generate a random index
        BagNode<T> *current = firstItem;                         // Start from the front of the bag
        BagNode<T> *rear = nullptr;                              // Initialize the rear pointer to nullptr

        for (int i = 0; i < randomIndexNum; i++)
        {                                 // Iterate to the randomly selected index
            rear = current;               // Rear becomes the current node
            current = current->getNext(); // Move to the next node
        }

        if (rear == nullptr)
        {
            firstItem = current->getNext(); // If the removed node is at the front, update the front pointer
        }
        else
        {
            rear->setNext(current->getNext()); // Link the previous node to the next node, skipping the removed node
        }
        counter--;                   // Decrement the count of items in the bag
        T item = current->getItem(); // Get the item from the removed node
        delete current;              // Delete the removed node
        return item;                 // Return the removed item
    }

    // Method to get the frequency of a specific item in the grab bag
    int getFrequencyOf(T item)
    {
        int frequency = 0;               // Initialize the frequency counter to 0
        BagNode<T> *current = firstItem; // Start at the front of the bag
        while (current != nullptr)
        { // Iterate through the bag
            if (current->getItem() == item)
            {                // If the current item is equal to the target item
                frequency++; // Increment the frequency counter
            }
            current = current->getNext(); // Move to the next item in the bag
        }
        return frequency; // Return the frequency of the item in the bag
    }

    void empty()
    {
        while (firstItem != nullptr)
        {
            BagNode<T> *temp = firstItem;     // Create a temp pointer to the current front node
            firstItem = firstItem->getNext(); // Move the front pointer to the next node
            delete temp;                      // Delete the temp node
        }
        counter = 0; // Reset the count to 0
    }
};