# Compiler and flags
CC = gcc
CFLAGS = -Iinclude
LDFLAGS = 

# Source files
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# Main executable
TARGET = bankmgmt

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean
