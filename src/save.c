/*
 * save.c - saving and loading the bank data
 *
 * All data is stored in ONE binary file: customersDetails.dat
 * It holds every account, PIN and transaction. The program loads this
 * file at start-up and writes it when the user saves or exits.
 *
 * No extra libraries are needed.
 */

#include "banking.h"

#define DATA_FILE  "customersDetails.dat"
#define DATA_TMP   "customersDetails.dat.tmp"
#define DATA_MAGIC "BANK1"            /* first 5 bytes of a valid file */

/* ------------------------------------------------------------------ */
/* Helper: free a whole customer list and all their transactions       */
/* ------------------------------------------------------------------ */
static void free_list(Customer *head)
{
    while (head)
    {
        Customer *next = head->next;

        Transaction *t = head->history_head;
        while (t)
        {
            Transaction *tn = t->next;
            free(t);
            t = tn;
        }

        free(head);
        head = next;
    }
}

/* ------------------------------------------------------------------ */
/* SAVE: write everything to the .dat file                              */
/* Returns 1 on success, 0 on failure. Works with an empty list too.   */
/*                                                                     */
/* File layout:                                                        */
/*   BANK1 | count | [Customer | n | Transaction x n] ...              */
/* ------------------------------------------------------------------ */
int save_data_file(Customer *customers)
{
    /* Write to a temporary file first. If anything fails, the old
       data file is still untouched. */
    FILE *f = fopen(DATA_TMP, "wb");
    if (!f)
        return 0;

    unsigned long count = 0;
    for (Customer *c = customers; c; c = c->next)
        count++;

    int ok = fwrite(DATA_MAGIC, 1, 5, f) == 5 &&
             fwrite(&count, sizeof count, 1, f) == 1;

    for (Customer *c = customers; ok && c; c = c->next)
    {
        /* Pointers are meaningless on disk, so save a copy with them blanked */
        Customer copy = *c;
        copy.next = NULL;
        copy.history_head = NULL;

        unsigned long n = 0;
        for (Transaction *t = c->history_head; t; t = t->next)
            n++;

        ok = fwrite(&copy, sizeof copy, 1, f) == 1 &&
             fwrite(&n, sizeof n, 1, f) == 1;

        for (Transaction *t = c->history_head; ok && t; t = t->next)
        {
            Transaction tc = *t;
            tc.next = NULL;
            ok = fwrite(&tc, sizeof tc, 1, f) == 1;
        }
    }

    if (fclose(f) != 0)
        ok = 0;

    if (!ok)
    {
        remove(DATA_TMP);              /* discard the half-written file */
        return 0;
    }

    /* Replace the old file with the new one in a single step.
       (On Windows, call remove(DATA_FILE) before rename.) */
    return rename(DATA_TMP, DATA_FILE) == 0;
}

/* ------------------------------------------------------------------ */
/* LOAD: rebuild the linked list from the .dat file                      */
/* Returns the list, or NULL on first run / damaged file.              */
/* ------------------------------------------------------------------ */
Customer *load_account_details(void)
{
    FILE *f = fopen(DATA_FILE, "rb");
    if (!f)
        return NULL;                   /* first run: nothing to load */

    Customer *head = NULL, *tail = NULL;
    char magic[5];
    unsigned long count;

    /* Check that this really is our file */
    if (fread(magic, 1, 5, f) != 5 || memcmp(magic, DATA_MAGIC, 5) != 0 ||
        fread(&count, sizeof count, 1, f) != 1)
        goto bad;

    for (unsigned long i = 0; i < count; i++)
    {
        Customer *c = calloc(1, sizeof *c);
        if (!c)
            goto bad;

        unsigned long n;               /* how many transactions follow */
        if (fread(c, sizeof *c, 1, f) != 1 || fread(&n, sizeof n, 1, f) != 1)
        {
            free(c);
            goto bad;
        }

        /* Pointers read from disk point to old memory - wipe them */
        c->next = NULL;
        c->history_head = NULL;

        /* Link the customer into the list BEFORE reading its transactions,
           so free_list() can clean it up if something fails below. */
        if (tail) tail->next = c; else head = c;
        tail = c;

        Transaction *ttail = NULL;
        for (unsigned long j = 0; j < n; j++)
        {
            Transaction *t = calloc(1, sizeof *t);
            if (!t)
                goto bad;

            if (fread(t, sizeof *t, 1, f) != 1)
            {
                free(t);
                goto bad;
            }

            t->next = NULL;
            if (ttail) ttail->next = t; else c->history_head = t;
            ttail = t;
        }
    }

    fclose(f);
    return head;

bad:                                   /* one shared clean-up for every error */
    fclose(f);
    free_list(head);
    rename(DATA_FILE, DATA_FILE ".bad");   /* keep the damaged file for inspection */
    fprintf(stderr, "Warning: %s was damaged. Saved as %s.bad. Starting empty.\n",
            DATA_FILE, DATA_FILE);
    return NULL;
}

/* ------------------------------------------------------------------ */
/* Called from the menu (option 9) and on exit                         */
/* ------------------------------------------------------------------ */
void save_account_details(Customer *customers)
{
    if (!save_data_file(customers))
    {
        fprintf(stderr, "Error: could not save %s. Your data was NOT saved.\n", DATA_FILE);
        return;
    }

    printf("Data saved to %s\n", DATA_FILE);
}