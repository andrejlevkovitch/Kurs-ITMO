//sort.c

#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *inFile;
    FILE *outFile;
    unsigned short nElements = 0;
    int key = 0;

    if ((inFile = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }
    
    fscanf (inFile, "%hu", &nElements);

    if (nElements == 0 || nElements > 1000) {
        printf ("ERROR not passible digit!\n");
        exit (EXIT_FAILURE);
    }

    int *masElements = malloc (nElements * sizeof (int));
    int *masIndex = malloc (nElements * sizeof (int));

    for (unsigned int i = 0; i < nElements; ++i) {
        fscanf (inFile, "%i", &masElements [i]);
    }

    if (fclose (inFile) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    masIndex [0] = 1;
    for (unsigned int i = 1; i < nElements; ++i) {
        key = masElements [i];
        for (unsigned int j = 0; j < i; ++j) {
            if (key < masElements [j]) {
                for (unsigned int l = i; l > j; --l) {
                    masElements [l] = masElements [l - 1];
                }

                masElements [j] = key;
                masIndex [i] = j + 1;

                break;
            }

            if ((i - j) == 1) {
                masIndex [i] = j + 2;
            }
        }
    }

    if ((outFile = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nElements; ++i) {
        fprintf (outFile, "%i ", masIndex [i]);
    }

    fprintf (outFile, "\n");

    for (unsigned int i = 0; i < nElements; ++i) {
        fprintf (outFile, "%i ", masElements [i]);
    }

    if (fclose (outFile) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    free (masElements);
    *masElements = 0;
    free (masIndex);
    *masIndex = 0;

    return EXIT_SUCCESS;
}
