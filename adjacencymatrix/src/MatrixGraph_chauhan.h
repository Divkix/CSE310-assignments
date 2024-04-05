#ifndef MATRIXGRAPH_CHAUHAN_H
#define MATRIXGRAPH_CHAUHAN_H

// import necessary libraries
#include <string>
#include <vector>

// define the class MatrixGraph
class MatrixGraph
{
    // define the private members of the class
private:
    int numVertices;         // number of vertices in the graph
    bool isDirected;         // boolean to check if the graph is directed or not
    float **adjacencyMatrix; // 2D array to store the adjacency matrix
    void initializeMatrix(); // initialize the adjacency matrix
    void deleteMatrix();     // delete the adjacency matrix

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
    bool pathExists(int v1, int v2);                  // check if a path exists between two vertices

    std::string toString();                      // return a string representation of the graph
    std::vector<int> getBFSPath(int v1, int v2); // get the path between two vertices using BFS
};

#endif // MATRIXGRAPH_CHAUHAN_H
