//hesh.c

#include <stdio.h>
#include <stdlib.h>

#define MOD 999983

struct list {
    struct list *next;
    struct list *prev;
    long long info;
};

int heshing (long long);
struct list *new_l (long long);
struct list *search (struct list *, long long);
struct list *insert (struct list *, long long);
struct list *rm (struct list *, struct list *);
struct list *del_list (struct list *d_list);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;
    struct list *hesh [MOD] = {};
    int size = 0;
    long long temp = 0;
    int k = 0;
    struct list *h_list = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }
    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    for (int i = 0; i < size; ++i) {
        while (getc (input) != '\n')
            continue;

        switch (getc (input)) {
            case 'A':
                fscanf (input, "%lli", &temp);
                k = heshing (temp);
                if (!search (hesh [k], temp)) {
                    hesh [k] = insert (hesh [k], temp);
                }

                break;
            case 'D':
                fscanf (input, "%lli", &temp);
                k = heshing (temp);
                if ((h_list = search (hesh [k], temp))) {
                    hesh [k] = rm (h_list, hesh [k]);
                }

                break;
            case '?':
                fscanf (input, "%lli", &temp);
                k = heshing (temp);
                if (!search (hesh [k], temp)) {
                    fprintf (output, "N\n");
                }
                else
                    fprintf (output, "Y\n");

                break;
        }
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }
    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (int i = 0; i < MOD; ++i) {
        hesh [i] = del_list (hesh [i]);
    }

    return EXIT_SUCCESS;
}

struct list *del_list (struct list *d_list)
{
    struct list *h_list = NULL;

    while (d_list) {
        h_list = d_list->next;
        free (d_list);
        d_list = NULL;
    }

    return d_list;
}

int heshing (long long a)
{
    return llabs (a % MOD);
}

struct list *new_l (long long value)
{
    struct list *new = malloc (sizeof *new);
    new->next = NULL;
    new->prev = NULL;
    new->info = value;

    return new;
}

struct list *search (struct list *s_list, long long value)
{
    while (s_list) {
        if (s_list->info == value)
            break;
        else
            s_list = s_list->next;
    }

    return s_list;
}

struct list *insert (struct list *i_list, long long value)
{
    struct list *h_list = new_l (value);

    h_list->next = i_list;
    if (i_list)
        i_list->prev = h_list;

    return h_list;
}

struct list *rm (struct list *r_list, struct list *array)
{
    if (r_list->next)
        r_list->next->prev = r_list->prev;

    if (r_list->prev)
        r_list->prev->next = r_list->next;
    else
        array = r_list->next;

    free (r_list);

    return array;
}
