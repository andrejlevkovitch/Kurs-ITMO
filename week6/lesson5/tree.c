//tree.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool proverka_left (struct node*, int);
bool proverka_right (struct node*, int);

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
        if (proverka_left (bin_tree->root->left, bin_tree->root->value) && proverka_right (bin_tree->root->right, bin_tree->root->value))
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

bool proverka_left (struct node *sNode, int bE)
{
    bool rez = false;

    if (sNode) {
        if (sNode->value > bE)
            return false;
        if (sNode->left) {
            if (sNode->left->value < sNode->value && sNode->left->value < bE) {
                rez = proverka_left (sNode->left, bE);
            }
            else
                return false;
        }
        else
            rez = true;
        if (rez) {
            if (sNode->right) {
                if (sNode->right->value > sNode->value && sNode->right->value < bE) {
                    return proverka_left (sNode->left, bE);
                }
                else
                    return false;
            }
            else {
                return true;
            }
        }
        else
            return false;
    }
    else
        return true;
}

bool proverka_right (struct node *sNode, int bE)
{
    bool rez = false;

    if (sNode) {
        if (sNode->value < bE)
            return false;
        if (sNode->left) {
            if (sNode->left->value < sNode->value && sNode->left->value > bE) {
                rez = proverka_right (sNode->left, bE);
            }
            else
                return false;
        }
        else
            rez = true;
        if (rez) {
            if (sNode->right) {
                if (sNode->right->value > sNode->value && sNode->right->value > bE) {
                    return proverka_right (sNode->right, bE);
                }
                else
                    return false;
            }
            else
                return true;
        }
        else
            return false;
    }
    else
        return true;
}
