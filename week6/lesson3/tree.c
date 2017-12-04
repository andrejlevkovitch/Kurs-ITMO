//tree.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define colum 3

struct node {
    struct node *left;
    struct node *right;
    int info;
};

struct tree {
    struct node *root;
    int size;
};

struct tree *create (void);
int hight (const struct node *h_node);
void inEl (struct node *in_node, int *array, int i, int *size);
void walk (const struct node *kur_node);
void print_tree (const struct tree *kur_tree);

int main (void)
{
    FILE *input;
    FILE *output;
    int *array = NULL;
    int size = 0;
    struct tree *bts = NULL;
    struct node *new_node = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * 3 * sizeof array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i %i %i", &array [i * colum], &array [i * colum + 1], &array [i * colum + 2]); 
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    bts = create ();

    if (size) {
        new_node = malloc (sizeof *new_node);
        bts->root = new_node;
        new_node->info = array [0];
        new_node->right = NULL;
        new_node->left = NULL;
        bts->size = 1;
        if (size > 1) {
            inEl (bts->root, array, 1, &bts->size);
        }
    }

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    fprintf (output, "%i\n", hight (bts->root));

    if (fclose (output ) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

struct tree *create (void)
{
    struct tree *new_tree = malloc (sizeof new_tree);//выделение памяти под структуру

    if (new_tree == NULL)//если что-то пошло не так
        return NULL;

    new_tree->root = NULL;//инициализация корня и текущего размера
    new_tree->size = 0;

    return new_tree;
}

void inEl (struct node *in_node, int *array, int i, int *size)
{
    struct node *new_node = NULL;

    if (array [i]) {//если левый ребенок существует
        new_node = NULL;
        new_node = malloc (sizeof *new_node);
        in_node->left = new_node;
        new_node->right = NULL;
        new_node->left = NULL;
        new_node->info = array [(array [i] - 1) * colum];
        (*size)++;
        inEl (in_node->left, array, (array [i] - 1) * colum + 1, size);
    }

    if (array [i + 1]) {//если правый ребенок сеществует
        new_node = NULL;
        new_node = malloc (sizeof *new_node);
        in_node->right = new_node;
        new_node->right = NULL;
        new_node->left = NULL;
        new_node->info = array [(array [i + 1] - 1) * colum];
        (*size)++;
        inEl (in_node->right, array, (array [i + 1] - 1) * colum + 1, size);
    }

    return;
}

int hight (const struct node *h_node)
{
    int h1 = 0, h2 = 0;

    if (!h_node)
        return 0;
    else {
        if (h_node->left) {
            h1 = hight (h_node->left);
        }
        if (h_node->right) {
            h2 = hight (h_node->right);
        }
    }

    if (h1 > h2)
        return h1 + 1;
    else
        return h2 + 1;
}

void walk (const struct node *kur_node)
{
    if (!kur_node)
        return;
    else {
        walk (kur_node->left);//рекурсия влево - пока не упрется в самый маленький элемент
        printf ("%i ", kur_node->info);
        walk (kur_node->right);//рекурсия вправо
    }

    return;
}

void print_tree (const struct tree *kur_tree)
{
    walk (kur_tree->root);
}
