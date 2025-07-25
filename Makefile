# Compiler and flags
CC = gcc
INCLUDES = -Iinclude
LDFLAGS = 

# Source files
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = bankmgmt

# Default build target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

# Create object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	@echo "Starting banking management system..."
	@./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean