//pile.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int *array = NULL;
    bool pile = true;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * sizeof *array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &array [i]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 1; i <= size; ++i) {
        if (2 * i <= size) {
            if (array [i - 1] > array [2 * i - 1])
                pile = false;
        }
        if (2 * i + 1 <= size) {
            if (array [i - 1] > array [2 * i])
                pile = false;
        }
        if (!pile)
            break;
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    if (pile)
        fprintf (output, "%s", "YES");
    if (!pile)
        fprintf (output, "%s", "NO");

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
