#include "banking.h"

int accountExists(Customer *customers, long int accountNumber)
{
    Customer *current = customers;
    while (current)
    {
        if (current->account_number == accountNumber)
            return 1;
        current = current->next;
    }
    return 0;
}

int transactionExists(Customer *customers, long int transactionId)
{
    Customer *current = customers;
    while (current)
    {
        Transaction *trans = current->transactionHistory;
        while (trans)
        {
            if (trans->transaction_id == transactionId)
            {
                return 1;
            }
            trans = trans->next;
        }
        current = current->next;
    }
    return 0; // Transaction does not exist
}

unsigned long int generate_transactionId(Customer *customers)
{
    unsigned long int transactionId;

    do
    {
        transactionId = (rand() % 9) + 1; // First digit 1-9 (to avoid leading zeros)
        for (int i = 1; i < 10; i++)
            transactionId = transactionId * 10 + (rand() % 10);
    } while (accountExists(customers, transactionId));

    return transactionId;
}

unsigned long int accountGenerate(Customer *customers)
{
    srand(time(0));
    unsigned long int accountNumber;
    do
    {
        accountNumber = 626001;
        for (int i = 0; i < 10; i++)
            accountNumber = accountNumber * 10 + (rand() % 10);
    } while (accountExists(customers, accountNumber));

    return accountNumber;
}

void create_account(Customer **customers)
{
    srand(time(0) + rand());
    Customer *newAccount = (Customer *)malloc(sizeof(Customer));
    if (!newAccount)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newAccount->account_number = accountGenerate(*customers);
    newAccount->pin = (rand() % 9000) + 1000;

    printf("\nCustomer Details::\n");
    printf("Customer Name : ");
    scanf(" %[^\n]", newAccount->holder_name);

    printf("Customer Address : ");
    scanf(" %[^\n]", newAccount->holder_address);

    printf("Customer Phone Number : ");
    scanf(" %[^\n]", newAccount->phone_number);

    printf("Customer Email : ");
    scanf(" %[^\n]", newAccount->email);

    char type;
    printf("Customer Account Type(Savings(S)/Current(C)) : ");
    scanf(" %c", &type);
    newAccount->type = type;

    if (type == 'S' || type == 's')
        newAccount->type = SAVINGS;
    else if (type == 'C' || type == 'c')
        newAccount->type = CURRENT;
    else
    {
        printf("Invalid account type. Defaulting to SAVINGS.\n");
        newAccount->type = SAVINGS;
    }

    newAccount->balance = 2000;

    char dob_str[11];
    printf("Customer DOB (DD/MM/YYYY): ");
    scanf(" %[^\n]", dob_str);

    struct tm tm = {0};
    strptime(dob_str, "%d/%m/%Y", &tm);
    newAccount->dob = mktime(&tm);

    newAccount->opening_date = time(NULL);

    Transaction *transactionHistory = (Transaction *)malloc(sizeof(Transaction));
    transactionHistory->transaction_id = generate_transactionId(customers);
    transactionHistory->timestamp = time(NULL);
    transactionHistory->type = DEPOSIT;
    transactionHistory->amount = newAccount->balance;
    transactionHistory->balance_after = newAccount->balance;
    transactionHistory->next = NULL;

    newAccount->transactionHistory = transactionHistory;

    if (!*customers)
    {
        newAccount->next = *customers;
        *customers = newAccount;
    }
    else
    {
        Customer *current = *customers;
        while (current->next)
            current = current->next;

        newAccount->next = current->next;
        current->next = newAccount;
    }

    system("clear");

    printf("Account created successfully!\n");
    print_account_details(newAccount);
}
