//merger.c

#include <stdio.h>
#include <stdlib.h>

void merge (FILE *output, int mas [], int left, int midle, int right)
{
    int counterL = 0;
    int counterR = 0;
    int num = 0;
    int n1 = midle - left + 1;
    int n2 = right - midle;

    int *masL = malloc (n1 * sizeof (int));
    int *masR = malloc (n2 * sizeof (int));

    fprintf (output, "%i %i %i %i\n", left + 1, right + 1, mas [left], mas [right]);

    for (unsigned int i = 0; i < n1; ++i) {
        masL [i] = mas [left + i]; 
    }
    for (unsigned int i = 0; i < n2; ++i) {
        masR [i] = mas [midle + 1 + i];
    }

    num = left;
    while (counterL < n1 && counterR < n2) {
        if (masL [counterL] > masR [counterR]) {
            mas [num] = masR [counterR];
            ++counterR;
        }
        else {
            mas [num] = masL [counterL];
            ++counterL;
        }

        ++num;
    }

    if (counterL == n1) {
        for (unsigned int i = 0; i < n2 - counterR; ++i) {
            mas [num + i] = masR [i + counterR];
        }
    }
    else {
        for (unsigned int i = 0; i < n1 - counterL; ++i) {
            mas [num + i] = masL [i + counterL];
        }
    }

//    free (masL);
//    *masL = 0;
//    free (masR);
//    *masR = 0;
}

void mergeSort (FILE *output, int mas [], int left, int right)
{
    int midle = 0;

    if (left < right) {
        midle = left + (right - left) / 2;
        mergeSort (output, mas, left, midle);
        mergeSort (output, mas, midle + 1, right);

        merge (output, mas, left, midle, right);
    }
}

int main (void)
{
    FILE *input;
    FILE *output;
    int nElements = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nElements);

    int *masElements = malloc (nElements * sizeof (int));

    for (unsigned int i = 0; i < nElements; ++i) {
        fscanf (input, "%i", &masElements [i]);
    }
   
    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    mergeSort (output, masElements, 0, nElements - 1);

    for (unsigned int i = 0; i < nElements; ++i) {
        fprintf (output, "%i ", masElements [i]);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

//    free (masElements);
//    *masElements = 0;

    return EXIT_SUCCESS;
}
