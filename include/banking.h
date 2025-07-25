#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_TRANSACTION_DESC 100
#define ACCOUNT_NUMBER_LENGTH 20

typedef enum {
    SAVINGS,
    CURRENT,
    FIXED_DEPOSIT,
    LOAN
} AccountType;

typedef enum {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER,
    INTEREST,
    FEE
} TransactionType;

typedef struct {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    char holder_name[MAX_NAME_LENGTH];
    char holder_address[MAX_ADDRESS_LENGTH];
    char phone_number[15];
    char email[50];
    time_t date_of_birth;
    char national_id[20];
} Customer;

typedef struct {
    char account_number[ACCOUNT_NUMBER_LENGTH];
    AccountType type;
    double balance;
    double interest_rate;
    time_t opening_date;
    bool is_active;
} Account;

typedef struct {
    char transaction_id[32]; // UUID or similar
    char account_number[ACCOUNT_NUMBER_LENGTH];
    TransactionType type;
    double amount;
    double balance_after;
    time_t timestamp;
    char description[MAX_TRANSACTION_DESC];
    char reference_number[32]; // For transfers/other tracking
} Transaction;