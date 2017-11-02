//sortland.c

#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int main (void)
{
    FILE *inFile;
    FILE *outFile;
    unsigned short nIdent = 0;
    unsigned short ident = 0;
    float key = 0;

    if ((inFile = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (inFile, "%hu", &nIdent);

    float *masElements = malloc (nIdent * sizeof *masElements);
    unsigned short *masIdent = malloc (nIdent * sizeof *masIdent);

    for (unsigned int i = 0; i < nIdent; ++i) {
        fscanf (inFile, "%f", &masElements [i]); 
        masIdent [i] = i + 1;
    }

    if (fclose (inFile) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 1; i < nIdent; ++i) {
        key = masElements [i];
        ident = masIdent [i];
        for (unsigned int j = 0; j < i; ++j) {
            if (key < masElements [j]) {
                for (unsigned int l = i; l > j; --l) {
                    masElements [l] = masElements [l - 1];
                    masIdent [l] = masIdent [l - 1];
                }

                masElements [j] = key;
                masIdent [j] = ident;
                break;
            }
        }
    }

    if ((outFile = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (outFile, "%hu ", masIdent [0]);
    fprintf (outFile, "%hu ", masIdent [nIdent / 2]);
    fprintf (outFile, "%hu", masIdent [nIdent - 1]);
    
    if (fclose (outFile) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

//    free (masElements);
//    *masElements = 0;
//    free (masIdent);
//    *masIdent = 0;

    return EXIT_SUCCESS;
}
