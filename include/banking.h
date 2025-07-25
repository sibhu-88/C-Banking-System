#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

typedef struct Customer
{
    long int account_number;
    int pin;
    char holder_name[50];
    char holder_address[100];
    char phone_number[15];
    char email[50];
    AccountType type;
    double balance;
    time_t dob;
    time_t opening_date;
    struct Customer *next;
} Customer;

typedef struct Transaction
{
    long int transaction_id;
    long int account_number;
    TransactionType type;
    double amount;
    double balance_after;
    time_t timestamp;
    struct Transaction *next;
} Transaction;

void main_menu(void);

void create_account(Customer **customers);
void view_all_account_details(Customer *customers);
void print_account_details(Customer *customer);
