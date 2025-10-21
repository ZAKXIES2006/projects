# Tell compiler to use g++
CXX = g++
# use C++17 standard, enable common warnings, enable extra warnings, include debug info
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories for output files
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

# Executable file name
TARGET = $(BIN_DIR)/library_app

# Find all .cpp files in current dir
SOURCES = $(wildcard *.cpp)

# Generate corresponding object file names, place them in obj dir
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# When make is typed, build final target
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJECTS)
	@echo "--- Linking executable ---"
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@
	@echo "Build successful! Executable is at $(TARGET)"

# Pattern rule to compile a .cpp file into a .o object file
$(OBJ_DIR)/%.o: %.cpp
	@echo "Compiling $< ..."
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to run the application.
run: all
	@mkdir -p $(DATA_DIR)
	./$(TARGET)

# 'make clean' to delete all compiled files
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned all build artifacts."

# '.PHONY' declares targets that are not actual files
.PHONY: all run clean