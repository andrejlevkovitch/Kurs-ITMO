//gir.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIL 1000000

long double binary (int, long double);

int main (void)
{
    FILE *input;
    FILE *output;

    int size = 0;
    long long a = 0;
    long double A = 0;
    int drobno = 0;
    char ch = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %lli", &size, &a);

    getc (input);
    for (unsigned int i = 0; i < 6; ++i) {
        ch = getc (input);
        if (ch < '0' || ch > '9')
            ch = '0';
        drobno *= 10;
        drobno += ch - '0';
    }

    a *= MIL;
    a += drobno;
    A = a;

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    a = binary (size, A);

    fprintf (output, "%lli.%lli", a / MIL, a - (a / MIL) * MIL);

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

long double binary (int size, long double a)
{
    int left = 0, right = size, midle = 0;
    long double b = 0, l = 0, r = 0;
    long double rezult = 0;

    bool rez = false;

    do {
        if (!rez)
            midle = left + (right - left) / 2;

        if (midle == size)
            break;

        b = (a - midle * MIL) * (long double)(midle - 1) / midle;
        l = (midle - 1) * b - a * (midle - 2) + (long double)(midle - 1) * (midle - 2) * MIL;
        r = (midle + 1) * b - a * midle + (long double)(midle + 1) * midle * MIL;
        printf ("midle == %i\n", midle);
        printf ("%Lf %Lf %Lf\n", b, l, r);

        if (l <= 0 && !rez)
            right = midle;
        else
            if (r <= 0 && !rez && midle != size - 1)
                left = midle + 1;
            else
                if (l > 0 && (r > 0 || midle == size - 1)) {
                    rez = true;
                    rezult = b;
                    midle++;
                    l = r = -1;
                }
                else
                    l = r = 1;
        if (midle == size - 1 && !rez)
            break;
    } while (l <= 0 || r <= 0);

    rezult = (size - 1) * rezult - a * (size - 2) + (long double)(size - 1) * (size - 2) * MIL;
    if (midle == size - 1 && !rez)
        rezult = 0;

    return rezult;
}
