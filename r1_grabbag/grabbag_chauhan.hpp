#include <iostream>
#include <ctime>
#include <random>
#include <memory>
#include <optional>

// Node class for the linked list
template <typename T>
class Node
{
public:
    T item;                        // The item stored in the node
    std::shared_ptr<Node<T>> next; // Pointer to the next node

    // Constructor
    Node(T item) : item(item), next(nullptr) {}
};

// GrabBag class
template <typename T>
class GrabBag
{
private:
    int count;                      // Number of items in the bag
    unsigned int seed;              // Seed for the random number generator
    std::shared_ptr<Node<T>> front; // Pointer to the front of the linked list
    std::minstd_rand randgen;       // Random number generator

public:
    // Default constructor
    GrabBag() : seed(static_cast<unsigned int>(time(NULL))), count(0), front(nullptr)
    {
        randgen.seed(seed); // Seed the random number generator
    }

    // Constructor with seed
    GrabBag(unsigned int newSeed) : seed(newSeed), count(0), front(nullptr)
    {
        randgen.seed(newSeed); // Seed the random number generator
    }

    // Returns the size of the bag
    int size() const
    {
        return count;
    }

    // Checks if the bag is empty
    bool empty() const
    {
        return count == 0;
    }

    // Adds an item to the bag
    void add(T item)
    {
        auto newNode = std::make_shared<Node<T>>(item); // Create a new node
        if (front == nullptr)
        {
            front = newNode; // If the bag is empty, the new node becomes the front
        }
        else
        {
            newNode->next = front; // Otherwise, the new node is added to the front
            front = newNode;
        }
        count++; // Increase the count
    }

    // Grabs a random item from the bag
    std::optional<T> grab()
    {
        if (empty())
        {
            return std::nullopt; // If the bag is empty, return nullopt
        }

        std::uniform_int_distribution<int> dist(0, count - 1); // Uniform distribution
        int randomIndex = dist(randgen);                       // Generate a random index
        auto current = front;
        std::shared_ptr<Node<T>> rear = nullptr;

        // Traverse the list to the random index
        for (int i = 0; i < randomIndex; i++)
        {
            rear = current;
            current = current->next;
        }

        // Remove the node from the list
        if (rear == nullptr)
        {
            front = current->next;
        }
        else
        {
            rear->next = current->next;
        }
        count--;              // Decrease the count
        return current->item; // Return the item
    }

    // Returns the frequency of an item in the bag
    int frequencyOf(T item) const
    {
        int frequency = 0;
        auto current = front;
        while (current != nullptr)
        {
            if (current->item == item)
            {
                frequency++; // Increase the frequency if the item is found
            }
            current = current->next;
        }
        return frequency;
    }

    // Clears the bag
    void clear()
    {
        front = nullptr; // Set the front to nullptr
        count = 0;       // Reset the count
    }
};