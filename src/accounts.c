#include "banking.h"

void update_account(Customer **customers)
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
            print_account_details(current);
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
    else
    {
        int op;
        do
        {
            update_account_menu();
            scanf("%d", &op);

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
            {
                char dob_str[11];
                printf("Customer DOB (DD/MM/YYYY): ");
                scanf(" %[^\n]", dob_str);

                struct tm tm = {0};
                strptime(dob_str, "%d/%m/%Y", &tm);
                current->dob = mktime(&tm);
                printf("Success: Customer date of birth updated.\n");
                break;
            }
            case 6:
            {
                char type;
                printf("Customer Account Type (Savings(S)/Current(C)): ");
                scanf(" %c", &type);
                if (type == 'S' || type == 's')
                {
                    current->type = SAVINGS;
                    printf("Success: Customer account type updated to SAVINGS.\n");
                }
                else if (type == 'C' || type == 'c')
                {
                    current->type = CURRENT;
                    printf("Success: Customer account type updated to CURRENT.\n");
                }
                else
                {
                    printf("Invalid account type. Defaulting to SAVINGS.\n");
                    current->type = SAVINGS;
                }
                break;
            }
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
    Customer *prev = NULL;

    while (current != NULL)
    {
        if (current->account_number == accNo && current->pin == pin)
        {
            found = 1;
            print_account_details(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    }
    else
    {
        char op;
        printf("Are you sure you want to delete your account (Y/N)? ");
        scanf(" %c", &op);

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
            free(current);
            printf("Success: Account deleted successfully.\n");
        }
        else
        {
            printf("Account deletion canceled.\n");
        }
    }
}
