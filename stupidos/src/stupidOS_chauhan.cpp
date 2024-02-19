//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 2/10/2024
//
// Description: This is the main file for the file system simulation. It contains the main function
//              that drives the simulation. The simulation allows the user to interact with the file
//              system by adding, deleting, and outputting files.
// Usage: ./stupidos -s <hard drive size> -f <initial state file>

// Import necessary libraries
#include "FileSystem_chauhan.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

// Utility function to display the menu
void printMenu()
{
    // Display the menu
    std::cout << "Menu:\n"
              << "1 - Show files on hard drive\n"
              << "2 - Add a file\n"
              << "3 - Delete a file\n"
              << "4 - Output a file\n"
              << "0 - Exit simulation\n";
}

// Function to handle the "Show files on hard drive" action
void showFiles(FileManager &fileManager)
{
    // Display the filenames and their sizes
    std::vector<std::string> filenames = fileManager.getFileNames();
    std::cout << std::left << std::setw(40) << "Filename" << std::right << std::setw(15) << "size\n";

    // Loop through the filenames and display their sizes
    // we are using setw to set the width of the output to make it look nice
    for (const auto &filename : filenames)
    {
        std::cout << std::left << std::setw(40) << filename
                  << std::right << std::setw(10) << fileManager.readFileSize(filename) << " blk\n";
    }
}

// Function to handle the "Add a file" action
void addFile(FileManager &fileManager)
{
    // Get the filename and contents from the user
    std::string filename, contents;

    // Check if there's a newline character in the buffer
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(); // Ignore the newline character
    }

    std::cout << "Enter filename: ";
    std::getline(std::cin, filename, ' ');
    std::cout << "Enter content string: ";
    std::getline(std::cin, contents, ' ');

    // NOTE: Added to debug the filename and contents
    // std::cout << "DEBUG" << std::endl;
    // std::cout << "filename: " << filename << " contents: " << contents << std::endl;
    // std::cout << "DEBUG END" << std::endl;

    // Add the file to the hard drive
    fileManager.addFile(filename, contents);
}

// Function to handle the "Delete a file" action
void deleteFile(FileManager &fileManager)
{
    // Get the filename from the user
    std::string filename;

    // Check if there's a newline character in the buffer
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(); // Ignore the newline character
    }

    std::cout << "Enter filename: ";
    std::getline(std::cin, filename, ' ');

    // NOTE: Added to debug the filename and contents
    // std::cout << "DEBUG" << std::endl;
    // std::cout << "filename: " << filename << std::endl;
    // std::cout << "DEBUG END" << std::endl;

    // Delete the file from the hard drive
    fileManager.deleteFile(filename);
}

// Function to handle the "Output a file" action
void outputFile(FileManager &fileManager)
{
    // Get the filename from the user
    std::string filename;

    // Check if there's a newline character in the buffer
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(); // Ignore the newline character
    }

    std::cout << "Enter filename: ";
    std::getline(std::cin, filename, ' ');

    // NOTE: Added to debug the filename and contents
    // std::cout << "DEBUG" << std::endl;
    // std::cout << "filename: " << filename << std::endl;
    // std::cout << "DEBUG END" << std::endl;

    // read the file from the hard drive and output the contents
    std::string content = fileManager.readFile(filename);
    std::cout << std::left << std::setw(30) << "Filename"
              << "Contents\n";

    // NOTE: Added to debug the filename and contents
    // std::cout << "DEBUG" << std::endl;
    // std::cout << "filename: " << filename << " contents: " << content << std::endl;
    // std::cout << "DEBUG END" << std::endl;

    // output the filename and its contents using this format
    std::cout << std::left << std::setw(30) << filename << content << std::endl;
}

// Main function to drive the simulation int main(int argc, char *argv[])s
int main(int argc, char *argv[])
{
    // Default hard drive size and initial state file
    int hardDriveSize = 10000;    // Default size
    std::string initialStateFile; // Default initial state file is empty

    // Parse command line arguments
    std::map<std::string, std::string> cmdOptions;
    // Loop through the command line arguments and store the options in a map
    for (int i = 1; i < argc; i++)
    {
        // If the argument is -s or -f and there is another argument after it, store it in the map
        std::string arg = argv[i];
        // store the option and its value in the map
        if ((arg == "-s" || arg == "-f") && i + 1 < argc)
        {
            // store the option and its value in the map
            cmdOptions[arg] = argv[++i];
        }
    }

    // Set the hard drive size
    if (cmdOptions.count("-s"))
    {
        // Convert the string to an integer and set the hard drive size
        hardDriveSize = std::stoll(cmdOptions["-s"]);
    }

    // Set the initial state file
    if (cmdOptions.count("-f"))
    {
        // Set the initial state file
        initialStateFile = cmdOptions["-f"];
    }

    // Adjust the constructor as needed
    FileManager fileManager(hardDriveSize);

    // Load initial state from file if provided
    if (!initialStateFile.empty())
    {
        // Read the file line by line and add the files to the hard drive
        std::ifstream file(initialStateFile);
        std::string line;

        // read the file line by line
        while (std::getline(file, line))
        {
            // split the line by spaces
            std::istringstream iss(line);
            std::string filename, contents;
            // create a new file
            if (std::getline(iss, filename, ':') && std::getline(iss, contents))
            {
                // add the file to the hard drive
                fileManager.addFile(filename, contents);
            }
        }
    }

    // Main loop to drive the simulation
    // choice is the user's choice from the menu from options 0-4
    // int choice;
    // do
    // {
    //     // Display the menu
    // printMenu();
    //     // get the user's choice
    //     std::cin >> choice;
    //     // NOTE: Added to debug the choice
    //     std::cout << choice << std::endl;
    //     // switch statement to handle the user's choice
    //     switch (choice)
    //     {
    //     case 1:
    //         // show the files on the hard drive
    //         showFiles(fileManager);
    //         break;
    //     case 2:
    //         // add a file to the hard drive
    //         addFile(fileManager);
    //         break;
    //     case 3:
    //         // delete a file from the hard drive
    //         deleteFile(fileManager);
    //         break;
    //     case 4:
    //         // output a file from the hard drive
    //         outputFile(fileManager);
    //         break;
    //     case 0:
    //         // exit the simulation by breaking out of the loop
    //         break;
    //     default:
    //         // break if the option is invalid
    //         break;
    //     }
    // } while (choice != 0);

    // NOTE: Debugging the loopturns
    // int loopturns = 0;

    // read input from file input by using `./exe < input.txt`
    std::string line;
    while (std::getline(std::cin, line, ' '))
    {
        printMenu();
        // NOTE: Debugging the loopturns
        // loopturns++;

        // split the line by spaces
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        // NOTE: Debugging the command
        // std::cout << "DEBUG" << std::endl;
        // std::cout << command << std::endl;
        // std::cout << "DEBUG END" << std::endl;
        if (command == "1")
        {
            showFiles(fileManager);
        }
        else if (command == "2")
        {
            addFile(fileManager);
        }
        else if (command == "3")
        {
            deleteFile(fileManager);
        }
        else if (command == "4")
        {
            outputFile(fileManager);
        }
        else if (command == "0")
        {
            break;
        }
        else
        {
            break;
        }
    }

    // NOTE: Debugging the loopturns
    // std::cout << "DEBUG" << std::endl;
    // std::cout << "loopturns: " << loopturns << std::endl;
    // std::cout << "DEBUG END" << std::endl;

    // return 0 to indicate successful completion
    return 0;
}