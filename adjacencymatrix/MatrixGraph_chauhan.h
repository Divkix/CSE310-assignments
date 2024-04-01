#ifndef MATRIXGRAPH_CHAUHAN_H
#define MATRIXGRAPH_CHAUHAN_H

#include <string>
#include <vector>

class MatrixGraph
{
private:
    int numVertices;
    bool isDirected;
    float **adjacencyMatrix;

public:
    MatrixGraph(int numVertices, bool isDirected);
    ~MatrixGraph();

    void addEdge(int v1, int v2);
    void addEdge(int v1, int v2, float weight);
    void removeEdge(int v1, int v2);
    bool adjacent(int v1, int v2);
    float getEdgeWeight(int v1, int v2);
    void setEdgeWeight(int v1, int v2, float weight);
    std::string toString();
    void printRaw();
    bool pathExists(int v1, int v2);
    std::vector<int> getBFSPath(int v1, int v2);

private:
    void initializeMatrix();
    void deleteMatrix();
};

#endif // MATRIXGRAPH_CHAUHAN_H