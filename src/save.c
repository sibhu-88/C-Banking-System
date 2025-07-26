#include "banking.h"

void save_account_details(Customer *customers)
{
    if (!customers)
    {
        fprintf(stderr, "Error: No Records Found!...\n");
        sleep(2);
        return;
    }

    FILE *file = fopen("customersDetails.csv", "w");  // Use .csv as easier to open in Excel
    if (!file)
    {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    fprintf(file, "Account Number,Name,Address,Phone,Email,Account Type,Balance,Date of Birth,Opening Date\n");

    Customer *current = customers;
    while (current != NULL)
    {
        char dob_str[20], opening_str[20];
        struct tm *tm_info;

        tm_info = localtime(&current->dob);
        strftime(dob_str, sizeof(dob_str), "%Y-%m-%d", tm_info);

        tm_info = localtime(&current->opening_date);
        strftime(opening_str, sizeof(opening_str), "%Y-%m-%d", tm_info);

        const char *account_type_str;
        switch (current->type)
        {
            case SAVINGS: account_type_str = "Savings"; break;
            case CURRENT: account_type_str = "Current"; break;
            default: account_type_str = "Unknown"; break;
        }

        fprintf(file, "%lu,\"%s\",\"%s\",\"%s\",\"%s\",%s,%.2lf,%s,%s\n",
                current->account_number,
                current->holder_name,
                current->holder_address,
                current->phone_number,
                current->email,
                account_type_str,
                current->balance,
                dob_str,
                opening_str);

        current = current->next;
    }

    fclose(file);
    printf("Customer account details saved successfully to customersDetails.csv\n");
}
