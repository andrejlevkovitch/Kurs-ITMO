//search.c

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int main (void)
{
    FILE *input;
    FILE *output;
    int *enq = NULL;
    int nOperace = 0;
    int size = 0;
    int head = 0, tail = 0;
    bool egan = true;

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
                tail++;
                egan = true;
                break;
            case '-':
                head++;
                break;
            case '?':
                if (egan) {
                    for (signed int i = tail - 1; i >= head; --i) {
                        if (enq [i] < enq [i - 1])
                            enq [i - 1] = enq [i];
                    }
                    egan = false;
                }
                fprintf (output, "%i\n", enq [head]);
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
