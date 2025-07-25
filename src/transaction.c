#include "banking.h"

void deposit_money(Customer **customers) {
    if (!*customers) {
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
    while (current != NULL) {
        if (current->account_number == accNo && current->pin == pin) {
            found = 1;
            print_account_details(current);
            break;
        }
        current = current->next;
    }

    if (!found) {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    } else {
        double deposit;
        printf("Enter The Amount For Deposit: ");
        scanf("%lf", &deposit);

        if (deposit <= 0) {
            printf("Error: Deposit amount must be greater than zero.\n");
            return;
        }

        current->balance += deposit;
        printf("Success: Amount deposited successfully.\n");
        printf("Available balance: %.2lf\n", current->balance);
    }
}

void withdraw_money(Customer **customers) {
    if (!*customers) {
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
    while (current != NULL) {
        if (current->account_number == accNo && current->pin == pin) {
            found = 1;
            print_account_details(current); 
        }
        current = current->next;
    }

    if (!found) {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    } else {
        double withdraw;
        printf("Enter The Amount For Withdrawal: ");
        scanf("%lf", &withdraw);

        // Validate withdrawal amount
        if (withdraw <= 0) {
            printf("Error: Withdrawal amount must be greater than zero.\n");
            return;
        }
        if (current->balance < withdraw) {
            printf("Error: Insufficient funds. Available balance: %.2lf\n", current->balance);
            return;
        }

        current->balance -= withdraw;
        printf("Success: Amount withdrawn successfully.\n");
        printf("Available balance: %.2lf\n", current->balance);
    }
}
