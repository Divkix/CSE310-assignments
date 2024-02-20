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

// Import necessary libraries
#include "FileSystem_chauhan.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

// Default constructor for the File class
File::File() {}

// FileManager constructor method with filename parameter
File::File(std::string filename) : filename(filename) {}

// FileManager constructor method with HARD_DRIVE_SIZE parameter
FileManager::FileManager(int HARD_DRIVE_SIZE)
{
  // Initialize the hard drive with null characters
  for (int i = 0; i < HARD_DRIVE_SIZE; ++i)
  {
    // Add the block index to the queue
    blocksAvailable.enqueue(i);
  }

  // Initialize the hard drive with null characters
  std::fill_n(hardDrive, HARD_DRIVE_SIZE,
              '\0'); // Initialize hard drive with null characters
}

// FileManager constructor method with filename parameter
FileManager::FileManager(const std::string &filename)
{
  // Initialize the hard drive with null characters
  std::ifstream file(filename);

  // if the file is open
  if (file.is_open())
  {
    // read the file line by line
    std::string line;
    while (std::getline(file, line))
    {
      // split the line by spaces
      std::istringstream iss(line);
      std::string name;
      std::string block;
      iss >> name;
      // create a new file
      File *newFile = new File;
      // set the file name
      while (iss >> block)
      {
        // add the block to the file
        newFile->addBlock(std::stoi(block));
      }
      // add the file to the vector
      files.push_back(newFile);
    }
  }
  else
  {
    // print an error message if the file is not open
    std::cout << "Unable to open file";
  }
}

// Method for getting the filename
std::string File::getFileName() const
{
  // return the file name
  return filename;
}

// Method for adding a block to the file
void File::addBlock(int blockIndex)
{
  // Add the block index to the linked list
  blocks.sortedInsert(blockIndex);
}

// Method for getting the file size
int File::fileSize() const
{
  // Return the size of the linked list
  return blocks.size();
}

// Method for getting the file blocks
std::vector<int> File::getFileBlocks() const
{
  // print the linked list
  blocks.printList();

  // Assuming blocks is a LinkedList of integers and you want to return them as
  // a vector
  std::vector<int> blockVector;
  ListNode<int> *current = blocks.head;
  // while current is not null, add the data to the vector and move to the next
  // node
  while (current != nullptr)
  {
    // Add the data to the vector
    blockVector.push_back(current->data);
    // Move to the next node
    current = current->next;
  }
  // Return the vector
  return blockVector;
}

// Method for finding a file by name
File *FileManager::findFileByName(const std::string &name)
{
  // Iterate through the files and return the file if found
  for (auto file : files)
  {
    // if the file name is equal to the name, return the file
    if (file->getFileName() == name)
    {
      // return the file
      return file;
    }
  }

  // return null if the file is not found
  return nullptr;
}

// Method for adding a file to the hard drive
void FileManager::addFile(const std::string &name,
                          const std::string &contents)
{
  // Check if the file already exists
  if (findFileByName(name) != nullptr)
  {
    // return
    exit(0);
  }

  // Create a new File object dynamically with the default constructor
  File *newFile = new File(name);
  // run a loop for each character in the contents
  for (char c : contents)
  {
    // if the queue is empty, print an error message and return
    if (blocksAvailable.isEmpty())
    {
      // print an error message if the hard drive is full and return
      std::cout << "Hard drive is full." << std::endl;
      return;
    }

    // get the block index from the queue
    int blockIndex = blocksAvailable.front();

    // remove the block index from the queue
    blocksAvailable.dequeue();

    // set the character in the hard drive at the block index
    hardDrive[blockIndex] = c;

    // add the block index to the file
    newFile->addBlock(blockIndex);
  }

  // add the file to the vector
  files.push_back(newFile);
}

// Method for deleting a file from the hard drive
void FileManager::deleteFile(const std::string &name)
{
  // Find the file by name
  File *file = findFileByName(name);
  // if the file is not found, print an error message and return
  if (file == nullptr)
  {
    std::cout << "File not found." << std::endl;
    return;
  }

  // for each block index in the file, set the hard drive at the block index to
  // null
  for (int blockIndex : file->getFileBlocks())
  {
    // set the hard drive at the block index to null
    hardDrive[blockIndex] = '\0';
    // add the block index to the queue
    blocksAvailable.enqueue(blockIndex);
  }
  // remove the file from the vector
  files.erase(std::remove(files.begin(), files.end(), file), files.end());
  // delete the file
  delete file;
}

// Method for reading a file from the hard drive
std::string FileManager::readFile(const std::string &name)
{
  // Find the file by name
  auto file = findFileByName(name);
  // if the file is not found, print an error message and return
  if (file == nullptr)
  {
    std::cout << "File not found." << std::endl;
    return "";
  }

  // for each block index in the file, add the character in the hard drive at
  // the block index to the contents
  std::vector<int> blocks = file->getFileBlocks();
  // define contents as an empty string
  std::string contents;
  // for each block index in the file, add the character in the hard drive at
  // the block index to the contents
  for (int blockIndex : blocks)
  {
    // add the character in the hard drive at the block index to the contents
    contents += hardDrive[blockIndex];
  }

  // return the contents
  return contents;
}

// Method for reading the file size
int FileManager::readFileSize(const std::string &name)
{
  // Find the file by name
  auto file = findFileByName(name);
  // if the file is not found, print an error message and return
  if (file == nullptr)
  {
    std::cout << "File not found." << std::endl;
    return -1;
  }

  // return the file size if the file is found
  return file->fileSize();
}

// Method for getting the file names
std::vector<std::string> FileManager::getFileNames()
{
  // create a vector of file names
  std::vector<std::string> filenames;

  // for each file in the files vector, add the file name to the vector of file
  // names
  for (auto file : files)
  {
    // add the file name to the vector of file names
    filenames.push_back(file->getFileName());
  }
  // return the vector of file names
  return filenames;
}
