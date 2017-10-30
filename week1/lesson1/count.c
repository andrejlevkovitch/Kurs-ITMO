//count.c

#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *inFile;
    int digit1 = 0, digit2 = 0;
    int rezult = 0;

    if ((inFile = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (inFile, "%i", &digit1);
    fscanf (inFile, "%i", &digit2);

    if (fclose (inFile) != 0) {
        printf ("Error of exit input.txt\n");
    }

    if (digit1 > 1000000000 || digit2 > 1000000000 || digit1 < -1000000000 || digit2 < -1000000000) {
        printf ("Error, it too big numbers!");
        exit (EXIT_FAILURE);
    }

    rezult = digit1 + digit2;

    FILE *outFile;

    if ((outFile = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (outFile, "%i", rezult);

    if (fclose (outFile) != 0) {
        printf ("Error of exit outfile.txt\n");
    }

    return EXIT_SUCCESS;
}
