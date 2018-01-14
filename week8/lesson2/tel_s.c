//tel_s.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 9887
#define DEF "put"

#define GET 9
#define PREV 3
#define NEXT 2
#define PUT 0
#define DEL 12

#define MAX_V 21

struct node {
    char *key;
    char *info;
    struct node *ord [2];

    struct node *child [2];
};

short hashing (char *);
struct node *add (struct node **, char *, char *, struct node *);
struct node *search (struct node *, char *);
struct node *cler (struct node *);
void rm (struct node **, char *);

int main (void)
{
    FILE *input = NULL;
    FILE *output = NULL;

    struct node *directory [M] = {};
    int size = 0;
    char operace [7] = {};
    char key [MAX_V] = {};
    char value [MAX_V] = {};
    struct node *h_node = NULL;
    struct node *last = NULL;

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
        fscanf (input, "%s", operace);
        switch (strcmp (DEF, operace)) {
            case GET:
                fscanf (input, "%s", key);
                if ((h_node = search (directory [hashing (key)], key)))
                    fprintf (output, "%s\n", h_node->info);
                else
                    fprintf (output, "%s\n", "<none>");
              break;
            case PREV:
                fscanf (input, "%s", key);
                if ((h_node = search (directory [hashing (key)], key)) && h_node->ord [0])
                    fprintf (output, "%s\n", h_node->ord [0]->info);
                else
                    fprintf (output, "%s\n", "<none>");
                break;
            case NEXT:
                fscanf (input, "%s", key);
                if ((h_node = search (directory [hashing (key)], key)) && h_node->ord [1])
                    fprintf (output, "%s\n", h_node->ord [1]->info);
                else
                    fprintf (output, "%s\n", "<none>");
                break;
            case PUT:
                fscanf (input, "%s %s", key, value);
                last = add (&directory [hashing (key)], key, value, last);
                break;
            case DEL:
                fscanf (input, "%s", key);
                rm (&directory [hashing (key)], key);
                break;
//          default:
//              fprintf (output, "!");
//              break;
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

    for (int i = 0; i < M; ++i) {
        if (directory [i]) {
            directory [i] = cler (directory [i]);
        }
    }

    return EXIT_SUCCESS;
}

short hashing (char *key)
{
    int rez = 0;
    char ch = 1;

    for (int i = 0; ch != '\0'; ++i) {
        ch = key [i];
        rez += ch * 31;
    }

    rez %= M;

    return rez;
}

struct node *add (struct node **a_el, char *key, char *in, struct node *last)
{
    struct node *in_node = *a_el;

    char op = 0;

    for (;;) {
        if (!in_node) {
            in_node = *a_el = malloc (sizeof *in_node);//выделение памяти под новый узел

            if (in_node) {
                in_node->key = malloc (strlen (key) + 1);
                strcpy (in_node->key, key);
                in_node->info = malloc (strlen (in) + 1);
                strcpy (in_node->info, in);
                in_node->child [0] = in_node->child [1] = NULL;
                in_node->ord [0] = last;
                if (last)
                    last->ord [1] = in_node;
                in_node->ord [1] = NULL;

                return in_node;
            }
            else
                return NULL;//если что-то пошло не так
        }
        else
            if (!(op = strcmp (in_node->key ,key))) {
                in_node->info = realloc (in_node->info, strlen (in) + 1);
                strcpy (in_node->info, in);
                return last;
            }
            else
                if (op > 0) {//нахождение нужного места для вставки
                    a_el = &in_node->child [0];
                    in_node = in_node->child [0];
                }
                else {
                    a_el = &in_node->child [1];
                    in_node = in_node->child [1];
                }
    }
}

void rm (struct node **rm_tree, char *element)
{
    struct node *rm_node = *rm_tree;
    struct node **q = rm_tree;//для изменения адреса в узле
    short op = 0;

    for (;;) {//поиск удаляемого элемента
        if (!rm_node)
            return;
        else
            if (!(op = strcmp (rm_node->key, element))) {
                break;
            }
            else
                if (op > 0) {
                    q = &rm_node->child [0];
                    rm_node = rm_node->child [0];
                }
                else {
                    q = &rm_node->child [1];
                    rm_node = rm_node->child [1];
                }
    }

    if (rm_node->ord [0])
        rm_node->ord [0]->ord [1] = rm_node->ord [1];
    if (rm_node->ord [1])
        rm_node->ord [1]->ord [0] = rm_node->ord [0];

    //удаление элемента
    if (!rm_node->child [1]) {//если правая ветка пуста
        *q = rm_node->child [0];
    }
    else {
        struct node *y = rm_node->child [1];//подветка основной ветки
        
        if (!y->child [0]) {//если левая подветка пуста
            y->child [1] = rm_node->child [0];//то левая ветка переносится в левую подветку
            *q = y;//а узел правого потомка смещается на место родителя
        }
        else {//если левая подветка заполнена
            struct node *x = y->child [0];//под-подветка левой подветки

            while (x->child [0]) {//находится самый маленький элемент
                y = x;
                x = y->child [0];
            }

            y->child [0] = x->child [1];//подветка принимает правого (единственного) ребенка себе
            x->child [0] = rm_node->child [0];//а найденный минимальный элемент становится на место удаленного
            x->child [1] = rm_node->child [1];
            *q = x;
        }
    }

    free (rm_node);//это значение больше нигде не используется, так что освобождаем его
    rm_node = NULL;

    return;
}

struct node *search (struct node *s_node, char *key)
{
    char op = 0;

    for (;;) {
        if (s_node == NULL)
            return NULL;
        else
            if (!(op = strcmp (s_node->key, key)))
                return s_node;
            else
                if (op > 0)
                    s_node = s_node->child [0];
                else
                    s_node = s_node->child [1];
    }
}

struct node *cler (struct node *c_node)
{
    if (c_node) {
        c_node->child [0] = cler (c_node->child [0]);
        c_node->child [1] = cler (c_node->child [1]);
        free (c_node->key);
        free (c_node->info);
        free (c_node);

        return NULL;
    }
    else
        return c_node;
}
