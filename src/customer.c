#include "banking.h"

int transactionExists(Customer *customers, unsigned long transactionId)
{
    Customer *current = customers;
    while (current)
    {
        Transaction *trans = current->history_head;
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
    } while (transactionExists(customers, transactionId));

    return transactionId;
}

void create_account(Customer **customers)
{
    srand(time(0) + rand());
    Customer *newAccount = (Customer *)calloc(1, sizeof(Customer));
    if (!newAccount)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    long int accountNumber = 626001;
    for (int i = 0; i < 10; i++)
        accountNumber = accountNumber * 10 + (secure_random() % 10);

    newAccount->account_number = accountNumber;

    newAccount->pin = generate_pin(); // was: (rand() % 9000) + 1000

    printf("\nCustomer Details::\n");
    printf("Customer Name : ");
    scanf(" %[^\n]", newAccount->holder_name);
    flush_line();

    printf("Customer Address : ");
    scanf(" %[^\n]", newAccount->holder_address);
    flush_line();

    printf("Customer Phone Number : ");
    scanf(" %[^\n]", newAccount->phone_number);
    flush_line();

    printf("Customer Email : ");
    scanf(" %[^\n]", newAccount->email);
    flush_line();

    newAccount->type = read_account_type("Customer Account Type(Savings(S)/Current(C)) : ");

    newAccount->balance = 2000;

    newAccount->dob = read_dob("Customer DOB (DD/MM/YYYY): ");

    newAccount->opening_date = time(NULL);

    Transaction *transactionHistory = (Transaction *)calloc(1, sizeof(Transaction));
    transactionHistory->transaction_id = generate_transactionId(*customers);
    transactionHistory->timestamp = time(NULL);
    transactionHistory->type = DEPOSIT;
    transactionHistory->amount = newAccount->balance;
    transactionHistory->balance_after = newAccount->balance;
    transactionHistory->next = NULL;

    newAccount->history_head = transactionHistory;

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
    print_account_details(newAccount, 1);
}
