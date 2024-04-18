//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 4/16/2024
//
// Description: This file contains the implementation of the MatrixGraph class.
//              The MatrixGraph class is used to represent a graph using an adjacency matrix.
//              The class provides functions to add and remove edges, check if two vertices are adjacent,
//              get the weight of an edge, set the weight of an edge, and get a string representation of the graph.
//              The class also provides functions to check if a path exists between two vertices and get the path between two vertices using BFS.
//              The class uses a 2D array to store the adjacency matrix and provides functions to initialize and delete the adjacency matrix.
//              The class also provides a function to print the raw adjacency matrix.
//              The class is used to represent both directed and undirected graphs.
//              The class uses a Queue class to perform BFS to check if a path exists between two vertices and get the path between two vertices.
//

// import necessary libraries
#include "MatrixGraph_chauhan.h"
#include "Queue_chauhan.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include "minmaxheap_chauhan.hpp"

// Constructor for the MatrixGraph class
// numVertices: the number of vertices in the graph
// isDirected: a boolean to check if the graph is directed or not
MatrixGraph::MatrixGraph(int numVertices, bool isDirected) {
    // set the number of vertices and whether the graph is directed
    this->numVertices = numVertices;
    this->isDirected = isDirected;

    // initialize the adjacency matrix
    initializeMatrix();
}

// Destructor for the MatrixGraph class
MatrixGraph::~MatrixGraph() {
    // delete the adjacency matrix
    deleteMatrix();
}

// addEdge function
// v1: the first vertex
// v2: the second vertex
// weight: the weight of the edge
// used to add an edge between two vertices with a weight
void MatrixGraph::addEdge(int v1, int v2, float weight) {
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        // add the edge to the adjacency matrix
        adjacencyMatrix[v1][v2] = weight;
        // if the graph is undirected, add the edge in the opposite direction
        if (!isDirected) {
            // add the edge to the adjacency matrix
            adjacencyMatrix[v2][v1] = weight;
        }
    }
}

// addEdge function
// v1: the first vertex
// v2: the second vertex
// used to add an edge between two vertices with
// a default weight of 1 or if no weight is provided
void MatrixGraph::addEdge(int v1, int v2) {
    // call the addEdge function with a weight of 1
    addEdge(v1, v2, 1);
}

// removeEdge function
// v1: the first vertex
// v2: the second vertex
// used to remove an edge between two vertices
void MatrixGraph::removeEdge(int v1, int v2) {
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        // remove the edge from the adjacency matrix
        adjacencyMatrix[v1][v2] = 0;
        // if the graph is undirected, remove the edge in the opposite direction
        if (!isDirected) {
            // remove the edge from the adjacency matrix
            adjacencyMatrix[v2][v1] = 0;
        }
    }
}

// adjacent function
// v1: the first vertex
// v2: the second vertex
// used to check if two vertices are adjacent
// returns true if the edge exists, false otherwise
bool MatrixGraph::adjacent(int v1, int v2) {
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        // return whether the edge exists
        return adjacencyMatrix[v1][v2] != 0;
    }
    // return false if the vertices are invalid
    return false;
}

// getEdgeWeight function
// v1: the first vertex
// v2: the second vertex
// used to get the weight of the edge between two vertices
// returns the weight of the edge if it exists
// not used in the current implementation
float MatrixGraph::getEdgeWeight(int v1, int v2) {
    // check if the vertices are invalid
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
        // throw an error if the vertices are invalid
        throw std::runtime_error("Invalid vertex numbers");
    }

    // check if the edge does not exist
    if (adjacencyMatrix[v1][v2] == 0) {
        // throw an error if the edge does not exist
        throw std::runtime_error("Edge does not exist");
    }

    // return the weight of the edge
    return adjacencyMatrix[v1][v2];
}

// setEdgeWeight function
// v1: the first vertex
// v2: the second vertex
// weight: the new weight of the edge
// used to set the weight of the edge between two vertices to a new value
// not used in the current implementation
void MatrixGraph::setEdgeWeight(int v1, int v2, float weight) {
    // check if the vertices are valid
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        // set the weight of the edge if it exists
        adjacencyMatrix[v1][v2] = weight;
        // if the graph is undirected, set the weight in the opposite direction
        if (!isDirected) {
            // set the weight of the edge
            adjacencyMatrix[v2][v1] = weight;
        }
    }
}

