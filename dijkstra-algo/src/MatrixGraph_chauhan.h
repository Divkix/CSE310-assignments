//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 4/16/2024
//
// Description: This file contains the declaration of the class MatrixGraph.
//              The class has been implemented to represent a graph using an adjacency matrix.
//              The class has been implemented to support both directed and undirected graphs.
//              The class has been implemented to support the following operations:
//              1. Add an edge between two vertices
//              2. Remove an edge between two vertices
//              3. Check if two vertices are adjacent
//              4. Get the weight of the edge between two vertices
//              5. Set the weight of the edge between two vertices to a new value
//              6. Print the raw adjacency matrix
//              7. Return a string representation of the graph
//              8. Check if a path exists between two vertices
//              9. Get the path between two vertices using BFS
//

#ifndef MATRIXGRAPH_CHAUHAN_H
#define MATRIXGRAPH_CHAUHAN_H

// import necessary libraries
#include <string>
#include <vector>

// define the class MatrixGraph
class MatrixGraph {
    // define the private members of the class
private:
    int numVertices;           // number of vertices in the graph
    bool isDirected;           // boolean to check if the graph is directed or not
    float **adjacencyMatrix{}; // 2D array to store the adjacency matrix
    void initializeMatrix();   // initialize the adjacency matrix
    void deleteMatrix();       // delete the adjacency matrix

    // define the public members of the class
public:
    MatrixGraph(int numVertices, bool isDirected); // constructor
    ~MatrixGraph();                                // destructor

    void addEdge(int v1, int v2);                     // add an edge between two vertices
    void addEdge(int v1, int v2, float weight);       // add an edge between two vertices with a weight
    void removeEdge(int v1, int v2);                  // remove an edge between two vertices
    bool adjacent(int v1, int v2);                    // check if two vertices are adjacent
    float getEdgeWeight(int v1, int v2);              // get the weight of the edge between two vertices
    void setEdgeWeight(int v1, int v2, float weight); // set the weight of the edge between two vertices to a new value
    void printRaw();                                  // print the raw adjacency matrix

    // the three functions which took a lot of brain power to implement
    std::string toString();                      // return a string representation of the graph
    bool pathExists(int v1, int v2);             // check if a path exists between two vertices
    std::vector<int> getBFSPath(int v1, int v2); // get the path between two vertices using BFS

    // additions for dijkstra's algorithm
    std::vector<int> getDijkstraPath(int, int);        // get the path between two vertices using Dijkstra's algorithm
    std::vector<std::vector<int>> getDijkstraAll(int); // get the shortest path from a single vertex to all other vertices
};

#endif // MATRIXGRAPH_CHAUHAN_H
