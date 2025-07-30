---

```markdown
# 💰 C Banking System

A simple command-line banking system developed in C that allows users to manage customer accounts, perform transactions, and save data using structured programming principles.

## 📂 Project Structure

```

.
├── accounts.c       # Functions to manage account creation, deletion, and modification
├── customer.c       # Customer information and handling logic
├── list.c           # Linked list implementation for dynamic record management
├── main.c           # Entry point of the program with user interaction menu
├── save.c           # Save/load functionality for data persistence
├── transaction.c    # Deposit and withdrawal functionality
├── banking.h        # Header file with function prototypes and struct definitions

````

## 🔧 Features

- Add new customer accounts
- Deposit and withdraw money
- View customer list
- Save and load data from file
- Linked list-based dynamic memory management
- Modular file separation for better maintenance

## 🛠️ Compilation

Use the following `Makefile` or compile manually:

### Compile with `gcc`:
```bash
gcc main.c accounts.c customer.c list.c transaction.c save.c -o banking
````

### Run:

```bash
./banking
```

## 🧾 Data Handling

* All customer records are stored in a linked list.
* Persistent storage is achieved using file I/O.
* Data is saved before program exits and loaded at startup.

## 🔐 Account Information

Each account holds:

* Customer name and ID
* Account number
* Balance
* Transaction history

## 📚 Dependencies

* Standard C Library (no external dependencies)
* Works on Linux/GCC-compatible systems

## 🚀 Getting Started

1. Clone or download this repository.
2. Compile using the provided instructions.
3. Run the executable to manage bank records interactively.

## 🤝 Contributions

Feel free to fork this project and suggest improvements or fixes. This project is designed as a simple educational tool for understanding structured programming and file handling in C.

## 📄 License

This project is released under the MIT License.

```
