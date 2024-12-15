# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRC = word_compression.c word_utils.c
# Output executable
OUT = main

# Default target
all: $(OUT)

# Build the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Clean up build files
clean:
	rm -f $(OUT)