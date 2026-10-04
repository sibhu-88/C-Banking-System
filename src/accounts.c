#include "banking.h"

void update_account(Customer **customers)
{
    if (!*customers)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        pause_screen();
        return;
    }

    long int accNo;
    int pin, found = 0;

    printf("Enter Customer Account Number: ");
    scanf("%ld", &accNo);
    flush_line();

    printf("Enter Customer PIN: ");
    scanf("%d", &pin);
    flush_line();

    Customer *current = *customers;
    while (current != NULL)
    {
        if (current->account_number == accNo && current->pin == pin)
        {
            found = 1;
            print_account_details(current, 0);
            break;
        }
        current = current->next;
    }

    if (!found)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        pause_screen();
        return;
    }
    else
    {
        int op;
        do
        {
            update_account_menu();
            scanf("%d", &op);
            flush_line();

            switch (op)
            {
            case 1:
                printf("\n\tEnter the Customer Name: ");
                scanf(" %[^\n]", current->holder_name);
                printf("Success: Customer name updated.\n");
                break;
            case 2:
                printf("\n\tEnter the Customer Address: ");
                scanf(" %[^\n]", current->holder_address);
                printf("Success: Customer address updated.\n");
                break;
            case 3:
                printf("\n\tEnter the Customer Phone Number: ");
                scanf(" %[^\n]", current->phone_number);
                printf("Success: Customer phone number updated.\n");
                break;
            case 4:
                printf("\n\tEnter the Customer Email: ");
                scanf(" %[^\n]", current->email);
                printf("Success: Customer email updated.\n");
                break;
            case 5:
                current->dob = read_dob("Customer DOB (DD/MM/YYYY): ");
                printf("Success: Customer date of birth updated.\n");
                break;
            case 6:
                current->type = read_account_type("Customer Account Type (Savings(S)/Current(C)): ");
                printf("Success: Customer account type updated to %s.\n",
                       current->type == SAVINGS ? "SAVINGS" : "CURRENT");
                break;
            case 0:
                printf("\n\tBack to main menu.......!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
            }
        } while (op != 0);
    }
}

void delete_account(Customer **customers)
{
    if (!*customers)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        pause_screen();
        return;
    }

    long int accNo;
    int pin, found = 0;

    printf("Enter Customer Account Number: ");
    scanf("%ld", &accNo);
    flush_line();

    printf("Enter Customer PIN: ");
    scanf("%d", &pin);
    flush_line();

    Customer *current = *customers;
    Customer *prev = NULL;

    while (current != NULL)
    {
        if (current->account_number == accNo && current->pin == pin)
        {
            found = 1;
            print_account_details(current, 0);
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        pause_screen();
        return;
    }
    else
    {
        char op;
        printf("Are you sure you want to delete your account (Y/N)? ");
        scanf(" %c", &op);
        flush_line();

        if (tolower(op) == 'y')
        {
            if (prev == NULL)
            {
                *customers = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current->history_head);  // Free the transaction history
            free(current);
            printf("Success: Account deleted successfully.\n");
        }
        else
        {
            printf("Account deletion canceled.\n");
        }
    }
}
