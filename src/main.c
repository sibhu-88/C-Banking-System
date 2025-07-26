#include "banking.h"

int main()
{
    int option;
    Customer *customers = NULL; 

    do
    {
       system("clear");

        printf("\tWelcome to Banking System\n");
        main_menu();
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            system("clear");
            create_account(&customers);
            sleep(2);
            break;
        case 2:
            system("clear");
            update_account(&customers);
            break;
        case 3:
            system("clear");
            delete_account(&customers);
            break;
        case 4:
            system("clear");
            view_account_details(customers);
            break;
        case 5:
            deposit_money(&customers);
            break;
        case 6:
            withdraw_money(&customers);
            break;
        case 7:
            system("clear");
            view_all_account_details(customers);
            break;
        case 8:
            
            break;
        case 9:
            // save_account_details();
            break;
        case 0:
            printf("Exiting the program...\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (option != 0);
}

void main_menu(void)
{
    printf("\n\n\t----------------------------------+\n");
    printf("\t|        Banking Management Menu   |\n");
    printf("\t|----------------------------------|\n");
    printf("\t| 1. Create New Account            |\n");
    printf("\t| 2. Update Account Details        |\n");
    printf("\t| 3. Delete Account                |\n");
    printf("\t| 4. View A Account Details        |\n");
    printf("\t| 5. Deposit Money                 |\n");
    printf("\t| 6. Withdraw Money                |\n");
    printf("\t| 7. View All Account Details      |\n");
    printf("\t| 8. Transaction History           |\n");
    printf("\t| 9. Save The Account Details      |\n");
    printf("\t| 0. Exit                          |\n");
    printf("\t+----------------------------------+\n");
    printf("\n\tEnter your choice: ");
}

void update_account_menu(void) {
    printf("\n\n\t----------------------------------+\n");
    printf("\t| Update Account Menu             |\n");
    printf("\t|----------------------------------|\n");
    printf("\t| 1. Update Customer Name         |\n");
    printf("\t| 2. Update Address                |\n");
    printf("\t| 3. Update Phone Number           |\n");
    printf("\t| 4. Update Email                  |\n");
    printf("\t| 5. Update Date of Birth          |\n");
    printf("\t| 6. Update Account Type           |\n");
    printf("\t| 0. Return to Main Menu           |\n");
    printf("\t+----------------------------------+\n");
    printf("\n\tEnter your choice: ");
}