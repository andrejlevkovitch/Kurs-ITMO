//avl_tree.c

#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *child [2];
    int info;
    int balance;
};

struct tree {
    struct node *root;
    int size;
};

struct tree *init_tree (void);
struct node *new_node (struct tree *, int);
struct node *serch (struct node *, const int);
void turn (struct node **);
struct node *insert (struct tree *, int);
struct node *del (struct node *);
struct tree *del_tree (struct tree *);
int rm (struct tree *, int);
void print_n (struct node *);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;
    int size = 0;
    int value = 0;

    struct tree *avl = init_tree ();
    if (!avl) {
        printf ("Error of memory\n");
        exit (EXIT_FAILURE);
    }

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
                insert (avl, value);
                fprintf (output, "%i\n", - avl->root->balance);
                break;
            case 'D':
                fscanf (input, "%i", &value);
                rm (avl, value);
                if (avl->root)
                    fprintf (output, "%i\n", - avl->root->balance);
                else
                    fprintf (output, "%i\n", 0);
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

//    printf ("%i\n", avl->root->info);
//    print_n (avl->root);
//    printf ("\n");

    avl = del_tree (avl);

    return EXIT_SUCCESS;
}

void print_n (struct node *pNode)
{
    if (pNode->child [0])
        print_n (pNode->child [0]);

    printf ("(%i %i)", pNode->info, pNode->balance);

    if (pNode->child [1])
        print_n (pNode->child [1]);
}

struct tree *init_tree (void)
{
    struct tree *tree = malloc (sizeof *tree);
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

struct node *new_node (struct tree *n_tree, int item)
{
    struct node *new = malloc (sizeof *new);
    if (new) {
        new->child [0] = new->child [1] = NULL;
        new->info = item;
        new->balance = 0;
        n_tree->size++;
    }

    return new;
}

struct node *insert (struct tree *in_tree, int element)
{
    struct node *in_node = in_tree->root;
    struct node **new = &in_tree->root;

    struct node **array [32] = {};
    int dirs [32] = {};
    int count = 0;

    for (;;) {
        if (!in_node) {
            in_node = *new = new_node (in_tree, element);
            break;
        }
        else
            if (in_node->info == element)
                return NULL;
            else {
                array [count] = new;
                dirs [count] = element > in_node->info;
                new = &in_node->child [dirs [count]];
                in_node = in_node->child [dirs [count]];
                count++;
            }
    }

    if (in_node && count) {
        for (int i = count - 1; i >= 0; --i) {
            if ((*array [i])->balance) {
                (*array [i])->balance = (dirs [i]) ? (*array [i])->balance - 1 : (*array [i])->balance + 1;
                if (abs ((*array [i])->balance) == 2)
                    turn (array [i]);
                if (!(*array [i])->balance)
                    break;
            }
            else
                (*array [i])->balance = (dirs [i]) ? -1 : 1;
        }
    }

    return in_node;
}

int rm (struct tree *rm_tree, int element)
{
    struct node *rm_node = rm_tree->root;
    struct node **q = &rm_tree->root;

    struct node **array [32] = {};
    int dirs [32] = {};
    int count = 0;

    for (;;) {
        if (!rm_node)
            return 1;
        else
            if (rm_node->info == element)
                break;
            else {
                array [count] = q;
                dirs [count] = element > rm_node->info;
                q = &rm_node->child [dirs [count]];
                rm_node = rm_node->child [dirs [count]];
                count++;
            }
    }

    if (!rm_node->child [0]) {
        *q = rm_node->child [1];
    }
    else {
        struct node *y = rm_node->child [0];
        
        dirs [count] = 0;
        array [count] = q;
        count++;

        if (!y->child [1]) {
            y->child [1] = rm_node->child [1];

            y->balance = rm_node->balance;
            *q = y;
        }
        else {
            struct node *x = y->child [1];
            dirs [count] = 1;
            array [count] = &rm_node->child [0];
            count++;

            while (x->child [1]) {
                dirs [count] = 1;
                array [count] = &y->child [1];
                count++;

                y = x;
                x = x->child [1];
            }

            y->child [1] = x->child [0];
            x->child [0] = rm_node->child [0];
            x->child [1] = rm_node->child [1];

            x->balance = rm_node->balance;

            *q = x;
        }
    }

    for (int i = count - 1; i >= 0; --i) {
        if ((*array [i])->balance) {
            (*array [i])->balance = (dirs [i]) ? (*array [i])->balance + 1 : (*array [i])->balance - 1;
            if (abs ((*array [i])->balance) == 2)
                turn (array [i]);
        }
        else {
            (*array [i])->balance = (dirs [i]) ? 1 : -1;
            if ((*array [i])->balance)
                break;
        }
    }

    rm_tree->size--;

    free (rm_node);
    rm_node = NULL;

    return 0;
}

struct node *serch (struct node *sNode, const int value)
{
    while (value != sNode->info) {
        sNode = sNode->child [value > sNode->info];

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
    for (int i = 0; i < 2; ++i) {
        rNode->child [i] = (rNode->child [i]) ? del (rNode->child [i]) : NULL;
    }

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

    int dir = (B->balance < 0);
    int mod = (dir) ? 1: -1;

    switch (B->child [dir]->balance * mod) {
        case -1: case 0:
            A = B->child [dir];
            hama = A->child [!dir];
            A->child [!dir] = B;
            B->child [dir] = hama;
            *tNode = A;

            switch (A->balance * mod) {
                case -1:
                    B->balance = 0;
                    A->balance = 0;
                    break;
                case 0:
                    B->balance = -1 * mod;
                    A->balance = 1 * mod;
                    break;
            }
            break;
        case 1:
            A = B->child [dir];
            C = A->child [!dir];
            beta = C->child [!dir];
            hama = C->child [dir];
            C->child [dir]= A;
            C->child [!dir]= B;
            A->child [!dir]= hama;
            B->child [dir]= beta;
            *tNode = C;

            switch (C->balance * mod) {
                case -1:
                    B->balance = 1 * mod;
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
                    A->balance = -1 * mod;
                    C->balance = 0;
                    break;
            }
            break;
        default:
            break;
    }

    return;
}
