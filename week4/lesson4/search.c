//search.c

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (void)
{
    FILE *input;
    FILE *output;
    int *enq = NULL;
    int nOperace = 0;
    int size = 0;
    int head = 0, tail = 0;
    int minElement = 0;
    int koordME = -1;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nOperace);
    size = nOperace;

    enq = malloc (size * sizeof *enq);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nOperace; ++i) {
        while (getc (input) != '\n')
            continue;
        switch (getc (input)) {
            case '+':
                fscanf (input, "%i", &enq [tail]);
                if (minElement > enq [tail]) {
                    minElement = enq [tail];
                    koordME = tail;
                }
                tail++;
                break;
            case '-':
                head++;
                break;
            case '?':
                if (koordME < head || koordME < 0) {
                    minElement = INT_MAX;
                    for (signed int j = head; j < tail; ++j) {
                        if (minElement > enq [j]) {
                            minElement = enq [j];
                            koordME = j;
                        }
                    }
                }
                fprintf (output, "%i\n", minElement);
                break;
        }
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
