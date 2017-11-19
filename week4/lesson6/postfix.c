//postfix.c

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000000

int main (void)
{
    FILE *input;
    FILE *output;
    int *stack = NULL;
    int nOrders = 0;
    int top = 0;
    int element = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nOrders);
    while (getc (input) != '\n')
        continue;

    stack = malloc (SIZE * sizeof *stack);

    for (unsigned int i = 0; i < nOrders; ++i) {
        element = getc (input);
        getc (input);

        switch (element) {
            case '+':
                top--;
                stack [top - 1] += stack [top];
                break;
            case '-':
                top--;
                stack [top - 1] -= stack [top];
                break;
            case '*':
                top--;
                stack [top - 1] *= stack [top];
                break;
            default:
                stack [top] = element - 48;
                top++;
                break;
        }
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (output, "%i", stack [0]);

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
