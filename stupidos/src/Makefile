# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

# Name of the executable
EXEC = stupidos

# Source files
SOURCES = FileSystem_chauhan.cpp stupidOS_chauhan.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = LinkedList_chauhan.hpp Queue_chauhan.hpp FileSystem_chauhan.h

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