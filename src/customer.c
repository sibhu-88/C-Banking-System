#include "banking.h"

int accountExists(Customer *customers, long int accountNumber)
{
    Customer *current = customers;
    while (current)
    {
        if (current->account_number == accountNumber) return 1;
        current = current->next;
    }
    return 0;
}

long int accountGenerate(Customer *customers)
{
    srand(time(0));
    long int accountNumber;
    do
    {
        accountNumber = 626001;
        for (int i = 0; i < 10; i++) accountNumber = accountNumber * 10 + (rand() % 10);
    } while (accountExists(customers, accountNumber));

    return accountNumber;
}

int generate_pin()
{
    srand(time(0) + rand());
    int pin = 0;
    for (int i = 0; i < 4; i++) pin = pin * 10 + (rand() % 10);
    return pin;
}

void create_account(Customer **customers)
{
    //system("clear");
    Customer *newAccount = (Customer *)malloc(sizeof(Customer));
    if (!newAccount)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newAccount->next = NULL;

    newAccount->account_number = accountGenerate(*customers);
    newAccount->pin = generate_pin();

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

    if (type == 'S' || type == 's') newAccount->type = SAVINGS;
    else if (type == 'C' || type == 'c') newAccount->type = CURRENT;
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

    if (!*customers) *customers = newAccount;
    else
    {
        Customer *current = *customers;
        while (current->next) current = current->next;
        current->next = newAccount;
    }

    // system("clear");

    printf("Account created successfully!\n");
    print_account_details(newAccount);

}
