//antiquick.c

#include <stdio.h>
#include <stdlib.h>

void generation (int masElements [], int anti [], int first, int last, int *kurrent)
{
    int left = first;
    int right = last;
    int midle = (left + right) / 2;
    int temp = 0;

    if (masElements [midle] == 1) {
        midle = masElements [midle] = *kurrent;
        --*kurrent;
    }

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

            temp = anti [left];
            anti [left] = anti [right];
            anti [right] = temp;

            ++left;
            --right;
        }
    }

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
        anti [i] = size - 1 - i;
    }

    generation (masElements, anti, 0, size - 1, kurrent);

    for (unsigned int i = 0; i < size; ++i) {
        rezult [i] = masElements [anti [i]];
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

//    if (size == 4) {
  //      fprintf (output, "3 4 1 2");
 //   }
//    else {
    for (unsigned int i = 0; i < size; ++i) {
        fprintf (output, "%i ", rezult [i]);
    }
//    }
    
    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
