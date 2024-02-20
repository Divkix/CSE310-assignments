#
# Author: Divanshu Chauhan
# ASU ID: 1224807311
#
# Date: 2/10/2024
#
# Description: This Makefile compiles and links the source files for the StupidOS project.
#              It uses g++ as the compiler with C++11 standard and Wall flag for warnings.
#              The executable produced is named 'stupidos'.
#              It also includes a 'clean' rule to remove the generated files and a 'run' rule to execute the program.
#

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
