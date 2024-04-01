#include "MatrixGraph_chauhan.h"
#include "Queue_chauhan.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

MatrixGraph::MatrixGraph(int numVertices, bool isDirected)
{
    this->numVertices = numVertices;
    this->isDirected = isDirected;
    initializeMatrix();
}

MatrixGraph::~MatrixGraph()
{
    deleteMatrix();
}

void MatrixGraph::addEdge(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        adjacencyMatrix[v1][v2] = 1;
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = 1;
        }
    }
}

void MatrixGraph::addEdge(int v1, int v2, float weight)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        adjacencyMatrix[v1][v2] = weight;
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = weight;
        }
    }
}

void MatrixGraph::removeEdge(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        adjacencyMatrix[v1][v2] = 0;
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = 0;
        }
    }
}

bool MatrixGraph::adjacent(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        return adjacencyMatrix[v1][v2] != 0;
    }
    return false;
}

float MatrixGraph::getEdgeWeight(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        if (adjacencyMatrix[v1][v2] != 0)
        {
            return adjacencyMatrix[v1][v2];
        }
        else
        {
            throw std::runtime_error("Edge does not exist");
        }
    }
    throw std::runtime_error("Invalid vertex numbers");
}

void MatrixGraph::setEdgeWeight(int v1, int v2, float weight)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        adjacencyMatrix[v1][v2] = weight;
        if (!isDirected)
        {
            adjacencyMatrix[v2][v1] = weight;
        }
    }
}

std::string MatrixGraph::toString()
{
    std::stringstream ss;
    for (int i = 0; i < numVertices; i++)
    {
        ss << "[" << std::setw(2) << i << "]:";
        for (int j = 0; j < numVertices; j++)
        {
            if (adjacencyMatrix[i][j] != 0)
            {
                ss << "-->[" << std::setw(2) << j << "," << std::setw(5)
                   << std::fixed << std::setprecision(2) << adjacencyMatrix[i][j] << "]";
            }
        }
        ss << std::endl;
    }
    return ss.str();
}

void MatrixGraph::printRaw()
{
    std::cout << "Adjacency Matrix:" << std::endl;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            std::cout << std::setw(5) << std::fixed << std::setprecision(2)
                      << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool MatrixGraph::pathExists(int v1, int v2)
{
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
    {
        return false;
    }

    std::vector<bool> visited(numVertices, false);
    Queue<int> queue;

    visited[v1] = true;
    queue.enqueue(v1);

    while (!queue.isEmpty())
    {
        int current = queue.dequeue();

        if (current == v2)
        {
            return true;
        }

        for (int neighbor = 0; neighbor < numVertices; ++neighbor)
        {
            if (adjacencyMatrix[current][neighbor] != 0 && !visited[neighbor])
            {
                visited[neighbor] = true;
                queue.enqueue(neighbor);
            }
        }
    }

    return false;
}

std::vector<int> MatrixGraph::getBFSPath(int v1, int v2)
{
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
    {
        return std::vector<int>();
    }

    std::vector<bool> visited(numVertices, false);
    std::vector<int> parent(numVertices, -1);
    Queue<int> queue;

    visited[v1] = true;
    queue.enqueue(v1);

    while (!queue.isEmpty())
    {
        int current = queue.dequeue();

        if (current == v2)
        {
            break;
        }

        for (int neighbor = 0; neighbor < numVertices; ++neighbor)
        {
            if (adjacencyMatrix[current][neighbor] != 0 && !visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = current;
                queue.enqueue(neighbor);
            }
        }
    }

    std::vector<int> path;
    if (visited[v2])
    {
        int current = v2;
        while (current != -1)
        {
            path.push_back(current);
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}

void MatrixGraph::initializeMatrix()
{
    adjacencyMatrix = new float *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adjacencyMatrix[i] = new float[numVertices]();
    }
}

void MatrixGraph::deleteMatrix()
{
    for (int i = 0; i < numVertices; i++)
    {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}