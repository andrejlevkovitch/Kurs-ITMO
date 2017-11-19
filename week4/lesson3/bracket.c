//bracket.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100000

int main (void)
{
    FILE *input;
    FILE *output;
    int quantity = 0;
    char *stack = NULL;
    int top = 0;
    bool TBS = true;
    char ch = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &quantity);
    while (getc (input) != '\n')
        continue;

    stack = malloc (SIZE * sizeof *stack);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < quantity; ++i) {
        top = 0;
        TBS = true;
        while ((ch = getc (input)) != '\n') {
            switch (ch) {
                case '(':
                    stack [top] = ch;
                    top++;
                    break;
                case '[':
                    stack [top] = ch;
                    top++;
                    break;
                case ')':
                    if (top == 0)
                        TBS = false;
                    else {
                        top--;
                        TBS = (stack [top] != '(') ? false: TBS;
                    }
                    break;
                case ']':
                    if (top == 0)
                        TBS = false;
                    else {
                        top--;
                        TBS = (stack [top] != '[') ? false: TBS;
                    }
                    break;
            }
        }

        if (ch == '\n') {
            TBS = (TBS && top != 0) ? false: TBS;

            if (TBS)
                fprintf (output, "YES\n");
            else
                fprintf (output, "NO\n");
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
