//tel_s.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 101
#define DEF "put"

#define GET "get"
#define PREV "prev"
#define NEXT "next"
#define PUT "put"
#define DEL "delete"

#define MAX_V 21

#define MAX_H 32

struct node {
    char *key;
    char *info;

    struct node *ord [2];
    struct node *child [2];

    short balance;
};

short hashing (char *);
struct node *add (struct node **, char *, char *, struct node *);
struct node *search (struct node *, char *);
struct node *cler (struct node *);
struct node *rm (struct node **, char *, struct node *);
struct node *new_node (struct node *, char *, char *);
void turn (struct node **);

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
        if (!strcmp (GET, operace)) {
            fscanf (input, "%s", key);
            if ((h_node = search (directory [hashing (key)], key)))
                fprintf (output, "%s\n", h_node->info);
            else
                fprintf (output, "%s\n", "<none>");
        }
        else if (!strcmp (PREV, operace)) {
            fscanf (input, "%s", key);
            if ((h_node = search (directory [hashing (key)], key)) && h_node->ord [0])
                fprintf (output, "%s\n", h_node->ord [0]->info);
            else
                fprintf (output, "%s\n", "<none>");
        }
        else if (!strcmp (NEXT, operace)) {
            fscanf (input, "%s", key);
            if ((h_node = search (directory [hashing (key)], key)) && h_node->ord [1])
                fprintf (output, "%s\n", h_node->ord [1]->info);
            else
                fprintf (output, "%s\n", "<none>");
        }
        else if (!strcmp (PUT, operace)) {
            fscanf (input, "%s %s", key, value);
            last = add (&directory [hashing (key)], key, value, last);
        }
        else if (!strcmp (DEL, operace)) {
            fscanf (input, "%s", key);
            last = rm (&directory [hashing (key)], key, last);
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

struct node *new_node (struct node *last, char *key, char *item)
{
    struct node *new = malloc (sizeof *new);
    if (new) {
        new->child [0] = new->child [1] = NULL;

        new->info = malloc (strlen (item) + 1);
        strcpy (new->info, item);
        new->key = malloc (strlen (key) + 1);
        strcpy (new->key, key);

        new->ord [0] = last;
        if (last)
            last->ord [1] = new;
        new->ord [1] = NULL;

        new->balance = 0;

    }

    return new;
}

struct node *add (struct node **a_el, char *key, char *in, struct node *last)
{
    struct node *in_node = *a_el;

    char op = 0;

    struct node **array [MAX_H] = {};//массив хранящий указатели на все пройденные ноды
    short dirs [MAX_H] = {};//массив хранящий направления движения
    short count = 0;

    for (;;) {
        if (!in_node) {
            in_node = *a_el = new_node (last, key, in);
            break;
        }
        else
            if (!(op = strcmp (in_node->key ,key))) {
                in_node->info = realloc (in_node->info, strlen (in) + 1);
                strcpy (in_node->info, in);
                return last;
            }
            else {
                array [count] = a_el;
                dirs [count] = (op > 0);
                a_el = &in_node->child [dirs [count]];
                in_node = in_node->child [dirs [count]];
                count++;
            }
    }

    if (in_node && count) {//когда произошла вставка происходит балансировка
        for (int i = count - 1; i >= 0; --i) {
            if ((*array [i])->balance) {//если баланс не равен нулю
                (*array [i])->balance = (dirs [i]) ? (*array [i])->balance - 1 : (*array [i])->balance + 1;//происходит изменение баланса в зависимости от направления
                if (abs ((*array [i])->balance) == 2)//выполняется поворот если надо
                    turn (array [i]);
                if (!(*array [i])->balance)//если баланс оказался равен 0, то дальнейшие корректировки не нужны
                    break;
            }
            else//если баланс узла был равен 0, то он изменяется в зависимости от направления
                (*array [i])->balance = (dirs [i]) ? -1 : 1;
        }
    }

    return in_node;

}

struct node *rm (struct node **rm_tree, char *element, struct node *last)
{
    struct node *rm_node = *rm_tree;
    struct node **q = rm_tree;//для изменения адреса в узле
    short op = 0;

    struct node **array [MAX_H] = {};//тоже что и во вставке
    short dirs [MAX_H] = {};
    short count = 0;

    for (;;) {//поиск удаляемого элемента
        if (!rm_node)
            return last;
        else
            if (!(op = strcmp (rm_node->key, element)))
                break;
            else {
                array [count] = q;
                dirs [count] = (op > 0);
                q = &rm_node->child [dirs [count]];
                rm_node = rm_node->child [dirs [count]];
                count++;
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
        
        dirs [count] = 1;//в этом случае создание массива продолжается
        array [count] = q;//в массив вводится указатель на удаляемую ноду, которая будет заменена другой
        count++;

        if (!y->child [0]) {//если левая подветка пуста
            y->child [0] = rm_node->child [0];//то левая ветка переносится в левую подветку
            y->balance = rm_node->balance;
            *q = y;//а узел правого потомка смещается на место родителя
        }
        else {//если левая подветка заполнена
            struct node *x = y->child [0];//под-подветка левой подветки
            short px = 0;
            px = count;
            dirs [count] = 0;
            count++;

            while (x->child [0]) {//находится самый маленький элемент
                dirs [count] = 0;
                array [count] = &y->child [0];
                count++;

                y = x;
                x = y->child [0];
            }

            y->child [0] = x->child [1];
            x->child [0] = rm_node->child [0];
            x->child [1] = rm_node->child [1];

            array [px] = &x->child [1];

            x->balance = rm_node->balance;

            *q = x;
        }
    }

    for (int i = count - 1; i >= 0; --i) {//опять балансировка
        if ((*array [i])->balance) {
            (*array [i])->balance = (dirs [i]) ? (*array [i])->balance + 1 : (*array [i])->balance - 1;
            if (abs ((*array [i])->balance) == 2)
                turn (array [i]);
        }
        else
            (*array [i])->balance = (dirs [i]) ? 1 : -1;

        if ((*array [i])->balance)
            break;
    }

    free (rm_node->key);
    free (rm_node->info);
    free (rm_node);//это значение больше нигде не используется, так что освобождаем его

    if (last != rm_node)
        return last;
    else
        return rm_node->ord [0];
}

struct node *search (struct node *s_node, char *key)
{
    short op = 0;

    for (;;) {
        if (s_node == NULL)
            return NULL;
        else
            if (!(op = strcmp (s_node->key, key)))
                return s_node;
            else
                    s_node = s_node->child [op > 0];
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

void turn (struct node **tNode)
{
    struct node *B = NULL;//балансируемый узел
    struct node *A = NULL;//ребенок балансируемого узла
    struct node *C = NULL;//ребенок узла А
    struct node *beta = NULL;//подветка узла С
    struct node *hama = NULL;//подветка узла С или А

    B = *tNode;

    short dir = (B->balance < 0);//направление
    short mod = (dir) ? 1: -1;//модификатор, зависящий от направления

    switch (B->child [dir]->balance * mod) {//операции поворота одни и теже, но происходят зеркально, взависимости от направления
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
