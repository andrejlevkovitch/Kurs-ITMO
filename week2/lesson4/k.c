//k.c

#include <stdio.h>
#include <stdlib.h>

void qusort (int masElements [], int first, int last, int k1, int k2)
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

    if (first < right && right >= k1) {
        qusort (masElements, first, right, k1, k2);
    }

    if (last > left && left <= k2) {
        qusort (masElements, left, last, k1, k2);
    }
}

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int k1 = 0, k2 = 0;
    int A = 0, B = 0, C = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }
    
    fscanf (input, "%i %i %i", &size, &k1, &k2);

    int *array = malloc (size * sizeof (*array));

    fscanf (input, "%i %i %i %i %i", &A, &B, &C, &array [0], &array [1]);

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 2; i < size; ++i) {
        array [i] = A * array [i - 2] + B * array [i - 1] + C;
    }

    qusort (array, 0, size - 1, k1 - 1, k2 - 1);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = k1 - 1; i < k2; ++i) {
        fprintf (output, "%i ", array [i]);
    }
    
    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
