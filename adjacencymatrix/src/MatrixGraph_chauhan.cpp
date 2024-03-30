#include "MatrixGraph_chauhan.h"
#include <iostream>
#include <fstream>
#include <string>

void processFile(const std::string &filename, bool isWeighted, bool isUndirected);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " {-u|-w} <file> [-ud]" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    std::string filename = argv[2];
    bool isWeighted = (option == "-w");
    bool isUndirected = (argc > 3 && std::string(argv[3]) == "-ud");

    processFile(filename, isWeighted, isUndirected);

    return 0;
}

void processFile(const std::string &filename, bool isWeighted, bool isUndirected)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    int numNodes;
    file >> numNodes;

    MatrixGraph graph(numNodes);

    int node1, node2, weight;
    while (file >> node1 >> node2)
    {
        if (isWeighted)
        {
            file >> weight;
        }
        else
        {
            weight = 1;
        }

        graph.addEdge(node1, node2, weight);

        if (isUndirected)
        {
            graph.addEdge(node2, node1, weight);
        }
    }

    file.close();
}