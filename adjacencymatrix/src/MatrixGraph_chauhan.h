#ifndef MATRIXGRAPH_CHAUHAN_H
#define MATRIXGRAPH_CHAUHAN_H

#include <string>
#include <vector>

class MatrixGraph
{
private:
    int numVertices;
    bool isDirected;
    std::vector<std::vector<float>> matrix;

public:
    MatrixGraph(int vertices, bool directed);
    MatrixGraph(int numNodes) : matrix(numNodes, std::vector<float>(numNodes, 0.0f)) {}

    void addEdge(int v1, int v2);
    void addEdge(int v1, int v2, float weight);
    void removeEdge(int v1, int v2);
    bool adjacent(int v1, int v2) const;
    float getEdgeWeight(int v1, int v2) const;
    void setEdgeWeight(int v1, int v2, float weight);
    std::string toString() const;
    void printRaw() const;
    bool pathExists(int start, int goal);
    std::vector<int> getBFSPath(int start, int goal);
};

#endif // MATRIXGRAPH_CHAUHAN_H
