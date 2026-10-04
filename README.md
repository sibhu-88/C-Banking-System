# 💰 C Banking System

A modular, menu-driven **banking management system written in C**. It runs in the terminal and lets you create accounts, deposit and withdraw money, view transaction history, and keep all data between runs in a binary file.

---

## 📖 About

This project is a learning exercise in building a complete, multi-file C application. Customer accounts and their transactions are stored in **linked lists** in memory, protected by a PIN, and saved to disk when you choose *Save* or *Exit*.

Every input is validated, so mistyped numbers, bad dates, overlong text or empty fields cannot crash the program or corrupt your data.

## ✨ Features

- Create an account with an auto-generated 16-digit account number and 4-digit PIN
- Update name, address, phone, email, date of birth and account type
- Delete an account (with confirmation)
- View one account or all accounts
- Deposit and withdraw with balance checks (no overdraft)
- Full per-account transaction history (ID, type, amount, balance after, timestamp)
- PIN-protected operations; the PIN is masked everywhere except right after account creation
- Input validation: phone (10–14 digits), email format, real calendar dates (`DD/MM/YYYY`), positive amounts
- Safe data file: written atomically, validated on load, damaged files are kept as `.bad`
- Automatic save and memory clean-up on every exit path (including <kbd>Ctrl</kbd>+<kbd>D</kbd>)

## 📋 Prerequisites

| Requirement | Notes |
|-------------|-------|
| **OS** | Linux, macOS, or Windows via **WSL** (uses POSIX functions such as `strptime`) |
| **Compiler** | `gcc` or `clang` with C11 support |
| **Build tool** | `make` |
| **Architecture** | 64-bit |

Install on Debian/Ubuntu:

```bash
sudo apt update && sudo apt install build-essential
```

No external libraries are required.

## 🚀 Getting Started

```bash
# 1. Clone
git clone https://github.com/sibhu-88/C-Banking-System.git
cd C-Banking-System

# 2. Build
make

# 3. Run
./bankmgmt        # or: make run
```

Other commands:

```bash
make clean        # remove build output (your saved data is kept)
```

## 🖥️ Usage

The main menu looks like this:

```
+----------------------------------+
|     Banking Management Menu      |
|----------------------------------|
| 1. Create New Account            |
| 2. Update Account Details        |
| 3. Delete Account                |
| 4. View An Account's Details     |
| 5. Deposit Money                 |
| 6. Withdraw Money                |
| 7. View All Account Details      |
| 8. Transaction History           |
| 9. Save The Account Details      |
| 0. Exit                          |
+----------------------------------+
```

- A new account starts with an opening balance of **2000** (`MIN_OPENING_BALANCE` in `banking.h`).
- **Write down your PIN** when the account is created; it is shown only once.
- Option **0** saves automatically before exiting.

## 📁 Project Structure

```
C-Banking-System/
├── include/
│   └── banking.h        # structs, constants, function prototypes
├── src/
│   ├── main.c           # entry point, menus, exit handling
│   ├── accounts.c       # update and delete accounts
│   ├── customer.c       # create account, login (PIN check), ID generation, memory free
│   ├── list.c           # view / print account details
│   ├── transaction.c    # deposit, withdraw, transaction history
│   ├── save.c           # save to and load from the data file
│   └── input.c          # validated input helpers, screen helpers, random numbers
├── Makefile
├── LICENSE
└── README.md
```

| File | Responsibility |
|------|----------------|
| `main.c` | Menu loop, loads data at start, saves and frees memory at exit |
| `accounts.c` | Update fields of an account, delete an account |
| `customer.c` | Account creation, `authenticate()`, unique account/transaction IDs |
| `list.c` | Formatted account display |
| `transaction.c` | Deposit/withdraw logic (shared), history table |
| `save.c` | Binary persistence with magic header, temp-file + rename, validation |
| `input.c` | Safe reading of text, numbers, amounts, dates, Y/N |

## 🧠 Topics Covered

- Structs, enums and `typedef`
- Singly linked lists (customers, each with its own transaction list)
- Dynamic memory (`calloc` / `free`) and leak-free clean-up
- Binary file I/O (`fread` / `fwrite`) and atomic saves with `rename`
- Input validation with `fgets`, `strtol`, `strtod`, `strptime`
- Modular design with header files
- Makefiles with automatic header dependencies
- Secure random numbers from `/dev/urandom`
- `atexit()` handlers
- Debugging with AddressSanitizer / UBSan

## 💾 Data Storage

- All data is kept in `customersDetails.dat`, created in the folder you run the program from.
- The file starts with a `BANK1` marker, so the program can recognise it.
- The file stores raw structs. It works only on the same OS, CPU and compiler that created it, so it is **not portable** between machines.
- The data file contains customer information and is excluded from Git by `.gitignore`.

## 🔍 Debugging Build

To check for memory errors:

```bash
gcc -std=c11 -g -fsanitize=address,undefined -Iinclude src/*.c -o bankmgmt_debug
./bankmgmt_debug
```

## ⚠️ Limitations

- Educational project: PINs are stored as plain numbers, not hashed.
- Money is stored as `double`; a real system would use integer cents.
- Single user, no network, no concurrency.

## 🔮 Future Improvements

- Hash PINs and lock an account after repeated wrong attempts
- Store money as integer cents
- Money transfer between accounts
- Portable data format (JSON or SQLite)
- Unit tests and CI
- GUI (GTK) or web front-end

## 🪪 License

Released under the [MIT License](LICENSE).

## 🙋‍♂️ Author

Developed by **Siva Prabhu** (Sibhu), Embedded Systems Trainer & Developer.