CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS =
INCLUDE_DIR = include
SRC_DIR = src
BIN_DIR = . # Or a 'bin' directory if you prefer

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/accounts.c \
       $(SRC_DIR)/customer.c \
       $(SRC_DIR)/list.c \
       $(SRC_DIR)/transaction.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/bankmgmt

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)