// toString function
// used to return a string representation of the graph
std::string MatrixGraph::toString() {
    // create a string stream to store the string representation
    std::stringstream ss;

    // iterate through the vertices
    for (int i = 0; i < numVertices; i++) {
        // add the vertex number to the string stream
        ss << "[" << std::setw(2) << i + 1 << "]:";
        // iterate through the neighbors of the vertex
        for (int j = 0; j < numVertices; j++) {
            // check if the edge exists
            if (adjacencyMatrix[i][j] != 0) {
                // add the neighbor to the string stream with the weight of the edge
                ss << "-->";
                ss << "[" << std::setw(2) << i + 1 << "," << std::setw(2) << j + 1 << "::"
                   << std::right << std::setw(6) << std::setfill(' ') << std::fixed << std::setprecision(2)
                   << adjacencyMatrix[i][j] << "]";
            }
        }
        // add a new line character to the string stream
        ss << std::endl;
    }
    // return the string representation
    return ss.str();
}

// working perfectly, formatting is correct
void MatrixGraph::printRaw() {
    // print the adjacency matrix
    std::cout << "Adjacency Matrix:" << std::endl
              << std::endl;

    // iterate through the vertices
    for (int i = 0; i < numVertices; i++) {
        // iterate through the neighbors of the vertex
        for (int j = 0; j < numVertices; j++) {
            // print the weight of the edge
            std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                      << adjacencyMatrix[i][j];
        }
        // print a new line character
        std::cout << std::endl;
    }
}

// pathExists function to check if a path exists between two vertices using BFS
bool MatrixGraph::pathExists(int v1, int v2) {
    // check if the vertices are valid, return false if they are not
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
        // return false if the vertices are invalid
        return false;
    }

    // create a dynamic array to store whether each vertex has been visited
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }

    // create a queue to perform BFS
    Queue<int> queue;

    // mark the starting vertex as visited and enqueue it
    visited[v1] = true;
    queue.enqueue(v1);

    // perform BFS until the queue is empty
    while (!queue.isEmpty()) {
        // dequeue a vertex from the queue
        int current = queue.dequeue();

        // check if the current vertex is the destination vertex, return true if it is
        if (current == v2) {
            delete[] visited;
            return true;
        }

        // iterate through the neighbors of the current vertex
        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            // check if the neighbor is connected to the current vertex and has not been visited
            if (adjacencyMatrix[current][neighbor] != 0 && !visited[neighbor]) {
                // mark the neighbor as visited and enqueue it
                visited[neighbor] = true;
                queue.enqueue(neighbor);
            }
        }
    }

    delete[] visited;
    // return false if the destination vertex is not reachable
    return false;
}

// getBFSPath Function
// v1: the starting vertex
// v2: the destination vertex
// used to get the path between two vertices using BFS
// returns a vector containing the path from the starting vertex to the destination vertex
std::vector<int> MatrixGraph::getBFSPath(int v1, int v2) {
    // check if the vertices are valid
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
        // return an empty vector if the vertices are invalid
        return {};
    }

    // create a vector to store whether each vertex has been visited
    bool *visited = new bool[numVertices];
    // create an array to store the parent of each vertex
    int *parent = new int[numVertices];
    // create a queue to perform BFS
    int *queue = new int[numVertices];
    // initialize the front and back of the queue
    int front = 0, back = 0;

    // initialize the visited and parent arrays
    for (int i = 0; i < numVertices; ++i) {
        // mark the vertex as not visited
        visited[i] = false;
        // set the parent to -1
        parent[i] = -1;
    }

    // mark the starting vertex as visited
    visited[v1] = true;
    // enqueue the starting vertex
    queue[back++] = v1;

    // perform BFS until the queue is empty or the destination vertex is reached
    while (front != back) {
        // dequeue a vertex from the queue
        int current = queue[front++];

        // check if the destination vertex is reached
        if (current == v2) {
            // break if the destination vertex is reached
            // as we only need to find the path to the destination
            break;
        }

        // iterate through the neighbors of the current vertex
        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            // check if the neighbor is connected to the current vertex and has not been visited
            if (adjacencyMatrix[current][neighbor] != 0 && !visited[neighbor]) {
                // mark the neighbor as visited
                visited[neighbor] = true;
                // set its parent
                parent[neighbor] = current;
                // enqueue it
                queue[back++] = neighbor;
            }
        }
    }

    // create a vector to store the path from the starting vertex to the destination vertex
    std::vector<int> path;

    // check if the destination vertex is reachable
    if (visited[v2]) {
        // backtrack from the destination vertex to the starting vertex
        int current = v2;
        // add the destination vertex to the path
        while (current != v1) {
            // add the current vertex to the path
            path.push_back(current);
            // move to the parent of the current vertex
            current = parent[current];
        }
        // add the starting vertex to the path
        path.push_back(v1);
        // reverse the path to get the correct order
        std::reverse(path.begin(), path.end());
    }

    // delete the dynamically allocated arrays
    delete[] visited;
    delete[] parent;
    delete[] queue;

    // return the path from the starting vertex to the destination vertex
    return path;
}

std::vector<int> MatrixGraph::getDijkstraPath(int start, int goal) {
    int numNodes = numVertices;
    MinHeap<std::pair < float, int>> heap(numNodes);
    float *shortestDistance = new float[numNodes];
    int *previousNode = new int[numNodes];

    for (int i = 0; i < numNodes; ++i) {
        shortestDistance[i] = std::numeric_limits<float>::max();
        previousNode[i] = -1;
    }

    shortestDistance[start] = 0;
    heap.enqueue({0, start});

    while (!heap.isEmpty()) {
        int closestNode = heap.peek().second;
        heap.dequeue();

        for (int neighbor = 0; neighbor < numNodes; ++neighbor) {
            if (adjacencyMatrix[closestNode][neighbor] != 0) {
                float tentativeDistance = shortestDistance[closestNode] + adjacencyMatrix[closestNode][neighbor];
                if (tentativeDistance < shortestDistance[neighbor]) {
                    shortestDistance[neighbor] = tentativeDistance;
                    previousNode[neighbor] = closestNode;
                    heap.enqueue({tentativeDistance, neighbor});
                }
            }
        }
    }

    std::vector<int> shortestPath;
    // Check if a path exists
    if (previousNode[goal] != -1) {
        for (int at = goal; at != -1; at = previousNode[at]) {
            shortestPath.push_back(at);
        }
        std::reverse(shortestPath.begin(), shortestPath.end());
    }

    delete[] shortestDistance;
    delete[] previousNode;

    return shortestPath;
}

std::vector <std::vector<int>> MatrixGraph::getDijkstraAll(int start) {
    int numNodes = numVertices;
    MinHeap<std::pair < float, int>>
    heap(numNodes);
    float *shortestDistance = new float[numNodes];
    int *previousNode = new int[numNodes];
    std::vector <std::vector<int>> allPaths(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        shortestDistance[i] = std::numeric_limits<float>::max();
        previousNode[i] = -1;
    }

    shortestDistance[start] = 0;
    heap.enqueue({0, start});

    while (!heap.isEmpty()) {
        int closestNode = heap.peek().second;
        heap.dequeue();

        for (int neighbor = 0; neighbor < numNodes; ++neighbor) {
            if (adjacencyMatrix[closestNode][neighbor] != 0) {
                float tentativeDistance = shortestDistance[closestNode] + adjacencyMatrix[closestNode][neighbor];
                if (tentativeDistance < shortestDistance[neighbor]) {
                    shortestDistance[neighbor] = tentativeDistance;
                    previousNode[neighbor] = closestNode;
                    heap.enqueue({tentativeDistance, neighbor});
                }
            }
        }
    }

    for (int endNode = 0; endNode < numNodes; ++endNode) {
        if (shortestDistance[endNode] != std::numeric_limits<float>::max()) {
            for (int at = endNode; at != -1; at = previousNode[at]) {
                allPaths[endNode].push_back(at);
            }
            std::reverse(allPaths[endNode].begin(), allPaths[endNode].end());
        }
    }

    delete[] shortestDistance;
    delete[] previousNode;

    return allPaths;
}

// initializeMatrix function
// used to initialize the adjacency matrix
// creates a 2D array to store the adjacency matrix
// initializes the values to 0
void MatrixGraph::initializeMatrix() {
    // create a 2D array to store the adjacency matrix
    adjacencyMatrix = new float *[numVertices];
    // iterate through the vertices
    for (int i = 0; i < numVertices; i++) {
        // create an array to store the neighbors of the vertex
        adjacencyMatrix[i] = new float[numVertices]();
    }
}

// deleteMatrix function
// used to delete the adjacency matrix
// deletes the 2D array storing the adjacency matrix
void MatrixGraph::deleteMatrix() {
    // iterate through the vertices
    for (int i = 0; i < numVertices; i++) {
        // delete the array of neighbors
        delete[] adjacencyMatrix[i];
    }

    // delete the array of vertices
    delete[] adjacencyMatrix;
}
