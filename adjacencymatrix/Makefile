# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++20 -Wall

# Name of the executable
EXEC = adjacencymatrix

# Source files
SOURCES = MatrixGraph_chauhan.cpp chauhan_TestGraph.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Output files such as output_graph*.txt
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
