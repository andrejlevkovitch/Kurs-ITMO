//tree.c

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define COLUMNS 3

struct node {
    struct node *left;
    struct node *right;
    int value;
};

struct tree {
    struct node *root;
};

void inTree (int (*)[], struct node **, int);
int test (struct node *, long long, long long);
int walk (struct node *);

int main (void)
{
    FILE *input;
    FILE *output;

    int nNodes = 0;

    struct tree *bin_tree = malloc (sizeof *bin_tree);;
    bin_tree->root = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nNodes);

    int array [nNodes][COLUMNS];

    for (int i = 0; i < nNodes; ++i) {
        fscanf (input, "%i %i %i", &array [i][0], &array [i][1], &array [i][2]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if (nNodes)
        inTree (array, &bin_tree->root, 0);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    if (nNodes) {
        if (walk (bin_tree->root))
            fprintf (output, "YES");
        else
            fprintf (output, "NO");
    }
    else
        fprintf (output, "YES");

    if (fclose (output ) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void inTree (int (*array)[COLUMNS], struct node **inNode, int n)
{
    *inNode = malloc (sizeof **inNode);
    (*inNode)->value = array [n][0];
    (*inNode)->right = NULL;
    (*inNode)->left = NULL;

    if (array [n][1]) {
        inTree (array, &(*inNode)->left, array [n][1] - 1);
    }
    if (array [n][2]) {
        inTree (array, &(*inNode)->right, array [n][2] - 1);
    }

    return;
}

int test (struct node *tNode,  long long min,  long long max)
{
    if (!tNode)
        return 1;
    else {
        if (tNode->value < max && tNode->value > min) {
            return (test (tNode->right, tNode->value, max)) ? test (tNode->left, min, tNode->value) : 0;
        }
        else
            return 0;
    }
}

int walk (struct node *tNode)
{
    if (test (tNode->left, LLONG_MIN, tNode->value) && test (tNode->right, tNode->value, LLONG_MAX))
        return 1;
    else
        return 0;
}
