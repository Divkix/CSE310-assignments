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

# Header files
HEADERS = Queue_chauhan.hpp MatrixGraph_chauhan.h Stack_chauhan.hpp

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
	rm -f $(EXEC) $(OBJECTS)

# Rule to run the program
ARGS =
run: $(EXEC)
	./$(EXEC) $(ARGS)
