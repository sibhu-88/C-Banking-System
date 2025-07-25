#include "banking.h"

void view_all_account_details(Customer *customers)
{
    if (!customers)
    {
        printf("\nNo customer records found.\n");
        return;
    }

    while (customers) print_account_details(customers);

    printf("Press Any Key to Return Back:");
    getchar();
    getchar();
}

void print_account_details(Customer *customer) {
    char dob_buffer[20];
    char open_buffer[20];
    
    strftime(dob_buffer, sizeof(dob_buffer), "%d/%m/%Y", localtime(&customer->dob));
    strftime(open_buffer, sizeof(open_buffer), "%d/%m/%Y %H:%M:%S", localtime(&customer->opening_date));

    printf("\n+--------------------- ACCOUNT DETAILS ---------------------+\n");
    printf("| %-20s | %-32ld |\n", "Account Number:", customer->account_number);
    printf("| %-20s | %-32s |\n", "Customer Name:", customer->holder_name);
    printf("| %-20s | %-32s |\n", "Account Type:", 
          customer->type == SAVINGS ? "SAVINGS" : "CURRENT");
    printf("| %-20s | $%-31.2f |\n", "Balance:", customer->balance);
    printf("| %-20s | %-32s |\n", "Date of Birth:", dob_buffer);
    printf("| %-20s | %-32s |\n", "Contact Number:", customer->phone_number);
    printf("| %-20s | %-32s |\n", "Email:", customer->email);
    printf("| %-20s | %-32s |\n", "Address:", customer->holder_address);
    printf("| %-20s | %-32s |\n", "Account Opened:", open_buffer);
    printf("| %-20s | %-32d |\n", "PIN:", customer->pin);
    printf("+---------------------+------------------------------------+\n");
}