#include "banking.h"

void deposit_money(Customer **customers)
{
    if (!*customers)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    }

    long int accNo;
    int pin, found = 0;

    printf("Enter Customer Account Number: ");
    scanf("%ld", &accNo);

    printf("Enter Customer PIN: ");
    scanf("%d", &pin);

    Customer *current = *customers;
    while (current != NULL)
    {
        if (current->account_number == accNo && current->pin == pin)
        {
            found = 1;
            print_account_details(current,0);
            break; // Don't forget to break here
        }
        current = current->next;
    }

    if (!found)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    }

    double deposit;
    do
    {
        printf("Enter The Amount For Deposit: ");
        scanf("%lf", &deposit);

        if (deposit <= 0)
        {
            printf("Error: Deposit amount must be greater than zero.\n");
            return;
        }
    } while (deposit <= 0);

    current->balance += deposit;

    Transaction *newTransaction = (Transaction *)calloc(1, sizeof(Transaction));
    if (!newTransaction)
    {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        return;
    }

    newTransaction->transaction_id = generate_transactionId(current);
    newTransaction->timestamp = time(NULL);
    newTransaction->type = DEPOSIT;
    newTransaction->amount = deposit;
    newTransaction->balance_after = current->balance;
    newTransaction->next = NULL;

    if (current->history_head == NULL)
    {
        current->history_head = newTransaction;
    }
    else
    {
        Transaction *temp = current->history_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newTransaction;
    }

    printf("Success: Amount deposited successfully.\n");
    printf("Available balance: %.2lf\n", current->balance);
    pause_screen();
}

void withdraw_money(Customer **customers)
{
    if (!*customers)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    }

    long int accNo;
    int pin, found = 0;

    printf("Enter Customer Account Number: ");
    scanf("%ld", &accNo);

    printf("Enter Customer PIN: ");
    scanf("%d", &pin);

    Customer *current = *customers;
    while (current != NULL)
    {
        if (current->account_number == accNo && current->pin == pin)
        {
            found = 1;
            print_account_details(current,0);
            break;
        }
        current = current->next;
    }

    if (!found)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    }

    double withdraw;
    do
    {
        printf("Enter The Amount For Withdrawal: ");
        scanf("%lf", &withdraw);

        if (withdraw <= 0)
        {
            printf("Error: Withdrawal amount must be greater than zero.\n");
            return;
        }
        if (current->balance < withdraw)
        {
            printf("Error: Insufficient funds. Available balance: %.2lf\n", current->balance);
            return;
        }

    } while (withdraw <= 0 || current->balance < withdraw);

    current->balance -= withdraw;

    Transaction *newTransaction = (Transaction *)calloc(1, sizeof(Transaction));
    if (!newTransaction)
    {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        return;
    }

    newTransaction->transaction_id = generate_transactionId(current);
    newTransaction->timestamp = time(NULL);
    newTransaction->type = WITHDRAWAL;
    newTransaction->amount = withdraw;
    newTransaction->balance_after = current->balance;
    newTransaction->next = NULL;

    if (current->history_head == NULL)
    {
        current->history_head = newTransaction;
    }
    else
    {
        Transaction *temp = current->history_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newTransaction;
    }

    printf("Success: Amount withdrawn successfully.\n");
    printf("Available balance: %.2lf\n", current->balance);
    pause_screen();
}

void transactionHistory(Customer *customers)
{
    if (!customers)
    {
        printf("No customer records found.\n");
        return;
    }

    long int accNo;
    int pin, found = 0;

    printf("Enter Customer Account Number: ");
    scanf("%ld", &accNo);

    printf("Enter Customer PIN: ");
    scanf("%d", &pin);

    Customer *current = customers;
    while (current != NULL)
    {
        if (current->account_number == accNo && current->pin == pin)
        {
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        return;
    }

    printf("\nAccount Number: %ld\n", current->account_number);
    printf("\nAccount Name: %s\n", current->holder_name);
    printf("\nAccount Type: %s\n", current->type == SAVINGS ? "SAVINGS" : "CURRENT");

    if (!current->history_head)
    {
        printf("No transaction history available.\n");
        return;
    }

    printf("\nTransaction History:\n");
    printf("%-10s %-12s %-12s %-12s %s\n", "ID", "Type", "Amount", "Balance", "Timestamp");
    printf("--------------------------------------------------------------------------------\n");

    Transaction *temp = current->history_head;
    while (temp != NULL)
    {
        char *typeStr;
        switch (temp->type)
        {
        case DEPOSIT:
            typeStr = "Deposit";
            break;
        case WITHDRAWAL:
            typeStr = "Withdrawal";
            break;
        default:
            typeStr = "Unknown";
            break;
        }

        char timeStr[26];
        struct tm *tm_info = localtime(&temp->timestamp);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);

        printf("%-10ld %-12s %-12.2lf %-12.2lf %s\n",
               temp->transaction_id, typeStr, temp->amount, temp->balance_after, timeStr);

        temp = temp->next;
    }
    pause_screen();
}
