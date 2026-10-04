#define _XOPEN_SOURCE 700   /* must be BEFORE any #include, so strptime is declared */
#include "banking.h"

#define MAX_AGE 120

/* Asks for a date of birth until the user enters a valid one. */
time_t read_dob(const char *prompt)
{
    char line[32];

    for (;;)
    {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin))
            exit(0);                                   /* end of input */
        line[strcspn(line, "\n")] = '\0';

        struct tm tm = {0};
        tm.tm_hour = 12;                               /* avoids daylight-saving edge cases */
        tm.tm_isdst = -1;

        /* 1. Did the text match DD/MM/YYYY, and was ALL of it used? */
        char *end = strptime(line, "%d/%m/%Y", &tm);
        if (end == NULL || *end != '\0')
        {
            puts("Invalid format. Use DD/MM/YYYY (example: 25/12/2000).");
            continue;
        }

        /* 2. Is it a real calendar date? (rejects 31/02/2000) */
        int d = tm.tm_mday, m = tm.tm_mon, y = tm.tm_year;
        time_t t = mktime(&tm);                        /* mktime fixes impossible dates */
        if (t == (time_t)-1 || tm.tm_mday != d || tm.tm_mon != m || tm.tm_year != y)
        {
            puts("That date does not exist. Try again.");
            continue;
        }

        /* 3. Not in the future, and not unrealistically old */
        time_t now = time(NULL);
        if (t > now)
        {
            puts("Date of birth cannot be in the future.");
            continue;
        }
        if (difftime(now, t) > MAX_AGE * 365.25 * 24 * 3600)
        {
            puts("Date of birth is too far in the past.");
            continue;
        }

        return t;
    }
}

/* Returns a random number from the operating system's secure generator. */
unsigned int secure_random(void)
{
    unsigned int value;
    FILE *f = fopen("/dev/urandom", "rb");
    if (f)
    {
        size_t n = fread(&value, sizeof value, 1, f);
        fclose(f);
        if (n == 1)
            return value;
    }
    return (unsigned int)rand();   /* fallback if /dev/urandom is unavailable */
}

int generate_pin(void)
{
    return 1000 + (int)(secure_random() % 9000);   /* 1000 to 9999 */
}

/* Asks for S or C until the user enters one of them. */
AccountType read_account_type(const char *prompt)
{
    char line[16];

    for (;;)
    {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin))
            exit(0);                                   /* end of input */

        line[strcspn(line, "\n")] = '\0';

        /* accept exactly one character: S/s or C/c */
        if (line[1] == '\0')
        {
            char ch = (char)tolower((unsigned char)line[0]);
            if (ch == 's') return SAVINGS;
            if (ch == 'c') return CURRENT;
        }
        puts("Invalid type. Enter S for Savings or C for Current.");
    }
}

/* Throw away whatever is left on the current input line. */
void flush_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Wait for the user to press Enter. */
void pause_screen(void)
{
    printf("\nPress Enter to continue...");
    fflush(stdout);
    flush_line();
}