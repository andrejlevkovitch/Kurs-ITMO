//sort.c

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 256

void countSort (int array [], int size, int maxElement);

int main (void)
{
    FILE *input;
    FILE *output;
    int size1 = 0, size2 = 0;
    int *array1 = NULL, *array2 = NULL;
    int maxElement = 0;
    long long count = 0;
    int *global = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %i", &size1, &size2);

    array1 = malloc (size1 * sizeof *array1);
    array2 = malloc (size2 * sizeof *array2);

    for (unsigned int i = 0; i < size1; ++i) {
        fscanf (input, "%i", &array1 [i]);
    }
    for (unsigned int i = 0; i < size2; ++i) {
        fscanf (input, "%i", &array2 [i]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    global = malloc (size1 * size2 * sizeof *global);

    for (unsigned int i = 0; i < size1; ++i) {
        for (unsigned int j = 0; j < size2; ++j) {
            global [i * size2 + j] = array1 [i] * array2 [j];
            if (maxElement < global [i * size2 + j])
                maxElement = global [i * size2 + j];
        }
    }

    countSort (global, size1 * size2, maxElement);

    for (unsigned int i = 0; i < size1 * size2; i += 10) {
        count += global [i];
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (output, "%lli", count);

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void countSort (int array [], int size, int maxElement)
{
    int countArray [LENGTH] = {};//используются десятичные разряды
    unsigned char *temp = NULL;
    int *rezult = NULL;

    rezult = malloc (size * sizeof *rezult);

    for (unsigned int l = 0; l < sizeof *array; ++l) {
        for (unsigned int i = 0; i < LENGTH; ++i) {
            countArray [i] = 0;//обнуляем все элементы, чтобы избавится от мусора
        }
        for (unsigned int i = 0; i < size; ++i) {
            temp = (long long) &array [i] + (long long) l;
            countArray [*temp] += 1;//подсчитываем сколько таких элементов в массиве
        }
        for (unsigned int i = 1; i < LENGTH; ++i) {
            countArray [i] += countArray [i - 1];//подсчитываем на каком месте должны стоять элементы
        }
        for (signed int i = size - 1; i >= 0; --i) {
            temp = (long long) &array [i] + (long long) l;
            countArray [*temp] -= 1;//поскольку место отсчитывается от 1 а не от 0, сначала уменшаем индекс
            rezult [countArray [*temp]] = array [i];//и ставим элемент на нужное место в массиве
        }
        for (unsigned int i = 0; i < size; ++i) {
            array [i] = rezult [i];
        }
    }
}
