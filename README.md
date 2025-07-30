# 💰 C Banking System

A modular C-based Banking Management System designed for educational purposes. This command-line interface program allows users to manage bank accounts, perform transactions, and persist data using file I/O.

---

## 📁 Project Files

| File Name       | Description |
|----------------|-------------|
| `main.c`        | Main entry point, user interaction and menu navigation |
| `accounts.c`    | Create, delete, and manage account-related operations |
| `customer.c`    | Handle customer details and verification |
| `list.c`        | Linked list implementation for dynamic customer records |
| `transaction.c` | Perform deposit and withdrawal operations |
| `save.c`        | Load and save data to/from file storage |
| `banking.h`     | Header file with struct definitions and function prototypes |

---

## 🔧 Features

- Add, delete, and modify customer accounts
- Deposit and withdraw functionality
- Linked list implementation for storing customer records
- Data persistence using files
- Modular structure for easier maintenance

---

## 🛠️ How to Compile

Use `gcc` to compile all the `.c` files together:

```bash
gcc main.c accounts.c customer.c list.c transaction.c save.c -o banking
```

Or use a `Makefile`:

```makefile
CC = gcc
CFLAGS = -Wall
SRC = main.c accounts.c customer.c list.c transaction.c save.c
OBJ = $(SRC:.c=.o)
TARGET = banking

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f *.o $(TARGET)
```

Run the program:

```bash
./banking
```

---

## 💾 Data Storage

- Customer and account data are stored in memory during runtime using linked lists.
- Data is written to and read from a file (`.dat` or `.txt`) to persist between runs.

---

## 🧍 Customer Information Includes

- Customer Name
- Account Number
- ID/Proof
- Balance
- Transaction history

---

## 📚 Learning Objectives

This project helps reinforce:
- C programming structure
- File handling (read/write)
- Linked lists
- Modular programming
- Function pointers and struct usage

---

## 🚀 Getting Started

1. Clone or download the files.
2. Compile using `gcc` or a `Makefile`.
3. Run the `./banking` binary and follow the interactive menu.
4. Use options to add, modify, list, and delete customers or perform transactions.

---

## ✅ Future Improvements

- Add password protection or login system
- Store data in JSON or SQLite for better structure
- GUI using GTK or web interface
- Enhanced error handling and validation

---

## 🪪 License

This project is provided for educational use and is open-source under the MIT License.

---

## 🙋‍♂️ Author

Developed by **Siva Prabhu** (Sibhu) — Embedded Systems Trainer & Developer
