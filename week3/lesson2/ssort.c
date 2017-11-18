//ssort.c

#include <stdio.h>
#include <stdlib.h>

#define LENGTH ('z' - 'a' + 1)

int main (void)
{
    FILE *input;
    FILE *output;
    char *charArray = NULL;
    int nArr = 0;
    int size = 0;
    int nCikle = 0;
    int *countArray = NULL;
    int *stringArray = NULL;
    int *rezult = NULL;
    int numS = 0;
    char temp = 0;
    int num = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %i %i", &nArr, &size, &nCikle);

    charArray = malloc (nArr * size * sizeof *charArray);

/*    for (unsigned int i = 0; i < size; ++i) {//не знаю почему, но при такой форме записи наблюдаются вылеты при nArr = 20, size = 10
        fscanf (input, "%s", &charArray [i * nArr]);
    }
*/

    num = 0;
    while ((temp = getc (input)) != EOF) {
        if (temp != '\n') {
            charArray [num] = temp;
            num++;
        }
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    countArray = malloc (LENGTH * sizeof *countArray);

    stringArray = malloc (nArr * sizeof *stringArray);
    rezult = malloc (nArr * sizeof *rezult);

    for (unsigned int i = 0; i < nArr; ++i) {
        stringArray [i] = i;
    }

    numS = size - 1;

    for (unsigned int l = 0; l < nCikle; ++l) {
        for (unsigned int i = 0; i < LENGTH; ++i) {
            countArray [i] = 0;
        }
        for (unsigned int i = 0; i < nArr; ++i) {
            countArray [charArray [numS * nArr + stringArray [i]] - 'a'] += 1;
        }
        for (unsigned int i = 1; i < LENGTH; ++i) {
            countArray [i] += countArray [i - 1];
        }
        for (signed int i = nArr - 1; i >= 0; --i) {
            countArray [charArray [numS * nArr + stringArray [i]] - 'a'] -= 1;
            rezult [countArray [charArray [numS * nArr + stringArray [i]] - 'a']] = stringArray [i];
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
