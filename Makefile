# Definitive Makefile for a flat directory structure.
# This version assumes all .h and .cpp files are in the same directory as the Makefile.

# Compiler and C++ standard. Using g++ but will respect system defaults.
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories for output files.
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

# The final executable file name.
TARGET = $(BIN_DIR)/library_app

# --- CRUCIAL PART ---
# Automatically find all .cpp files in the CURRENT directory.
# This MUST find all your .cpp files.
SOURCES = $(wildcard *.cpp)

# Generate the corresponding object file names, placing them in the obj directory.
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# The default target, 'all', which is executed when you just type 'make'.
all: $(TARGET)

# Rule to link the final executable.
$(TARGET): $(OBJECTS)
	@echo "--- Linking executable ---"
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@
	@echo "Build successful! Executable is at $(TARGET)"

# Pattern rule to compile a .cpp file into a .o object file.
$(OBJ_DIR)/%.o: %.cpp
	@echo "Compiling $< ..."
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to run the application.
run: all
	@mkdir -p $(DATA_DIR)
	./$(TARGET)

# Target to clean up all build artifacts.
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned all build artifacts."

# '.PHONY' declares targets that are not actual files.
.PHONY: all run clean