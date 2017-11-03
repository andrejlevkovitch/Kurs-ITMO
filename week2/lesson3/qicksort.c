//quicksort.c

#include <stdio.h>
#include <stdlib.h>

void qusort (int masElements [], int first, int last)
{
    int left = first;
    int right = last;
    int midle = masElements [(left + right) / 2];
    int temp = 0;

    while (left <= right) {
        while (masElements [left] < midle) {
            ++left;
        }

        while (masElements [right] > midle) {
            --right;
        }

        if (left <= right) {
            temp = masElements [left];
            masElements [left] = masElements [right];
            masElements [right] = temp;
            ++left;
            --right;
        }
    }

    if (first < right) {
        qusort (masElements, first, right);
    }

    if (last > left) {
        qusort (masElements, left, last);
    }
}

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    int *masElements = malloc (size * sizeof (*masElements));

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &masElements [i]);
    }
    
    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    qusort (masElements, 0, size - 1);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }
    
    for (unsigned int i = 0; i < size; ++i) {
        fprintf (output, "%i ", masElements [i]);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
