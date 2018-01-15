//hesh_tab.c

#include <stdio.h>
#include <stdlib.h>

#define M 20999977
#define hashing(A) A % M

#define TUZ 1000
#define KVA 1000000000000000

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;

    long long *arr = NULL;
    int temp = 0;

    arr = malloc (M * sizeof *arr);

    for (int i = 0; i < M; ++i) {
        arr [i] = -1;
    }

    int N = 0;
    long long X = 0;
    short A = 0, Ac = 0, Ad = 0;
    long long B = 0, Bc = 0, Bd = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i %lli %hi %lli", &N, &X, &A, &B);
    fscanf (input, "%hi %lli %hi %lli", &Ac, &Bc, &Ad, &Bd);

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    for (int i = 0; i < N; ++i) {
        temp = hashing (X);
        if (arr [temp] != -1) {
            while (arr [temp] != -1 && arr [temp] != X && temp != M)
                temp++;

                if (arr [temp] == X) {
                    A = (A + Ac) % TUZ;
                    B = (B + Bc) % KVA;
                }
        }
        if (arr [temp] != X) {
            arr [temp] = X;
            A = (A + Ad) % TUZ;
            B = (B + Bd) % KVA;
        }

        X = (X * A + B) % KVA;
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file ouput.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (output, "%lli %hi %lli", X, A, B);

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file ouput.txt\n");
        exit (EXIT_FAILURE);
    }

    free (arr);
    arr = NULL;

    return EXIT_SUCCESS;
}
