#include "banking.h"


int main()
{
    int option;
    Customer *customers = NULL; 

    do
    {
       // system("clear");

        printf("\tWelcome to Banking System\n");
        main_menu();
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            create_account(&customers);
            sleep(2);
            break;
        case 2:
            // update_account();
            break;
        case 3:
            // delete_account();
            break;
        case 4:
            // search_account();
            break;
        case 5:
            // deposit_money();
            break;
        case 6:
            // withdraw_money();
            break;
        case 7:
            view_all_account_details(customers);
            break;
        case 8:
            // view_account_details();
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
    printf("\t| 4. Search Account                |\n");
    printf("\t| 5. Deposit Money                 |\n");
    printf("\t| 6. Withdraw Money                |\n");
    printf("\t| 7. View All Account Details      |\n");
    printf("\t| 8. View Account Details          |\n");
    printf("\t| 9. Save The Account Details      |\n");
    printf("\t| 0. Exit                          |\n");
    printf("\t+----------------------------------+\n");
    printf("\n\tEnter your choice: ");
}