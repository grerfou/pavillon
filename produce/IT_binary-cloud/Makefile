Makefile

# Variables
#CXX = g++
#CXXFLAGS = -Wall -g -std=c++17 -I/usr/local/include
#LDFLAGS = -lraylib
#SRC_DIR = src
#OBJ_DIR = obj
#TARGET = app

# Source and object files
#SRCS = $(wildcard $(SRC_DIR)/*.cpp)
#OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
#all: $(TARGET)

# Build the target
#$(TARGET): $(OBJS)
#	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build object files
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
#	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
#$(OBJ_DIR):
#	mkdir -p $(OBJ_DIR)

# Clean up build files
#clean:
#	rm -rf $(OBJ_DIR) $(TARGET)

#run :
#	make
#	./app
#	make clean

# Phony targets
#.PHONY: all clean




# Nom de l'exécutable
#TARGET = main

# Fichiers sources
#SOURCES = ./src/main.cpp

# Compilateur
#CXX = clang++

# Drapeaux de compilation
#CXXFLAGS = -I. -Wall -std=c++11
#CXXFLAGS = clang++ -I. -Wall -std=c++11 ./src/main.cpp -o main -lraylib -lm -ldl -lpthread -lX11




# Bibliothèques
#LIBS = -lraylib -lm -ldl -lpthread -lX11

# Règle par défaut
#all: $(TARGET)

# Règle pour créer l'exécutable
#$(TARGET): $(SOURCES)
#	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

# Règle pour nettoyer les fichiers compilés
#clean:
#	rm -f $(TARGET) *.o

# Règle pour exécuter le programme
#run: $(TARGET)
#	./$(TARGET)

# Règle pour tout nettoyer et recompiler
#rebuild: clean all

#.PHONY: all clean run rebuild




# Nom de l'exécutable
TARGET = ImageToBinary

# Dossiers
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Fichiers source et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g    # -g pour le debug

# Options de linkage (sans librt)
LDFLAGS = -lraylib -lm -lpthread -ldl -lX11

# Règles
all: $(BIN_DIR)/$(TARGET)

# Créer l'exécutable
$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Créer les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et les binaires
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean







gcc -o ImageToBinary ./src/main.c -lraylib -lm -lpthread -ldl -lX11
