#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

typedef enum
{
    SAVINGS,
    CURRENT,
} AccountType;

typedef enum
{
    DEPOSIT,
    WITHDRAWAL
} TransactionType;

typedef struct Transaction
{
    unsigned long int transaction_id;
    long int account_number;
    TransactionType type;
    double amount;
    double balance_after;
    time_t timestamp;
    struct Transaction *next;
} Transaction;

typedef struct Customer
{
    unsigned long int account_number;
    int pin;
    char holder_name[50];
    char holder_address[100];
    char phone_number[15];
    char email[50];
    AccountType type;
    double balance;
    time_t dob;
    time_t opening_date;
    Transaction *transactionHistory;
    struct Customer *next;
} Customer;

void main_menu(void);
void update_account_menu(void);

void create_account(Customer **customers);
void update_account(Customer **customers);
void delete_account(Customer **customers);
void view_account_details(Customer *customers);
void deposit_money(Customer **customers);
void withdraw_money(Customer **customers);
void view_all_account_details(Customer *customers);
void transactionHistory(Customer *customers); 
void save_account_details(Customer *customers);

void print_account_details(Customer *customer);

