//avl_tree.c

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 3

struct node {
    struct node *left;
    struct node *right;
    int value;
    int hight;
    int balance;
};

struct tree {
    struct node *root;
};

struct tree *init_tree (void);
void build (struct node **inNode, int n, int (*array)[COLUMNS]);
void rm (struct node *rNode);
struct node *serch (struct node *sNode, int value);
void out_rez (struct node *pNode, int (*array)[COLUMNS], int *num);
void print_nodes (struct node *pNode);
int highting (struct node *hNode);
void turn (struct node **tNode);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;
    int size = 0;
    struct tree *avl = init_tree ();
    int n = 1;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    int mas [size][COLUMNS];

    for (int i = 0; i < size; ++i) {
        fscanf (input, "%i %i %i", &mas [i][0], &mas [i][1], &mas [i][2]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    build (&avl->root, 0, mas);
    highting (avl->root);
//    print_nodes (avl->root);
//    printf ("\n");
    turn (&avl->root);
//    print_nodes (avl->root);
//    printf ("\n");

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (output, "%i\n", size);
    out_rez (avl->root, mas, &n);
    for (int i = 0; i < n; ++i) {
        fprintf (output, "%i %i %i\n", mas [i][0], mas [i][1], mas [i][2]);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    rm (avl->root);
    avl->root = NULL;
    free (avl);
    avl = NULL;

    return EXIT_SUCCESS;
}

struct tree *init_tree (void)
{
    struct tree *tree = malloc (sizeof *tree);
    tree->root = NULL;

    return tree;
}

void build (struct node **inNode, int n, int (*array)[COLUMNS])
{
    *inNode = malloc (sizeof **inNode);
    (*inNode)->value = array [n][0];
    (*inNode)->left = NULL;
    (*inNode)->right = NULL;
    (*inNode)->hight = 0;
    (*inNode)->balance = 0;

    if (array [n][1]) {
        build (&(*inNode)->left, array [n][1] - 1, array);
    }
    if (array [n][2]) {
        build (&(*inNode)->right, array [n][2] - 1, array);
    }

    return;
}

void rm (struct node *rNode)
{
    if (rNode->left)
        rm (rNode->left);
    if (rNode->right)
        rm (rNode->right);

    rNode->left = NULL;
    rNode->right = NULL;
    free (rNode);

    return;
}

struct node *serch (struct node *sNode, int value)
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

void out_rez (struct node *pNode, int (*array)[COLUMNS], int *num)
{
    int string = *num - 1;

    array [string][0] = pNode->value;

    if (pNode->right) {
        array [string][2] = ++(*num);
        out_rez (pNode->right, array, num);
    }
    else
        array [string][2] = 0;

    if (pNode->left) {
        array [string][1] = ++(*num);
        out_rez (pNode->left, array, num);
    }
    else
        array [string][1] = 0;

    return;
}

void print_nodes (struct node *pNode)
{
    if (pNode->left)
        print_nodes (pNode->left);

    printf ("(%i %i) ", pNode->value, pNode->balance);

    if (pNode->right)
        print_nodes (pNode->right);

    return;
}

int highting (struct node *hNode)
{
    int n = 0;
    int k = 0;

    if (hNode) {
        k = highting (hNode->right) + 1;
        n = highting (hNode->left) + 1;

        hNode->hight = (n > k) ? n: k;
        hNode->balance = n - k;
    }

    if (n > k)
        return n;
    else
        return k;
}

void turn (struct node **tNode)
{
    struct node *A = NULL;
    struct node *B = NULL;
    struct node *C = NULL;
    struct node *beta = NULL;
    struct node *hama = NULL;

    int l = 0, r = 0;

    B = *tNode;

    switch ((*tNode)->balance) {
        case -2:
            switch ((*tNode)->right->balance) {
                case -1: case 0:
                    A = B->right;
                    hama = A->left;
                    A->left = B;
                    B->right = hama;
                    *tNode = A;

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

                    break;
                default:
                    break;
            }

            break;
        case 2:
            switch ((*tNode)->left->balance) {
                case 1: case 0:
                    A = B->left;
                    hama = A->right;
                    A->right = B;
                    B->left = hama;
                    *tNode = A;

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

                    break;
                default:
                    break;
            }

            break;
        default:
            break;
    }

    if (B) {
        if (B->left)
            l = B->left->hight;
        if (B->right)
            r = B->right->hight;
        B->balance = l - r;
        B->hight = (l > r) ? l + 1: r + 1;

        l = 0;
        r = 0;
    }

    if (A) {
        if (A->left)
            l = A->left->hight;
        if (A->right)
            r = A->right->hight;
        A->balance = l - r;
        A->hight = (l > r) ? l + 1: r + 1;

        l = 0;
        r = 0;
    }

    if (C) {
        if (C->left)
            l = C->left->hight;
        if (C->right)
            r = C->right->hight;
        C->balance = l - r;
        C->hight = (l > r) ? l + 1: r + 1;

        l = 0;
        r = 0;
    }

    return;
}
