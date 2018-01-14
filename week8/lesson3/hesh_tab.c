//hesh_tab.c

    #include <stdio.h>
    #include <stdlib.h>

    #define MAX_H 32
    #define M 101
    #define hashing(A) A % M

    #define TUZ 1000
    #define KVA 1000000000000000

    struct node {
        struct node *child [2];
        long long info;
        char balance;
    };

    struct tree {
        struct node *root;
        short size;
    };

    struct tree *init_tree (void);
    struct node *new_node (struct tree *, long long );
    struct node *search (struct tree*, const long long );
    void turn (struct node **);
    struct node *insert (struct tree *, long long );
    struct node *del (struct node *);
    struct tree *del_tree (struct tree *);
    int rm (struct tree *, long long );

    int main (void)
    {
        FILE *input = NULL;
        FILE *output = NULL;

        struct tree *arr [M] = {};

        int N = 0;
        long long X = 0;
        short A = 0, Ac = 0, Ad = 0;
        long long B = 0, Bc = 0, Bd = 0;

        if ((input = fopen ("input.txt", "r")) == NULL) {
            printf ("ERROR of open file input.txt\n");
            exit (EXIT_FAILURE);
        }

        fscanf (input, "%i %lli %hi %lli", &N, &X, &A, &B);
        fscanf (input, "%hi %lli %hi %lli", &Ac, &Bc, &Ad, &Bd);

        if (fclose (input) != 0) {
            printf ("ERROR of exit from file input.txt\n");
            exit (EXIT_FAILURE);
        }

      for (int i = 0; i < M; ++i) {
          arr [i] = init_tree ();
      }

        for (int i = 0; i < N; ++i) {
            if (search (arr [hashing (X)], X)) {
                A = (A + Ac) % TUZ;
                B = (B + Bc) % KVA;
            }
            else {
                insert (arr [hashing (X)], X);
                A = (A + Ad) % TUZ;
                B = (B + Bd) % KVA;
            }

            X = (X * A + B) % KVA;
        }

        if ((output = fopen ("output.txt", "w")) == NULL) {
            printf ("ERROR of open file ouput.txt\n");
            exit (EXIT_FAILURE);
        }

        fprintf (output, "%lli %hi %lli", X, A, B);

        if (fclose (output) != 0) {
            printf ("ERROR of exit from file ouput.txt\n");
            exit (EXIT_FAILURE);
        }

      for (int i = 0; i < M; ++i) {
          arr [i] = del_tree (arr [i]);
      }

        return EXIT_SUCCESS;
    }

    struct tree *init_tree (void)
    {
        struct tree *tree = malloc (sizeof *tree);
        tree->root = NULL;
        tree->size = 0;

        return tree;
    }

    struct node *new_node (struct tree *n_tree,  long long item)
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

    struct node *insert (struct tree *in_tree,  long long element)
    {
        struct node *in_node = in_tree->root;
        struct node **new = &in_tree->root;

        struct node **array [MAX_H] = {};//массив хранящий указатели на все пройденные ноды
        short dirs [MAX_H] = {};//массив хранящий направления движения
        short count = 0;

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

    int rm (struct tree *rm_tree,  long long element)
    {
        struct node *rm_node = rm_tree->root;
        struct node **q = &rm_tree->root;

        struct node **array [MAX_H] = {};//тоже что и во вставке
        short dirs [MAX_H] = {};
        short count = 0;

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
            
            dirs [count] = 0;//в этом случае создание массива продолжается
            array [count] = q;//в массив вводится указатель на удаляемую ноду, которая будет заменена другой
            count++;

            if (!y->child [1]) {
                y->child [1] = rm_node->child [1];

                y->balance = rm_node->balance;//удаляемая нода изменяется, но баланс остается
                *q = y;
            }
            else {
                struct node *x = y->child [1];
                short px = 0;
                px = count;
                dirs [count] = 1;//дополнение в массив указателей происходит ниже
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

                array [px] = &x->child [0];//вот оно, так как именно эта нода заменяет собой удаляемую

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

        rm_tree->size--;

        free (rm_node);
        rm_node = NULL;

        return 0;
    }

    struct node *search (struct tree *stree, const  long long value)
    {
        struct node *snode = stree->root;
        if (!snode)
            return NULL;
        while (value != snode->info) {
            snode = snode->child [value > snode->info];

            if (!snode)
                break;
        }

        return snode;
    }

    void turn (struct node **tnode)
    {
        struct node *b = NULL;//балансируемый узел
        struct node *a = NULL;//ребенок балансируемого узла
        struct node *c = NULL;//ребенок узла а
        struct node *beta = NULL;//подветка узла с
        struct node *hama = NULL;//подветка узла с или а

        b = *tnode;

        short dir = (b->balance < 0);//направление
        short mod = (dir) ? 1: -1;//модификатор, зависящий от направления

        switch (b->child [dir]->balance * mod) {//операции поворота одни и теже, но происходят зеркально, взависимости от направления
            case -1: case 0:
                a = b->child [dir];
                hama = a->child [!dir];
                a->child [!dir] = b;
                b->child [dir] = hama;
                *tnode = a;

                switch (a->balance * mod) {
                    case -1:
                        b->balance = 0;
                        a->balance = 0;
                        break;
                    case 0:
                        b->balance = -1 * mod;
                        a->balance = 1 * mod;
                        break;
                }
                break;
            case 1:
                a = b->child [dir];
                c = a->child [!dir];
                beta = c->child [!dir];
                hama = c->child [dir];
                c->child [dir]= a;
                c->child [!dir]= b;
                a->child [!dir]= hama;
                b->child [dir]= beta;
                *tnode = c;

                switch (c->balance * mod) {
                    case -1:
                        b->balance = 1 * mod;
                        a->balance = 0;
                        c->balance = 0;
                        break;
                    case 0:
                        b->balance = 0;
                        a->balance = 0;
                        c->balance = 0;
                        break;
                    case 1:
                        b->balance = 0;
                        a->balance = -1 * mod;
                        c->balance = 0;
                        break;
                }
                break;
            default:
                break;
        }

        return;
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
