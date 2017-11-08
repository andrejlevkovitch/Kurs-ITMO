//sort.c

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void quick (int array [], int first, int last);

int main (void)
{
    FILE *input;
    FILE *output;
    int size1 = 0, size2 = 0;
    long long rezult = 0;
    int *array1 = NULL, *array2 = NULL;
    int *factor1 = NULL, *factor2 = NULL;
    int *countArr = NULL;
    int max = INT_MIN, min = INT_MAX;
    int *help1 = NULL, *help2 = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %i", &size1, &size2);

    array1 = malloc (size1 * sizeof *array1);
    array2 = malloc (size2 * sizeof *array2);

    for (unsigned int i = 0; i < size1; ++i) {
        fscanf (input, "%i", &array1 [i]);
        if (array1 [i] < min)
            min = array1 [i];
        else
            if (array1 [i] > max)
                max = array1 [i];
    }
    for (unsigned int i = 0; i < size2; ++i) {
        fscanf (input, "%i", &array2 [i]);
        if (array2 [i] < min)
            min = array2 [i];
        else
            if (array2 [i] > max)
                max = array2 [i];
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    factor1 = malloc (size1 * size2 * sizeof *factor1);
    factor2 = malloc (size1 * size2 * sizeof *factor2);
    help1 = malloc (size1 * size2 * sizeof *help1);
    help2 = malloc (size1 * size2 * sizeof *help2);

    for (unsigned int i = 0; i < size1; ++i) {
        for (unsigned int j = 0; j < size2; ++j) {
            if (array1 [i] > array2 [j]) {
                factor1 [i * size2 + j] = array1 [i];
                factor2 [i * size2 + j] = array2 [j];
            }
            else {
                factor1 [i * size2 + j] = array2 [j];
                factor2 [i * size2 + j] = array1 [i];
            }
        }
    }

    countArr = malloc ((max + 1 - min) * sizeof *countArr);

    for (unsigned int i = 0; i < max + 1 - min; ++i) {
        countArr [i] = 0;
    }
    for (unsigned int i = 0; i < size1 * size2; ++i) {
        countArr [factor1 [i] - min] += 1;
    }
    for (unsigned int i = 1; i < max + 1 - min; ++i) {
        countArr [i] += countArr [i - 1];
    }
    for (signed int i = size1 * size2 - 1; i >= 0; --i) {
        countArr [factor1 [i] - min] -= 1;
        help1 [countArr [factor1 [i] - min]] = factor1 [i];
        help2 [countArr [factor1 [i] - min]] = factor2 [i];
    }

    for (unsigned int i = 0; i < max + 1 - min; ++i) {
        countArr [i] = 0;
    }
    for (unsigned int i = 0; i < size1 * size2; ++i) {
        countArr [help2 [i] - min] += 1;
    }
    for (unsigned int i = 1; i < max + 1 - min; ++i) {
        countArr [i] += countArr [i - 1];
    }
    for (signed int i = size1 * size2 - 1; i >= 0; --i) {
        countArr [help2 [i] - min] -= 1;
        factor1 [countArr [help2 [i] - min]] = help1 [i];
        factor2 [countArr [help2 [i] - min]] = help2 [i];
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < size1 * size2; i += 10) {
        if (i != 0 && factor1 [i - 1] * factor2 [i - 1] > factor1 [i] * factor2 [i]) {
            factor1 [i] = factor1 [i - 1];
            factor2 [i] = factor2 [i - 1];
        }
//        else
        if (i != (size1 * size2 - 1) && factor1 [i + 1] * factor2 [i + 1] < factor1 [i] * factor2 [i]) {
            factor1 [i] = factor1 [i + 1];
            factor2 [i] = factor2 [i + 1];
        }

        rezult += factor1 [i] * factor2 [i];
    }

    fprintf (output, "%lli", rezult);

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
