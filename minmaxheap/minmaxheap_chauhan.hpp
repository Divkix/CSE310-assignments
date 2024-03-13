// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 3/13/2024
//
// Description:
// This file contains the implementation of the MinHeap and MaxHeap classes.
// The MinHeap class is a min-heap implementation, and the MaxHeap class is a max-heap implementation.
// The MinHeap class is a template class, and the MaxHeap class is a template class.
//
// Note:
// I have also condensed the code for speed and efficiency

// include the necessary header files: iostream, algorithm, and stdexcept
#include <algorithm>
#include <iostream>
#include <stdexcept>

// using the template class to create a min heap
template <typename T>
// class for the min heap
class MinHeap
{
private:
    // private members of the class
    T *heapArray;     // data pointer to the array of elements in the heap
    int heapSize;     // current number of elements in the heap
    int heapCapacity; // maximum possible number of elements in the heap
    int heapIndex;    // index for the heap

    // function to min heapify the heap
    // it takes the index as the parameter
    void minheapify(int index)
    {
        // left and right side of the heap
        int leftSide = 2 * index;
        int rightSide = 2 * index + 1;
        // smallest number
        int smallestNumber = index;

        // if left side is less than the size and the data at left side is less than the data at smallest number
        smallestNumber = (leftSide <= heapSize && heapArray[leftSide] < heapArray[smallestNumber]) ? leftSide : smallestNumber;

        // if right side is less than the size and the data at right side is less than the data at smallest number
        smallestNumber = (rightSide <= heapSize && heapArray[rightSide] < heapArray[smallestNumber]) ? rightSide : smallestNumber;

        // if the smallest number is not equal to the index
        // then, swap the data at index and smallest number
        // and call the minheapify function
        if (smallestNumber != index)
        {
            // swap the data at index and smallest number
            swap(heapArray[index], heapArray[smallestNumber]);
            // call the minheapify function
            minheapify(smallestNumber);
        }
    }

public:
    // public members of the class

    // constructor for the min heap
    // takes the capacity as the parameter
    MinHeap(int capacity)
    {
        this->heapSize = 0;                        // set the size to 0
        this->heapCapacity = capacity;             // set the capacity to the capacity
        heapArray = new T[this->heapCapacity + 1]; // +1 to accommodate 1-based indexing
        if (!heapArray)                            // if the data is null, then throw an error
            throw runtime_error("Memory allocation failed.");
    }

    // destructor for the min heap
    ~MinHeap()
    {
        delete[] heapArray; // delete the data
    }

    // function to enqueue the element in the heap
    void enqueue(T element)
    {
        // if the size is equal to the capacity
        // then, throw an overflow error
        if (heapSize == heapCapacity)
            throw overflow_error("Heap is full.");

        // increment the size
        int index = ++heapSize;

        // set the data at index to the element
        heapArray[index] = element;

        // while the index is greater than 1 and the data at index is less than the data at index / 2
        // swap the data at index and index / 2
        // and set the index to index / 2
        while (index > 1 && heapArray[index] < heapArray[index / 2])
        {
            // swap the data at index and index / 2
            swap(heapArray[index], heapArray[index / 2]);

            // set the index to index / 2
            index /= 2;
        }
    }

    // function to dequeue the element from the heap
    void dequeue()
    {
        // if the heap is empty
        // then, throw an underflow error
        if (isEmpty())
            throw underflow_error("Heap is empty.");

        // set the data at 1 to the data at size
        heapArray[1] = heapArray[heapSize--];

        // call the minheapify function
        minheapify(1);
    }

    // function to check if the heap is empty
    bool isEmpty()
    {
        // return true if the size is 0
        return heapSize == 0;
    }

    // function to peek the element from the heap
    T peek()
    {
        // if the heap is empty
        // then, throw an underflow error
        if (isEmpty())
            throw underflow_error("Heap is empty");

        // return the data at 1
        return heapArray[1];
    }

    // function to get the size of the heap
    int getSize()
    {
        // return the size
        return heapSize;
    }

    // function to get the capacity of the heap
    int getCapacity()
    {
        // return the capacity
        return heapCapacity;
    }
};

// using the template class to create a max heap
template <typename T>
// class for the max heap
class MaxHeap
{
private:
    T *heapData;      // pointer to the array of elements in heap
    int heapCapacity; // current number of elements in heap
    int capacity;     // maximum possible number of elements in heap

    // function to max heapify the heap
    // it takes the index as the parameter
    void maxheapify(int index)
    {
        int left = 2 * index;      // left child index
        int right = 2 * index + 1; // right child index
        int largest = index;       // index of the largest element

        // if left child is less than or equal to size and data at left is greater than data at largest
        largest = (left <= heapCapacity && heapData[left] > heapData[largest]) ? left : largest;

        // if right child is less than or equal to size and data at right is greater than data at largest
        largest = (right <= heapCapacity && heapData[right] > heapData[largest]) ? right : largest;

        // if largest is not equal to index
        // then, swap the data at index and largest
        // and call the maxheapify function
        if (largest != index)
        {
            // swap the data at index and largest
            swap(heapData[index], heapData[largest]);
            // call the maxheapify function
            maxheapify(largest);
        }
    }

public:
    // public members of the class

    // constructor for the max heap
    // takes the capacity as the parameter
    MaxHeap(int capacity)
    {
        this->heapCapacity = 0;               // set the size to 0
        this->capacity = capacity;            // set the capacity to the capacity
        heapData = new T[this->capacity + 1]; // +1 to accommodate 1-based indexing

        // if the data is null, then throw an error
        if (!heapData)
            throw runtime_error("Memory allocation failed.");
    }

    // destructor for the max heap
    ~MaxHeap()
    {
        // delete the data
        delete[] heapData;
    }

    // function to enqueue the element in the heap
    // takes the element as the parameter
    void enqueue(T element)
    {
        // if the size is equal to the capacity
        // then, throw an overflow error
        if (heapCapacity == capacity)
            throw overflow_error("Heap is full.");

        int index = ++heapCapacity; // increment the size
        heapData[index] = element;  // set the data at index to the element

        // while the index is greater than 1 and the data at index is greater than the data at index / 2
        // swap the data at index and index / 2
        // and set the index to index / 2
        while (index > 1 && heapData[index] > heapData[index / 2])
        {
            // swap the data at index and index / 2
            swap(heapData[index], heapData[index / 2]);

            // set the index to index / 2
            index /= 2;
        }
    }

    // function to dequeue the element from the heap
    void dequeue()
    {
        // if the heap is empty
        // then, throw an underflow error
        if (isEmpty())
            throw underflow_error("Heap is empty.");

        // set the data at 1 to the data at size
        heapData[1] = heapData[heapCapacity--];

        // call the maxheapify function
        maxheapify(1);
    }

    // function to check if the heap is empty
    bool isEmpty()
    {
        // return true if the size is 0
        return heapCapacity == 0;
    }

    // function to peek the element from the heap
    T peek()
    {
        // if the heap is empty
        if (isEmpty())
            throw underflow_error("Heap is empty");

        // return the data at 1
        return heapData[1];
    }

    // function to get the size of the heap
    int getSize()
    {
        // return the size
        return heapCapacity;
    }

    // function to get the capacity of the heap
    int getCapacity()
    {
        // return the capacity
        return capacity;
    }
};