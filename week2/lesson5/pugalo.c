//pugalo.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void qusort (int masElements [], int first, int last, int line)
{
    int left = first;
    int right = last;
    int midle = masElements [right];
    int temp = 0;

    while (left <= right) {
        while (masElements [left] < midle) {
            left += line;
        }

        while (masElements [right] > midle) {
            right -= line;
        }

        if (left <= right) {
            temp = masElements [left];
            masElements [left] = masElements [right];
            masElements [right] = temp;
            left += line;
            right -= line;
        }
    }

    if (first < right) {
        qusort (masElements, first, right, line);
    }

    if (last > left) {
        qusort (masElements, left, last, line);
    }
}

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int line = 0;
    bool rezult = true;
    int finEl = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %i", &size, &line);

    int *matrosxka = malloc (size * sizeof (*matrosxka));

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &matrosxka [i]);
    }
    
    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < line; ++i) {
        if ((i + line) >= size)
            break;
        finEl = ((size - 1) / line) * line + i;
        if (finEl >= size)
            finEl -= line;
        qusort (matrosxka, i, finEl, line);
    }

    for (unsigned int i = 1; i < size; ++i) {
        if (matrosxka [i] < matrosxka [i - 1]) {
            rezult = false;
            break;
        }
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    if (rezult)
        fprintf (output, "YES");
    else
        fprintf (output, "NO");
    
    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
