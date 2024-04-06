// Import necessary libraries
#include "MatrixGraph_chauhan.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// Function to print the menu
void printMenu()
{
    // provide the user with the options
    std::cout << "Welcome to the Graph tester!" << std::endl;
    std::cout << "1) Print the graph" << std::endl;
    std::cout << "2) Find a path" << std::endl;
    std::cout << "3) Start a file" << std::endl;
    std::cout << "4) Add a path to the file" << std::endl;
    std::cout << "0) Quit" << std::endl;
}

// Main function
int main(int argc, char *argv[])
{
    // Check if the user has provided the correct number of arguments
    // if it is less than 3, then print the usage and return 1
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " {-u|-w} <file> [-ud]" << std::endl;
        return 1;
    }

    // Read the flag and filename from the command line arguments
    std::string flag = argv[1];
    std::string filename = argv[2];
    bool isUndirected = (argc > 3 && std::string(argv[3]) == "-ud"); // Check if the graph is undirected

    // Open the file
    std::ifstream infile(filename);
    if (!infile)
    {
        // If the file cannot be opened, print an error message and return 1
        std::cout << "Error opening file: " << filename << std::endl;
        return 1;
    }

    // Read the number of vertices and edges from the file
    int numVertices, numEdges;
    // Read the first line of the file into numVertices and numEdges
    infile >> numVertices >> numEdges;

    // Create a graph object named graph
    MatrixGraph graph(numVertices, !isUndirected);

    // if the flag is -u, then read the edges from the file and add them to the graph
    if (flag == "-u")
    {
        // Read the edges from the file and add them to the graph
        int v1, v2;
        // Read the edges from the file and add them to the graph
        while (infile >> v1 >> v2)
        {
            // Add the edge to the graph
            graph.addEdge(v1-1, v2-1);
        }
    }
        // else if the flag is -w, then read the edges and weights from the file and add them to the graph
    else if (flag == "-w")
    {
        // Read the edges and weights from the file and add them to the graph
        int v1, v2;
        // Read the edges and weights from the file and add them to the graph
        float weight;
        // Read the edges and weights from the file and add them to the graph
        while (infile >> v1 >> v2 >> weight)
        {
            // Add the edge to the graph
            graph.addEdge(v1-1, v2-1, weight);
        }
    }
    else
        // else print an error message and return 1
    {
        std::cout << "Invalid flag: " << flag << std::endl;
        return 1;
    }

    // Close the file
    infile.close();

    int choice;                 // user input
    std::string outputFilename; // output file name
    std::ofstream outfile;      // output file

    do
    {
        // Print the menu
        printMenu();
        // Get the user's choice
        // std::cout << "Enter your choice: ";
        // Read the user's choice
        std::cin >> choice;

        // Perform the action based on the user's choice
        switch (choice)
        {
            // for case 1, print the graph
            case 1:
                std::cout << graph.toString();
                break;
                // for case 2, find a path
            case 2:
            {
                // Get the starting and goal vertices from the user
                int v1, v2;
                std::cin >> v1; // Read the starting vertex
                std::cin >> v2; // Read the goal vertex
                v1--;
                v2--;

                // Check if a path exists between the starting and goal vertices
                if (!graph.pathExists(v1, v2))
                {
                    // If no path exists, print an error message
                    std::cout << "No path from " << v1+1 << " to " << v2+1 << ".";
                }

                // If a path exists, find the path and print it
                std::vector<int> path = graph.getBFSPath(v1, v2);
                // Print the path
                float cumulativeWeight = 0; // Initialize cumulative weight
                for (size_t i = 0; i < path.size(); ++i)
                {
                    // Add the weight of the current edge to the cumulative weight
                    if (i != 0) {
                        cumulativeWeight += graph.getEdgeWeight(path[i - 1], path[i]);
                    }
                    // print the vertex and the cumulative weight
                    std::cout << "[" << std::setw(2) << path[i] + 1 << ":"
                              << std::setw(6) << std::fixed << std::setprecision(2)
                              << cumulativeWeight << "]";
                    // if the vertex is not the last vertex in the path, print ==>
                    if (i < path.size() - 1)
                    {
                        std::cout << "==>";
                    }
                }
                std::cout << std::endl;
                break;
            }
                // for case 3, start a file
            case 3:
                std::cin >> outputFilename;                 // Read the output filename
                outfile.open(outputFilename);               // Open the output file
                if (!outfile)                               // If the output file cannot be opened, print an error message
                {
                    // Print an error message
                    std::cout << "Error creating file: " << outputFilename << std::endl;
                }
                else
                {
                    // Print a message that the file has been created
                    outfile << numVertices << " " << numEdges << std::endl;
                    // use a loop to print the edges
                    for (int i = 0; i < numVertices; ++i)
                    {
                        // use another loop to print the edges
                        for (int j = i+1; j < numVertices; ++j) // Start from i+1 to only consider the upper triangular part
                        {
                            // if the vertices are adjacent, print the edge
                            if (graph.adjacent(i, j))
                            {
                                // print the edge
                                outfile << i+1 << " " << j+1;
                                // if the flag is -w, print the weight of the edge
                                if (flag == "-w")
                                {
                                    // print the weight of the edge
                                    outfile << " " << std::to_string(graph.getEdgeWeight(i, j));
                                }
                                // print a new line
                                outfile << std::endl;
                            }
                        }
                    }
                }
                // break out of the switch statement
                break;
                // for case 4, add a path to the file
                // for case 4, add a path to the file
            case 4:
                // if the output file is not open, print an error message
                if (!outfile.is_open())
                {
                    // Print an error message
                    std::cout << "No file has been created yet." << std::endl;
                }
                else
                {
                    // Get the starting and goal vertices from the user
                    int v1, v2;
                    std::cin >> v1;                             // Read the starting vertex
                    std::cin >> v2;                             // Read the goal vertex
                    if (graph.pathExists(v1, v2))               // Check if a path exists between the starting and goal vertices
                    {
                        // If a path exists, find the path and print it
                        std::vector<int> path = graph.getBFSPath(v1, v2);
                        // use a loop to print the path
                        for (size_t i = 0; i < path.size(); ++i)
                        {
                            // print the vertex and the weight of the edge
                            outfile << "[" << std::setw(2) << path[i]+1 << ":"
                                    << std::setw(6) << std::fixed << std::setprecision(2)
                                    << (i == 0 ? 0 : graph.getEdgeWeight(path[i - 1], path[i])) << "]";
                            // if the vertex is not the last vertex in the path, print ==>
                            if (i < path.size() - 1)
                            {
                                outfile << "==>";
                            }
                        }
                        // print a new line
                        outfile << std::endl;
                    }
                }
                // break out of the switch statement
                break;
                // hidden code 9999 ;)
                // it prints the raw graph
            case 9999:
                graph.printRaw();
                break; // break out of the switch statement
                // for case 0, exit the program
            case 0:
                outfile.close(); // Close the output file
                break;
                // for default, print an error message
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0); // Repeat the loop until the user chooses to exit

    // Return 0 to indicate successful completion
    return 0;
}
