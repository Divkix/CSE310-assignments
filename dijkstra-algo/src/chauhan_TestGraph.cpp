//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 4/16/2024
//
// Description: This file contains the main function to test the MatrixGraph class.
//              The program reads a graph from a file and provides the user with a menu to perform
//              various operations on the graph. The user can print the graph, find a path between
//              two vertices, save the graph to a file, and add a path to the file. The program
//              uses the BFS algorithm to find the path between two vertices.
//              The enhancements in this version are:
//              1. The program can now perform Dijkstra's algorithm to find the shortest path between two vertices.
//              2. The program can now save all Dijkstra paths from a starting vertex to a file.
//              3. The program can now save the Dijkstra path to a file.
//

// Import necessary libraries
#include "MatrixGraph_chauhan.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// Function to print the menu
void printMenu()
{
    std::cout << "Welcome to the Graph tester!"
              << std::endl;
    std::cout << "1) Print the graph"
              << std::endl;
    std::cout << "2) Find a BFS path"
              << std::endl;
    std::cout << "3) Find a Single Dijkstra Path"
              << std::endl;
    std::cout << "4) Find all Dijkstra Paths from a start"
              << std::endl;
    std::cout << "5) Start a file"
              << std::endl;
    std::cout << "6) Add a BFS path to the file"
              << std::endl;
    std::cout << "7) Add single Dijkstra Path to file"
              << std::endl;
    std::cout << "8) Add all Dijkstra Paths from a start"
              << std::endl;
    std::cout << "0) Quit"
              << std::endl;
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
    bool isUndirected = (argc > 3 && std::string(argv[3]) ==
                                         "-ud"); // Check if the graph is undirected or not based on if '-ud' is provided

    // Open the file to read the graph
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

    // Check if the flag is valid or not
    if (flag != "-u" && flag != "-w")
    {
        std::cout << "Invalid flag: " << flag << std::endl;
        return 1;
    }

    // if the flag is -u, then read the edges from the file and add them to the graph
    if (flag == "-u")
    {
        // Read the edges from the file and add them to the graph
        int v1, v2;
        // Read the edges from the file and add them to the graph
        while (infile >> v1 >> v2)
        {
            // Add the edge to the graph
            graph.addEdge(v1 - 1, v2 - 1); // we have to subtract 1 from the vertices to make them 0-based
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
            graph.addEdge(v1 - 1, v2 - 1, weight); // we have to subtract 1 from the vertices to make them 0-based
        }
    }

    // Close the input file
    infile.close();

    // Initialize the variables
    int choice;                 // user input for the menu choice
    std::string outputFilename; // output file name for writing the paths
    std::ofstream outfile;      // output file stream for writing the paths

    // using a while loop to display the menu and get the user's choice
    do
    {
        // Print the menu
        printMenu();
        // Read the user's choice
        std::cin >> choice;

        // Perform the action based on the user's choice
        switch (choice)
        {
        // for case 1, print the graph
        case 1:
        {
            // using the toString function to print the graph
            std::cout << graph.toString();
            break; // break out of the switch statement
        }
            // for case 2, find a BFS path
        case 2:
        {
            // Get the starting and goal vertices from the user
            int v1, v2;
            std::cin >> v1; // Read the starting vertex
            std::cin >> v2; // Read the goal vertex
            v1--;           // Subtract 1 to make the vertices 0-based
            v2--;           // Subtract 1 to make the vertices 0-based

            // Check if a path exists between the starting and goal vertices
            if (!graph.pathExists(v1, v2))
            {
                // If no path exists, print an error message
                std::cout << "No BFS path from " << v1 + 1 << " to " << v2 + 1 << "." << std::endl;
                break;
            }

            // If a path exists, find the path and print it
            std::vector<int> path = graph.getBFSPath(v1, v2);

            // Initialize cumulative weight
            float cumulativeWeight = 0;

            std::cout << "BFS path from " << v1 + 1 << " to " << v2 + 1 << " is:" << std::endl;

            // use a loop to print the path
            for (size_t i = 0; i < path.size(); ++i)
            {
                // Add the weight of the current edge to the cumulative weight if the vertex is not the starting vertex
                if (i != 0)
                {
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
            // print a new line
            std::cout << std::endl;
            break;
        }
            // for part 3, find a single Dijkstra path
        case 3:
        {
            // Get the starting and goal vertices from the user
            int v1, v2;
            std::cin >> v1 >> v2;
            v1--;
            v2--;

            // Find the Dijkstra path
            std::vector<int> path = graph.getDijkstraPath(v1, v2);

            // If no path exists, print an error message
            if (path.empty())
            {
                std::cout << "No DIJKSTRA path from " << v1 + 1 << " to " << v2 + 1 << "." << std::endl;
            }
            else
            {
                // Initialize cumulative weight
                float cumulativeWeight = 0;

                // Print the path
                std::cout << "DIJKSTRA path from " << v1 + 1 << " to " << v2 + 1 << " is:" << std::endl;
                for (int i = 0; i < path.size(); ++i)
                {
                    // Add the weight of the current edge to the cumulative weight if the vertex is not the starting vertex
                    if (i != 0)
                    {
                        if (graph.adjacent(path[i - 1], path[i]))
                        // if edge exists, add the weight of the edge to the cumulative weight
                        {
                            cumulativeWeight += graph.getEdgeWeight(path[i - 1], path[i]);
                        }
                        else
                        // If the edge does not exist, print an error message and break
                        {
                            std::cout << "Edge does not exist between " << path[i - 1] + 1 << " and " << path[i] + 1
                                      << std::endl;
                            break;
                        }
                    }
                    // print the vertex and the cumulative weight
                    std::cout << "[" << std::setw(2) << path[i] + 1 << ":" << std::setw(6) << std::fixed
                              << std::setprecision(2) << cumulativeWeight << "]";
                    // if the vertex is not the last vertex in the path, print ==>
                    if (i < path.size() - 1)
                    {
                        // print ==> in between the vertices
                        std::cout << "==>";
                    }
                }
                // print a new line
                std::cout << std::endl;
            }
            break;
        }
            // for case 4, find all Dijkstra paths from a start
        case 4:
        {
            // Get the starting vertex from the user
            int v1;
            std::cin >> v1;
            v1--;

            // Find all Dijkstra paths
            std::vector<std::vector<int>> allPaths = graph.getDijkstraAll(v1);

            // Print all paths
            for (int i = 0; i < allPaths.size(); ++i)
            {
                // Skip if the starting vertex and the destination vertex are the same
                if (i == v1)
                {
                    // Print the starting vertex
                    std::cout << "DIJKSTRA Paths start at Vertex " << v1 + 1 << std::endl;
                    continue;
                }

                if (allPaths[i].empty())
                // if no path exists, print an error message
                {
                    std::cout << "Path to " << i + 1 << ": "
                              << "No DIJKSTRA path from " << v1 + 1 << " to "
                              << i + 1 << std::endl;
                }
                else
                // if a path exists, print the path
                {
                    // Initialize cumulative weight
                    float cumulativeWeight = 0;
                    // Print the path
                    std::cout << "Path to " << i + 1 << ": ";
                    for (int j = 0; j < allPaths[i].size(); ++j)
                    {
                        // Add the weight of the current edge to the cumulative weight if the vertex is not the starting vertex
                        if (j != 0)
                        {
                            cumulativeWeight += graph.getEdgeWeight(allPaths[i][j - 1], allPaths[i][j]);
                        }
                        // print the vertex and the cumulative weight
                        std::cout << "[" << std::setw(2) << allPaths[i][j] + 1 << ":" << std::setw(6) << std::fixed
                                  << std::setprecision(2) << cumulativeWeight << "]";
                        // if the vertex is not the last vertex in the path, print ==>
                        if (j < allPaths[i].size() - 1)
                        {
                            // print ==> in between the vertices
                            std::cout << "==>";
                        }
                    }
                    // print a new line
                    std::cout << std::endl;
                }
            }
            break;
        }
            // for case 5, start a file
        case 5:
        {
            // Read the output filename
            std::cin >> outputFilename;
            // Open the output file
            outfile.open(outputFilename);

            // If the output file cannot be opened, print an error message
            if (!outfile)
            {
                // Print an error message
                std::cout << "Error creating file: " << outputFilename << std::endl;
                break;
            }

            // initialize a new variable to store the number of edges,
            // as the actual number of edges is different from the number
            // of edges read from the file, we have to traverse the entire
            // adjacency matrix to get the actual number of edges
            numEdges = 0;
            // looping through the adjacency matrix to count the number of edges
            for (int i = 0; i < numVertices; ++i)
            {
                // loop through the adjacency matrix
                for (int j = 0; j < numVertices; ++j)
                {
                    // check if the vertices are adjacent
                    if (graph.adjacent(i, j))
                    {
                        // increment the number of edges
                        ++numEdges;
                    }
                }
            }

            // save the number of vertices and edges to the file
            outfile << numVertices << " " << numEdges << std::endl;

            // now we have to print the edges to the file
            // use a loop to print the edges
            for (int i = 0; i < numVertices; ++i)
            {
                // use another loop to print the edges
                for (int j = 0; j < numVertices; ++j) // Start from 0 to consider all edges
                {
                    // if the vertices are adjacent, print the edge
                    if (graph.adjacent(i, j))
                    {
                        // print the edge
                        outfile << i + 1 << " " << j + 1;

                        // if the flag is -w, print the weight of the edge as wells
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
            // break out of the switch statement
            break;
        }
            // for case 6, add a path to the file for BFS path
        case 6:
        {
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
                std::cin >> v1; // Read the starting vertex
                std::cin >> v2; // Read the goal vertex
                v1--;
                v2--;

                // Check if a path exists between the starting and goal vertices
                if (!graph.pathExists(v1, v2))
                {
                    // If no path exists, print an error message
                    outfile << "No path from " << v1 + 1 << " to " << v2 + 1 << ".";
                }

                // If a path exists, find the path and print it
                std::vector<int> path = graph.getBFSPath(v1, v2);
                // use a loop to print the path
                float cumulativeWeight = 0.0; // Initialize cumulative weight
                for (size_t i = 0; i < path.size(); ++i)
                {
                    // Add the weight of the current edge to the cumulative weight
                    if (i != 0)
                    {
                        cumulativeWeight += graph.getEdgeWeight(path[i - 1], path[i]);
                    }
                    // print the vertex and the cumulative weight
                    outfile << "[" << std::setw(2) << path[i] + 1 << ":"
                            << std::setw(6) << std::fixed << std::setprecision(2)
                            << cumulativeWeight << "]";
                    // if the vertex is not the last vertex in the path, print ==>
                    if (i < path.size() - 1)
                    {
                        outfile << "==>";
                    }
                }
                // print a new line
                outfile << std::endl;
            }
            // break out of the switch statement
            break;
        }
            // for case 7, add a path to the file for Dijkstra path
        case 7:
        {
            // Get the starting and goal vertices from the user
            int v1, v2;
            std::cin >> v1 >> v2;
            v1--;
            v2--;

            // Find the Dijkstra path
            std::vector<int> path = graph.getDijkstraPath(v1, v2);

            // Write the path to the file
            if (path.empty())
            {
                outfile << "No path found." << std::endl;
            }
            else
            {
                outfile << "Path: ";
                for (int i = 0; i < path.size(); ++i)
                {
                    outfile << path[i] + 1; // Adding 1 to convert from 0-based to 1-based indexing
                    if (i != path.size() - 1)
                    {
                        outfile << " -> ";
                    }
                }
                outfile << std::endl;
            }
            break;
        }
            // for case 8, add all Dijkstra paths from a start to the file
        case 8:
        {
            // Get the starting vertex from the user
            int v1;
            std::cin >> v1;
            v1--;

            // Find all Dijkstra paths
            std::vector<std::vector<int>> allPaths = graph.getDijkstraAll(v1);

            // Write all paths to the file
            for (int i = 0; i < allPaths.size(); ++i)
            {
                outfile << "Path to vertex " << i + 1 << ": ";
                if (allPaths[i].empty())
                {
                    outfile << "No path found." << std::endl;
                }
                else
                {
                    for (int j = 0; j < allPaths[i].size(); ++j)
                    {
                        outfile << allPaths[i][j] + 1; // Adding 1 to convert from 0-based to 1-based indexing
                        if (j != allPaths[i].size() - 1)
                        {
                            outfile << " -> ";
                        }
                    }
                    outfile << std::endl;
                }
            }
            break;
        }
            // hidden code 9999 ;)
            // it prints the raw graph
        case 9999:
            // print the raw graph
            graph.printRaw();
            break; // break out of the switch statement
        case 1111:
            break;
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
