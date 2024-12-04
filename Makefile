# Set the compiler
CXX = g++

# Set the compiler flags (using quotes to handle spaces in paths)
CXXFLAGS = -I"External Library/SFML/include" -I"External Library/box2d/include"

# Source and object files
SRC = $(wildcard src/*.cpp)      # All .cpp files in the src folder
OBJ = $(SRC:src/%.cpp=obj/%.o)   # Corresponding .o files stored in the obj folder

# Executable name
TARGET = main

# Folders
OBJ_DIR = obj
SRC_DIR = src

# The default target
all: $(TARGET)

# Create object directory if it doesn't exist, then compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) -L"External Library/SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system \
    -L"External Library/box2d/lib" -lbox2d 

# Clean target to remove generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
