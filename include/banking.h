#ifndef BANKING_H
#define BANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h> /* only header needed here: time_t is used in the structs */

/* ---------- Types ---------- */
typedef enum
{
    SAVINGS,
    CURRENT
} AccountType;
typedef enum
{
    DEPOSIT,
    WITHDRAWAL
} TransactionType;

typedef struct Transaction
{
    unsigned long transaction_id;
    long int account_number;
    TransactionType type;
    double amount;
    double balance_after;
    time_t timestamp;
    struct Transaction *next;
} Transaction;

typedef struct Customer
{
    unsigned long account_number;
    int pin;
    char holder_name[50];
    char holder_address[100];
    char phone_number[15];
    char email[50];
    AccountType type;
    double balance;
    time_t dob;
    time_t opening_date;
    Transaction *history_head; /* was: transactionHistory */
    struct Customer *next;
} Customer;

/* ---------- main.c ---------- */
void main_menu(void);
void update_account_menu(void);

/* ---------- accounts.c ---------- */
void update_account(Customer **customers);
void delete_account(Customer **customers);

/* ---------- customer.c ---------- */
void create_account(Customer **customers);
int transactionExists(Customer *customers, unsigned long transactionId);
unsigned long generate_transactionId(Customer *customers); /* matches the counter version from B7 */

/* ---------- list.c ---------- */
void view_account_details(Customer *customers);
void view_all_account_details(Customer *customers);
void print_account_details(Customer *customer, int show_pin);

/* ---------- transaction.c ---------- */
void deposit_money(Customer **customers);
void withdraw_money(Customer **customers);
void view_transaction_history(Customer *customers); /* was: transactionHistory */

/* ---------- save.c ---------- */
int save_data_file(Customer *customers);
Customer *load_account_details(void);

/* ---------- input.c (helpers from earlier fixes) ---------- */
void flush_line(void);
void pause_screen(void);
time_t read_dob(const char *prompt);
AccountType read_account_type(const char *prompt);
unsigned int secure_random(void);
int generate_pin(void);

#endif /* BANKING_H */