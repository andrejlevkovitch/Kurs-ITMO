//ssort_dop.c

#include <stdio.h>
#include <stdlib.h>

#define LENGTH ('z' - 'a' + 1)

int main (void)
{
    FILE *input;
    FILE *output;
    int nArr = 0;
    int size = 0;
    int nCikle = 0;
    int numS = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %i %i", &nArr, &size, &nCikle);
    while (getc (input) != '\n')
        continue;

    char charArray [size][nArr];

    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < nArr; ++j) {
            charArray [i][j] = getc (input);
        }

        while (getc (input) != '\n')
            continue;
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    int countArray [LENGTH];
    int stringArray [nArr];
    int rezult [nArr];

    for (unsigned int i = 0; i < nArr; ++i) {
        stringArray [i] = i;
    }

    numS = size - 1;

    for (unsigned int l = 0; l < nCikle; ++l) {
        for (unsigned int i = 0; i < LENGTH; ++i) {
            countArray [i] = 0;
        }
        for (unsigned int i = 0; i < nArr; ++i) {
            countArray [charArray [numS][stringArray [i]] - 'a'] += 1;
        }
        for (unsigned int i = 1; i < LENGTH; ++i) {
            countArray [i] += countArray [i - 1];
        }
        for (signed int i = nArr - 1; i >= 0; --i) {
            countArray [charArray [numS][stringArray [i]] - 'a'] -= 1;
            rezult [countArray [charArray [numS][stringArray [i]] - 'a']] = stringArray [i];
        }
        for (unsigned int i = 0; i < nArr; ++i) {
            stringArray [i] = rezult [i];
        }

        --numS;
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nArr; ++i) {
        fprintf (output, "%i ", stringArray [i] + 1);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
