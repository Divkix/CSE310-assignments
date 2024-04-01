#include "MatrixGraph_chauhan.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void printMenu()
{
    std::cout << "Welcome to the Graph tester!" << std::endl;
    std::cout << "1) Print the graph" << std::endl;
    std::cout << "2) Find a path" << std::endl;
    std::cout << "3) Start a file" << std::endl;
    std::cout << "4) Add a path to the file" << std::endl;
    std::cout << "0) Quit" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " {-u|-w} <file> [-ud]" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string filename = argv[2];
    bool isUndirected = (argc > 3 && std::string(argv[3]) == "-ud");

    std::ifstream infile(filename);
    if (!infile)
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int numVertices, numEdges;
    infile >> numVertices >> numEdges;

    MatrixGraph graph(numVertices, !isUndirected);

    if (flag == "-u")
    {
        int v1, v2;
        while (infile >> v1 >> v2)
        {
            graph.addEdge(v1, v2);
        }
    }
    else if (flag == "-w")
    {
        int v1, v2;
        float weight;
        while (infile >> v1 >> v2 >> weight)
        {
            graph.addEdge(v1, v2, weight);
        }
    }
    else
    {
        std::cout << "Invalid flag: " << flag << std::endl;
        return 1;
    }

    infile.close();

    int choice;
    std::string outputFilename;
    std::ofstream outfile;

    do
    {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << graph.toString() << std::endl;
            break;
        case 2:
        {
            int v1, v2;
            std::cout << "Enter the starting vertex: ";
            std::cin >> v1;
            std::cout << "Enter the goal vertex: ";
            std::cin >> v2;
            if (graph.pathExists(v1, v2))
            {
                std::vector<int> path = graph.getBFSPath(v1, v2);
                std::cout << "Path from " << v1 << " to " << v2 << " is:" << std::endl;
                for (size_t i = 0; i < path.size(); ++i)
                {
                    std::cout << "[" << std::setw(2) << path[i] << ":"
                              << std::setw(5) << std::fixed << std::setprecision(2)
                              << (i == 0 ? 0 : graph.getEdgeWeight(path[i - 1], path[i])) << "]";
                    if (i < path.size() - 1)
                    {
                        std::cout << "==>";
                    }
                }
                std::cout << std::endl;
            }
            else
            {
                std::cout << "No path from " << v1 << " to " << v2 << std::endl;
            }
            break;
        }
        case 3:
            std::cout << "Enter the output filename: ";
            std::cin >> outputFilename;
            outfile.open(outputFilename);
            if (!outfile)
            {
                std::cout << "Error creating file: " << outputFilename << std::endl;
            }
            else
            {
                outfile << numVertices << " " << numEdges << std::endl;
                for (int i = 0; i < numVertices; ++i)
                {
                    for (int j = 0; j < numVertices; ++j)
                    {
                        if (graph.adjacent(i, j))
                        {
                            outfile << i << " " << j;
                            if (flag == "-w")
                            {
                                outfile << " " << graph.getEdgeWeight(i, j);
                            }
                            outfile << std::endl;
                        }
                    }
                }
                outfile.close();
                std::cout << "Graph saved to file: " << outputFilename << std::endl;
            }
            break;
        case 4:
            if (!outfile.is_open())
            {
                std::cout << "No file has been created yet." << std::endl;
            }
            else
            {
                int v1, v2;
                std::cout << "Enter the starting vertex: ";
                std::cin >> v1;
                std::cout << "Enter the goal vertex: ";
                std::cin >> v2;
                if (graph.pathExists(v1, v2))
                {
                    std::vector<int> path = graph.getBFSPath(v1, v2);
                    outfile << "Path from " << v1 << " to " << v2 << " is:" << std::endl;
                    for (size_t i = 0; i < path.size(); ++i)
                    {
                        outfile << "[" << std::setw(2) << path[i] << ":"
                                << std::setw(5) << std::fixed << std::setprecision(2)
                                << (i == 0 ? 0 : graph.getEdgeWeight(path[i - 1], path[i])) << "]";
                        if (i < path.size() - 1)
                        {
                            outfile << "==>";
                        }
                    }
                    outfile << std::endl;
                }
                else
                {
                    outfile << "No path from " << v1 << " to " << v2 << std::endl;
                }
            }
            break;
        case 9999:
            graph.printRaw();
            break;
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}