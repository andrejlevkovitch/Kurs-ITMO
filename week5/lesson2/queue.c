//queue.c

#include <stdio.h>
#include <stdlib.h>

void restoring (int array [], int num);
void heapify (int array [], int num, int lenght);

int main (void)
{
    FILE *input;
    FILE *output;

    int nOperace;

    int *array = NULL;
    int *pile = NULL;

    int num = 0, temp = 0;
    int last = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nOperace);

    while (getc (input) != '\n')
        continue;

    array = malloc (nOperace * sizeof *array);
    pile = malloc (nOperace * sizeof *pile);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nOperace; ++i) {
        switch (getc (input)) {
            case 'A':
                fscanf (input, "%i", &pile [last]);
                array [i] = pile [last];
                last++;
                restoring (pile, last - 1);
                break;
            case 'X':
                if (last) {
                    fprintf (output, "%i\n", pile [0]);
                    pile [0] = pile [last - 1];
                    last--;
                }
                else {
                    fprintf (output, "*\n");
                }
                break;
            case 'D':
                fscanf (input, "%i %i", &num, &temp);
                for (unsigned int j = 0; j < last; ++j) {
                    if (pile [j] == array [num - 1]) {
                        array [num - 1] = temp;
                        pile [j] = temp;
                        restoring (pile, j);
                        break;
                    }
                }
                break;
        }

        while (getc (input) != '\n')
            continue;
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void restoring (int array [], int num)
{
    int leas = 0;
    int temp = 0;

    leas = (num - 1) / 2;

    if (array [leas] > array [num]) {
        temp = array [num];
        array [num] = array [leas];
        array [leas] = temp;

        restoring (array, leas);
    }

    return;
}

void heapify (int array [], int num, int lenght)
{
    int left = 0, right = 0;
    int leas = 0;
    int temp = 0;

    left = 2 * num + 1;
    right = 2 * num + 2;
    leas = num;

    if (left < lenght && array [left] < array [leas])
        leas = left;
    if (right < lenght && array [right] < array [leas])
        leas = right;

    if (leas != num) {
        temp = array [num];
        array [num] = array [leas];
        array [leas] = temp;

        heapify (array, leas, lenght);
    }

    return;
}
