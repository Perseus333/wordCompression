# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Source files
SRC = src/main.c src/compression.c src/word_utils.c src/hash_utils.c
# Output executable
OUT = bin/main

# Default target
all: $(OUT)

# Build the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)