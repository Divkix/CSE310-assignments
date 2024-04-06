#
# Author: Divanshu Chauhan
# ASU ID: 1224807311
#
# Date: 4/6/2024
#
# Description: This Makefile compiles and links the source files for the AdjacencyMatrix assignment.
#              It uses g++ as the compiler with C++11 standard and Wall flag for warnings.
#              The executable produced is named 'adjacencymatrix'.
#              It also includes a 'clean' rule to remove the generated files and a 'run' rule to execute the program.
#

# Compiler
CC = g++

# Compiler flags, using C++20 standard and all warnings
CFLAGS = -std=c++20 -Wall

# Name of the executable
EXEC = adjacencymatrix

# Source files
SOURCES = MatrixGraph_chauhan.cpp chauhan_TestGraph.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Output files such as output_graph*.txt which were used for testing
OUTPUTS = output_graph*.txt

# Header files
HEADERS = Queue_chauhan.hpp MatrixGraph_chauhan.h

# Default target
all: $(EXEC)

# Rule to link the program
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile the source files
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the workspace
clean:
	rm -f $(EXEC) $(OBJECTS) $(OUTPUTS)

.PHONY: all clean run
