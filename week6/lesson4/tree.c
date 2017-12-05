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
void inEl (struct node *in_node, int *array, int i, int *size);
int walk (const struct node *kur_node);
int rm (struct node *rm_node, int size, int element);
void print (const struct node *kur_node);

int main (void)
{
    FILE *input;
    FILE *output;
    int *array = NULL;
    int size = 0;
    struct tree *bts = NULL;
    struct node *new_node = NULL;
    int sizeD = 0;
    int *deleted = NULL;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * 3 * sizeof *array);

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i %i %i", &array [i * colum], &array [i * colum + 1], &array [i * colum + 2]); 
    }

    fscanf (input, "%i", &sizeD);

    deleted = malloc (sizeD * sizeof *deleted);

    for (unsigned int i = 0; i < sizeD; ++i) {
        fscanf (input, "%i", &deleted [i]);
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

    for (unsigned int i = 0; i < sizeD; ++i) {
        bts->size = rm (bts->root, bts->size, deleted [i]);
        fprintf (output, "%i\n", bts->size);
    }

    if (fclose (output ) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

struct tree *create (void)
{
    struct tree *new_tree = malloc (sizeof *new_tree);//выделение памяти под структуру

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

int walk (const struct node *kur_node)
{
    int size = 0;
    if (!kur_node)
        return 0;
    else {
        size += walk (kur_node->left);//рекурсия влево - пока не упрется в самый маленький элемент
        size += walk (kur_node->right);//рекурсия вправо
    }

    return ++size;
}

int rm (struct node *rm_node, int size, int element)
{
    struct node **del = NULL;

    while (rm_node && rm_node->info != element) {
        if (element < rm_node->info) {
            del = &rm_node->left;
            rm_node = rm_node->left;
        }
        else
            if (element > rm_node->info) {
                del = &rm_node->right;
                rm_node = rm_node->right;
            }
    }

    if (!rm_node)
        return size;
    else {
        size -= walk (rm_node);
        rm_node->left = NULL;
        rm_node->right = NULL;
        *del = NULL;
        return size;
    }
}
