# Makefile for Cheese project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreturn-type -g

# Target executable
TARGET = ./build/solution.exe

# Runtime arguments
RUN_ARGS ?=

# Source files
SOURCES = $(wildcard src/Day[0-9][0-9].cpp) ./src/main.cpp $(wildcard src/Day[0-9][0-9]/*.cpp) $(wildcard src/utils/*.cpp) ./src/Tester/Tester.cpp

# include directories
INCLUDE_DIRS = include include/utils $(wildcard include/Day[01][0-9]) include/Tester

# include
INCLUDE = $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(TARGET) $(OBJECTS)

# Build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	$(TARGET) $(RUN_ARGS)

# Run tests
tests: $(TARGET)
	$(TARGET) -t

# Show help
help:
	@echo Available targets:
	@echo   all      - Build the program (default)
	@echo   clean    - Remove object files and executable
	@echo   rebuild  - Clean and build
	@echo   run      - Build and run the program
	@echo   help     - Show this help message

.PHONY: all clean rebuild run help
