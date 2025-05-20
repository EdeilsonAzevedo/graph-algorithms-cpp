# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++17

# Include and source directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj

# Target executable
TARGET = prim.bin

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
