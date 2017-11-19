//enqueue.c

#include <stdio.h>
#include <stdlib.h>

#define maxSize 1000000

int main (void)
{
    FILE *input;
    FILE *output;
    int *enq= NULL;
    int nOrders;
    int size = 0;
    int tail = 0;
    int head = 0;
    char operacia = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nOrders);

    if (nOrders > maxSize)
        size = maxSize;
    else
        size = nOrders;

    enq = malloc (size * sizeof *enq);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nOrders; ++i) {
        getc (input);
        fscanf (input, "%c", &operacia);
        if (operacia == '+') {
            fscanf (input, "%i", &enq [tail]);
            tail++;
            tail = (tail == maxSize) ? 0: tail;
        }
        else {
            fprintf (output, "%i\n", enq [head]);
            head++;
            head = (head == maxSize) ? 0: head;
        }
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file \n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
