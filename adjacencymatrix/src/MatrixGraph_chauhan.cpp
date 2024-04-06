// import necessary libraries
#include "MatrixGraph_chauhan.h"
#include "Queue_chauhan.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

// Constructor for the MatrixGraph class
MatrixGraph::MatrixGraph(int numVertices, bool isDirected)
{
    // set the number of vertices and whether the graph is directed
    this->numVertices = numVertices;
    this->isDirected = isDirected;
    initializeMatrix(); // initialize the adjacency matrix
}

// destructor for the MatrixGraph class
MatrixGraph::~MatrixGraph()
{
    // delete the adjacency matrix
    deleteMatrix();
}

// addEdge function to add an edge between two vertices with a weight
void MatrixGraph::addEdge(int v1, int v2, float weight)
{
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        // add the edge to the adjacency matrix
        adjacencyMatrix[v1][v2] = weight;
        // if the graph is undirected, add the edge in the opposite direction
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = weight; // add the edge to the adjacency matrix
        }
    }
}

// addEdge function to add an edge between two vertices
void MatrixGraph::addEdge(int v1, int v2)
{
    addEdge(v1, v2, 1); // call the addEdge function with a weight of 1
}

// removeEdge function to remove an edge between two vertices
void MatrixGraph::removeEdge(int v1, int v2)
{
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        // remove the edge from the adjacency matrix
        adjacencyMatrix[v1][v2] = 0;
        // if the graph is undirected, remove the edge in the opposite direction
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = 0; // remove the edge from the adjacency matrix
        }
    }
}

// adjacent function to check if two vertices are adjacent
bool MatrixGraph::adjacent(int v1, int v2)
{
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        return adjacencyMatrix[v1][v2] != 0; // return whether the edge exists
    }
    return false; // return false if the vertices are invalid
}

// getEdgeWeight function to get the weight of an edge
float MatrixGraph::getEdgeWeight(int v1, int v2)
{
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        // return the weight of the edge if it exists
        if (adjacencyMatrix[v1][v2] != 0)
        {
            return adjacencyMatrix[v1][v2];
        }
        else
            // throw an exception if the edge does not exist
        {
            throw std::runtime_error("Edge does not exist");
        }
    }
    // throw an exception if the vertices are invalid
    throw std::runtime_error("Invalid vertex numbers");
}

// setEdgeWeight function to set the weight of an edge
void MatrixGraph::setEdgeWeight(int v1, int v2, float weight)
{
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        // set the weight of the edge if it exists
        adjacencyMatrix[v1][v2] = weight;
        // if the graph is undirected, set the weight in the opposite direction
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = weight; // set the weight of the edge
        }
    }
}

std::string MatrixGraph::toString()
{
    std::stringstream ss;
    for (int i = 0; i < numVertices; i++)
    {
        ss << "[" << std::setw(2) << i + 1 << "]:";
        for (int j = 0; j < numVertices; j++)
        {
            if (adjacencyMatrix[i][j] != 0)
            {
                ss << "-->";
                ss << "[" << std::setw(2) << i + 1 << "," << std::setw(2) << j + 1 << "::"
                   << std::right << std::setw(6) << std::setfill(' ') << std::fixed << std::setprecision(2) << adjacencyMatrix[i][j] << "]";
            }
        }
        ss << std::endl;
    }
    return ss.str();
}

// working perfectly, formatting is correct
void MatrixGraph::printRaw()
{
    std::cout << "Adjacency Matrix:" << std::endl << std::endl;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                      << adjacencyMatrix[i][j];
        }
        std::cout << std::endl;
    }
}

// pathExists function to check if a path exists between two vertices using BFS
bool MatrixGraph::pathExists(int v1, int v2)
{
    // check if the vertices are valid, return false if they are not
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
    {
        return false;
    }

    // create a vector to store whether each vertex has been visited
    std::vector<bool> visited(numVertices, false);
    Queue<int> queue; // create a queue to perform BFS

    // mark the starting vertex as visited and enqueue it
    visited[v1] = true;
    queue.enqueue(v1); // enqueue the starting vertex

    // perform BFS until the queue is empty
    while (!queue.isEmpty())
    {
        // dequeue a vertex from the queue
        int current = queue.dequeue();

        // check if the current vertex is the destination vertex, return true if it is
        if (current == v2)
        {
            return true;
        }

        // iterate through the neighbors of the current vertex
        for (int neighbor = 0; neighbor < numVertices; ++neighbor)
        {
            // check if the neighbor is connected to the current vertex and has not been visited
            if (adjacencyMatrix[current][neighbor] != 0 && !visited[neighbor])
            {
                // mark the neighbor as visited and enqueue it
                visited[neighbor] = true;
                // enqueue the neighbor
                queue.enqueue(neighbor);
            }
        }
    }

    // return false if the destination vertex is not reachable
    return false;
}

// getBFSPath function to get the path from one vertex to another using BFS
std::vector<int> MatrixGraph::getBFSPath(int v1, int v2)
{
    // check if the vertices are valid, return an empty vector if they are not
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
    {
        return {};
    }

    std::vector<bool> visited(numVertices, false); // create a vector to store whether each vertex has been visited
    std::vector<int> parent(numVertices, -1);      // create a vector to store the parent of each vertex
    Queue<int> queue;                              // create a queue to perform BFS

    visited[v1] = true; // mark the starting vertex as visited
    queue.enqueue(v1);  // enqueue the starting vertex

    // perform BFS until the queue is empty
    while (!queue.isEmpty())
    {
        // dequeue a vertex from the queue
        int current = queue.dequeue();

        // check if the current vertex is the destination vertex, break if it is
        if (current == v2)
        {
            break;
        }

        // iterate through the neighbors of the current vertex
        for (int neighbor = 0; neighbor < numVertices; ++neighbor)
        {
            // check if the neighbor is connected to the current vertex and has not been visited
            if (adjacencyMatrix[current][neighbor] != 0 && !visited[neighbor])
            {
                visited[neighbor] = true;   // mark the neighbor as visited
                parent[neighbor] = current; // set the parent of the neighbor
                queue.enqueue(neighbor);    // enqueue the neighbor
            }
        }
    }

    // create a vector to store the path from the starting vertex to the destination vertex
    std::vector<int> path;
    // check if the destination vertex is reachable
    if (visited[v2])
    {
        int current = v2; // set the current vertex to the destination vertex
        // iterate through the parents of the vertices to find the path
        while (current != -1)
        {
            path.push_back(current);   // add the current vertex to the path
            current = parent[current]; // set the current vertex to its parent
        }
        // reverse the path to get the correct order
        std::reverse(path.begin(), path.end());
    }

    // return the path from the starting vertex to the destination vertex
    return path;
}

// initializeMatrix function to initialize the adjacency matrix
void MatrixGraph::initializeMatrix()
{
    // create a 2D array to store the adjacency matrix
    adjacencyMatrix = new float *[numVertices];
    // iterate through the vertices
    for (int i = 0; i < numVertices; i++)
    {
        // create an array to store the neighbors of the vertex
        adjacencyMatrix[i] = new float[numVertices]();
    }
}

// deleteMatrix function to delete the adjacency matrix
void MatrixGraph::deleteMatrix()
{
    // iterate through the vertices
    for (int i = 0; i < numVertices; i++)
    {
        delete[] adjacencyMatrix[i]; // delete the array of neighbors
    }
    // delete the array of vertices
    delete[] adjacencyMatrix;
}
