//antiquick.c

#include <stdio.h>
#include <stdlib.h>

void generation (int masElements [], int anti [], int first, int last, int *kurrent)
{
    int left = first;
    int right = last;
    int midle = (left + right) / 2;
    if (right - left == 1) {
        ++midle;
    }
    int temp = 0;

    if (masElements [midle] == 1) {
        masElements [midle] = *kurrent;
        --*kurrent;
    }

    temp = masElements [midle];
    masElements [midle] = masElements [right];
    masElements [right] = temp;

    temp = anti [midle];
    anti [midle] = anti [right];
    anti [right] = temp;

    left = right;
    --right;

/*    left = midle;
    while (left <= right) {
        while (masElements [left] < *kurrent) {
            ++left;
        }

        while (masElements [right] > *kurrent) {
            --right;
        }

        if (left <= right) {
            temp = masElements [left];
            masElements [left] = masElements [right];
            masElements [right] = temp;

            temp = anti [left];
            anti [left] = anti [right];
            anti [right] = temp;

            ++left;
            --right;
        }
    }*/

    if (first < right) {
        generation (masElements, anti, first, right, kurrent);
    }

    if (last > left) {
        generation (masElements, anti, left, last, kurrent);
    }
}

int main (void)
{
    FILE *input;
    FILE *output;
    int size = 0;
    int num = 0;
    int *kurrent = &num;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }
    
    fscanf (input, "%i", &size);
    *kurrent = size;
    
    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    int *masElements = malloc (size * sizeof (*masElements));
    int *rezult = malloc (size * sizeof (*rezult));

    for (unsigned int i = 0; i < size; ++i) {
        masElements [i] = 1;
    }

    int *anti = malloc (size * sizeof (*anti));

    for (unsigned int i = 0; i < size; ++i) {
        anti [i] = i;
    }

    generation (masElements, anti, 0, size - 1, kurrent);

    for (unsigned int i = 0; i < size; ++i) {
        rezult [anti [i]] = masElements [i];
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < size; ++i) {
        fprintf (output, "%i ", rezult [i]);
    }
    
    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
