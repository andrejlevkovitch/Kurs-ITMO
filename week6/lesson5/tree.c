//tree.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define colum 3

bool inEl (int *array, int i, int size);

int main (void)
{
    FILE *input;
    FILE *output;
    int *array = NULL;
    int size = 0;
    bool umova = true;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * 3 * sizeof *array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i %i %i", &array [i * colum], &array [i * colum + 1], &array [i * colum + 2]); 
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if (size) {
        if (size > 1) {
            umova = inEl (array, 1, array [0]);
        }
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    if (umova)
        fprintf (output, "YES");
    else
        fprintf (output, "NO");

    if (fclose (output ) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

bool inEl (int *array, int i, int parent)
{
    int child = 0;
    bool umova = true;

    if (array [i]) {//если левый ребенок существует
        child = array [(array [i] - 1) * colum];
        if (child >= parent)
            return false;
        else
            umova = inEl (array, (array [i] - 1) * colum + 1, child);
    }

    if (array [i + 1]) {//если правый ребенок сеществует
        child = array [(array [i + 1] - 1) * colum];
        if (child <= parent)
            return false;
        else
            umova = inEl (array, (array [i + 1] - 1) * colum + 1, child);
    }

    if (!umova)
        return false;
    else
        return true;
}
