//avl_tree.c

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 3

struct node {
    struct node *left;
    struct node *right;
    int value;
    int balance;
};

struct tree {
    struct node *root;
};

struct tree *init_tree (void);
void build (struct node **inNode, int n, int (*array)[COLUMNS], struct node *parent);
struct node *serch (struct node *sNode, int value);
int highting (struct node *hNode);
void turn (struct node **tNode);
struct node *insert (struct tree *in_tree, int element);
void out_rez (struct node *pNode, int (*array)[COLUMNS], int *num);
void rm (struct node *rNode);
void balancer (struct node **bNode);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;
    int size = 0;
    int inUzel = 0;
    int n = 1;
    struct node *inNode = NULL;

    struct tree *avl = init_tree ();

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    int array [size + 1][COLUMNS];

    for (int i = 0; i < size; ++i) {
        fscanf (input, "%i %i %i", &array [i][0], &array [i][1], &array [i][2]);
    }

    fscanf (input, "%i", &inUzel);

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if (size) {
        build (&avl->root, 0, array, NULL);
    }
    inNode = insert (avl, inUzel);
    balancer (&avl->root);
    out_rez (avl->root, array, &n);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (output, "%i\n", n);

    for (int i = 0; i < n; ++i) {
        fprintf (output, "%i %i %i\n", array [i][0], array [i][1], array [i][2]);
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

void balancer (struct node **bNode)
{
    if ((*bNode)->left)
        balancer (&(*bNode)->left);
    if ((*bNode)->right)
        balancer (&(*bNode)->right);

    highting (*bNode);

    if (abs ((*bNode)->balance) == 2)
        turn (bNode);

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

struct tree *init_tree (void)
{
    struct tree *tree = malloc (sizeof *tree);
    tree->root = NULL;

    return tree;
}

struct node *insert (struct tree *in_tree, int element)
{
    struct node *in_node = in_tree->root;
    struct node **new = &in_tree->root;//нужен для изменения адреса, который содержится в root

    for (;;) {
        if (!in_node) {
            in_node = *new = malloc (sizeof *in_node);//выделение памяти под новый узел

            if (in_node) {
                in_node->value = element;//присваивание значений в новом узле
                in_node->left = in_node->right = NULL;
                in_node->balance = 0;

                return in_node;
            }
            else
                return NULL;//если что-то пошло не так
        }
        else
            if (in_node->value == element)//на случай, если проверка не была проведена
                return NULL;
            else
                if (in_node->value > element) {//нахождение нужного места для вставки
                    new = &in_node->left;
                    in_node = in_node->left;
                }
                else {
                    new = &in_node->right;
                    in_node = in_node->right;
                }
    }
}

void build (struct node **inNode, int n, int (*array)[COLUMNS], struct node *parent)
{
    *inNode = malloc (sizeof **inNode);
    (*inNode)->value = array [n][0];
    (*inNode)->left = NULL;
    (*inNode)->right = NULL;
    (*inNode)->balance = 0;

    if (array [n][1]) {
        build (&(*inNode)->left, array [n][1] - 1, array, (*inNode));
    }
    if (array [n][2]) {
        build (&(*inNode)->right, array [n][2] - 1, array, (*inNode));
    }

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

int highting (struct node *hNode)
{
    int n = 0;
    int k = 0;

    if (hNode) {
        k = highting (hNode->right) + 1;
        n = highting (hNode->left) + 1;

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
