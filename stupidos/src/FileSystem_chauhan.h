//
// Name: Divanshu Chauhan
// ASU ID: 1224807311
//
// Date: 2/10/2024
//
// Description: This file contains the implementation of a FileManager class and a File class.
//              The FileManager class is a class that manages files and the hard
//              drive. The File class is a class that represents a file.
//

// FileSystem_chauhan.h
#ifndef FILESYSTEM_CHAUHAN_H
#define FILESYSTEM_CHAUHAN_H

// import the linked list and queue classes along with necessary libraries
#include "LinkedList_chauhan.hpp"
#include "Queue_chauhan.hpp"
#include <string>
#include <vector>

// File class
class File
{
private:
  // Properties
  std::string filename; // Name of the file
  LinkedList<int>
      blocks; // Linked list of block indexes, aka contents of the file

public:
  // Constructor
  File();                     // Default constructor
  File(std::string filename); // Default constructor with filename parameter

  // Methods
  std::string getFileName() const; // returns the filename
  void addBlock(int blockIndex);   // Adds an index to the linked list
  int fileSize() const;            // Returns how big the file is (list size)
  std::vector<int>
  getFileBlocks() const; // Returns the indexes that make up the file
};

// FileManager class
class FileManager
{
private:
  // Properties
  static const int HARD_DRIVE_SIZE = 10000; // Example size
  char hardDrive[HARD_DRIVE_SIZE];          // Hard drive
  Queue<int> blocksAvailable;               // Queue of available blocks
  std::vector<File *> files;                // Vector of files

public:
  // Constructors
  FileManager(); // Default constructor
  FileManager(
      int hardDriveSize); // Default constructor with hard drive size parameter
  FileManager(const std::string
                  &filename); // Default constructor with filename parameter

  // Methods
  void addFile(const std::string &name,
               const std::string &contents); // Adds a file to the hard drive
  void
  deleteFile(const std::string &name); // Deletes a file from the hard drive
  std::string
  readFile(const std::string &name); // Reads a file from the hard drive
  std::vector<std::string>
  getFileNames();                                // Returns the names of all the files on the hard drive
  int readFileSize(const std::string &name);     // Returns the size of a file
  File *findFileByName(const std::string &name); // Returns a file by name
};

#endif // FILESYSTEM_CHAUHAN_H
