//avl_tree.c

#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *left;
    struct node *right;
    int value;
    int balance;
};

struct tree {
    struct node *root;
    int size;
};

struct tree *init_tree (void);
struct node *serch (struct node *sNode, const int value);
void turn (struct node **tNode);
struct node *del (struct node *);
struct tree *del_tree (struct tree *);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;
    int size = 0;
    int value = 0;
    struct node **hNode = NULL;

    struct tree *avl = init_tree ();

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    for (int i = 0; i < size; ++i) {
        while (getc (input) != '\n')
            continue;

        switch (getc (input)) {
            case 'A':
                fscanf (input, "%i", &value);
                fprintf (output, "%i\n", avl->root->balance);
                break;
            case 'D':
                fscanf (input, "%i", &value);
                break;
            case 'C':
                fscanf (input, "%i", &value);
                if (avl->root && serch (avl->root, value))
                    fprintf (output, "Y\n");
                else
                    fprintf (output, "N\n");

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

    avl = del_tree (avl);

    return EXIT_SUCCESS;
}

struct tree *init_tree (void)
{
    struct tree *tree = malloc (sizeof *tree);
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

struct node *serch (struct node *sNode, const int value)
{
    while (value != sNode->value) {
        if (value > sNode->value)
            sNode = sNode->right;
        else
            sNode = sNode->left;

        if (!sNode)
            break;
    }

    return sNode;
}

struct tree *del_tree (struct tree *rTree)
{
    rTree->root = (rTree->root) ? del (rTree->root) : NULL;

    rTree->size = 0;
    free (rTree);

    return NULL;
}

struct node *del (struct node *rNode)
{
    rNode->left = (rNode->left) ? del (rNode->left) : NULL;
    rNode->right = (rNode->right) ? del (rNode->right) : NULL;

    free (rNode);

    return NULL;
}

void turn (struct node **tNode)
{
    struct node *A = NULL;
    struct node *B = NULL;
    struct node *C = NULL;
    struct node *beta = NULL;
    struct node *hama = NULL;

    B = *tNode;

    switch (B->balance) {
        case -2:
            switch (B->right->balance) {
                case -1: case 0:
                    A = B->right;
                    hama = A->left;
                    A->left = B;
                    B->right = hama;
                    *tNode = A;

                    switch (A->balance) {
                        case -1:
                            B->balance = 0;
                            A->balance = 0;
                            break;
                        case 0:
                            B->balance = -1;
                            A->balance = 1;
                            break;
                    }
                    break;
                case 1:
                    A = B->right;
                    C = A->left;
                    beta = C->left;
                    hama = C->right;
                    C->right = A;
                    C->left = B;
                    A->left = hama;
                    B->right = beta;
                    *tNode = C;

                    switch (C->balance) {
                        case -1:
                            B->balance = 1;
                            A->balance = 0;
                            C->balance = 0;
                            break;
                        case 0:
                            B->balance = 0;
                            A->balance = 0;
                            C->balance = 0;
                            break;
                        case 1:
                            B->balance = 0;
                            A->balance = -1;
                            C->balance = 0;
                            break;
                    }
                    break;
                default:
                    break;
            }

            break;
        case 2:
            switch (B->left->balance) {
                case 1: case 0:
                    A = B->left;
                    hama = A->right;
                    A->right = B;
                    B->left = hama;
                    *tNode = A;

                    switch (A->balance) {
                        case 1:
                            B->balance = 0;
                            A->balance = 0;
                            break;
                        case 0:
                            B->balance = 1;
                            A->balance = -1;
                            break;
                    }
                    break;
                case -1:
                    A = B->left;
                    C = A->right;
                    beta = C->right;
                    hama = C->left;
                    C->left = A;
                    C->right = B;
                    A->right = hama;
                    B->left = beta;
                    *tNode = C;

                    switch (C->balance) {
                        case -1:
                            B->balance = 0;
                            A->balance = 1;
                            C->balance = 0;
                            break;
                        case 0:
                            B->balance = 0;
                            A->balance = 0;
                            C->balance = 0;
                            break;
                        case 1:
                            B->balance = -1;
                            A->balance = 0;
                            C->balance = 0;
                            break;
                    }
                    break;
                default:
                    break;
            }

            break;
        default:
            break;
    }

    return;
}
