//swap.c

#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *inFile;
    FILE *outFile;
    unsigned short nElements = 0;
    int key = 0;
    unsigned short index = 0;

    if ((inFile = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }
    
    fscanf (inFile, "%hu", &nElements);

    int *masElements = malloc (nElements * sizeof *masElements);

    for (unsigned int i = 0; i < nElements; ++i) {
        fscanf (inFile, "%i", &masElements [i]);
    }

    if (fclose (inFile) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if ((outFile = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }
    
    for (unsigned int i = 0; i < nElements; ++i) {
        key = masElements [i];
        index = i;

        for (unsigned int j = i + 1; j < nElements; ++j) {
            if (key > masElements [j]) {
                key = masElements [j];
                index = j;
            }

            if (i != 0 && masElements [i - 1] == key) break;
        }

        if (index != i) {
            masElements [index] = masElements [i];
            masElements [i] = key;
            fprintf (outFile, "Swap elements at indices %i and %hu.\n", i + 1, index + 1);
        }
    }

    fprintf (outFile, "No more swaps needed.\n");
    for (unsigned int i = 0; i < nElements; ++i) {
        fprintf (outFile, "%i ", masElements [i]);
    }

    if (fclose (outFile) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
