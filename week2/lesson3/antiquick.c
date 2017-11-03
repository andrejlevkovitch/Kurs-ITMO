//antiquick.c

#include <stdio.h>
#include <stdlib.h>

void generation (int masElements [], int first, int last, int *kurrent)
{
    int midle = first + (last - first) / 2;

    masElements [midle] = *kurrent;
    --*kurrent;

    if (midle + 1 != last)
    generation (masElements, midle + 1, last, kurrent);

    if (midle != first)
    generation (masElements, first, midle, kurrent);
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

    int *masElements = malloc (size * sizeof (int));

    generation (masElements, 0, size - 1, kurrent);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (int i = size - 1; i >= 0; --i) {
        if (masElements [i] == 0) 
            masElements [i] = 1;
        fprintf (output, "%i ", masElements [i]);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
