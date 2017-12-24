//tree.c

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 4

struct node {
    struct node *left;
    struct node *right;
    int h;
    int value;
};

struct tree {
    struct node *root;
};

struct tree *init_tree (void);
void build (struct node **, int, int (*)[COLUMNS]);
void rm (struct node *);
struct node *serch (struct node *, int);
int hight_a (int (*array)[COLUMNS], int el);
int highting (struct node *);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;

    int size = 0;
//    struct tree *bt = init_tree ();
//    struct node *hNode = NULL;

    int h = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    int array [size][COLUMNS];

    for (int i = 0; i < size; ++i) {
        fscanf (input, "%i %i %i", &array [i][0], &array [i][1], &array [i][2]);
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

//    if (size) {
//        build (&bt->root, 0, array);
//        highting (bt->root);
//    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    hight_a (array, 1);
    for (int i = 0; i < size; ++i) {
//        hNode = serch (bt->root, array [i][0]);
//        h = hNode->h;
        h = array [i][3];
        fprintf (output, "%i\n", h);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

//    rm (bt->root);
//    bt->root = NULL;
//    free (bt);
//    bt = NULL;

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
    (*inNode)->h = 0;

    if (array [n][1]) {
        build (&(*inNode)->left, array [n][1] - 1, array);
    }
    if (array [n][2]) {
        build (&(*inNode)->right, array [n][2] - 1, array);
    }

    return;
}

int highting (struct node *hNode)
{
    int n = 0;
    int k = 0;

    if (hNode) {
        k = highting (hNode->right) + 1;
        n = highting (hNode->left) + 1;

        hNode->h = k - n;
    }

    if (n > k)
        return n;
    else
        return k;
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

int hight_a (int (*array)[COLUMNS], int el)
{
    int n = 0;
    int k = 0;

    if (el) {
        n = hight_a (array, array [el - 1][1]) + 1;
        k = hight_a (array, array [el - 1][2]) + 1;

        array [el - 1][3] = k - n;
    }

    if (n > k)
        return n;
    else
        return k;
}
