//stack.c

#include <stdio.h>
#include <stdlib.h>

#define maxSize 1000000

int main (void)
{
    FILE *input;
    FILE *output;
    int *stack = NULL;
    int nOrders;
    int size = 0;
    int top = 0;
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

    stack = malloc (size * sizeof *stack);

    for (unsigned int i = 0; i < size; ++i) {
        stack [i] = 0;
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nOrders; ++i) {
        getc (input);
        fscanf (input, "%c", &operacia);
        if (operacia == '+') {
            fscanf (input, "%i", &stack [top]);
            top++;
            top = (top == maxSize) ? 0: top;
        }
        else {
            top--;
            fprintf (output, "%i\n", stack [top]);
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
