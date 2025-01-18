# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fno-lto
TARGET = main

# Source and objects
SRC = main.cpp FuncClass.cpp
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link the binary
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
