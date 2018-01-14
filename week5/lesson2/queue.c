//queue.c

#include <stdio.h>
#include <stdlib.h>

//так как нам нужно будет находить минимальный элемент, а также заменять произвольный элемент значением меньше, чем предыдущее - нам понадобятся две ф-ции востановления свойств кучи
void restoring (int array [], int pile [], int bunch [], int num);//восстанавливает свойства кучи двигаясь от указанного элемента до корня
void heapify (int array [], int pile [], int bunch [], int num, int lenght);//будет двигаться от корня до листьев - нужна после удаления элемента из кучи (удаляется всегда 1-й элемент)

int main (void)
{
    FILE *input;
    FILE *output;

    int nOperace;

    int *array = NULL;//массив в котором хранятся элементы
    int *pile = NULL;//массив в котором хранятся координаты элементов в массиве array - этот массив будет двоичным деревом, отсортированным не по значениям которые он хранит, а по значениям массива array
    int *bunch = NULL;//массив в котором хранятся координаты координат элементов массива array в массиве pile - без этого нельзя будет сразу узнать координаты нужного элемента в массиве pile при замене значения элемента

    int num = 0, temp = 0;//эти две переменные будут хранить значения для замены значения элемента во время операции D
    int last = 0;//последний элемент кучи

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &nOperace);

    while (getc (input) != '\n')
        continue;

    array = malloc (nOperace * sizeof *array);
    pile = malloc (nOperace * sizeof *pile);
    bunch = malloc (nOperace * sizeof *bunch);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nOperace; ++i) {
        switch (getc (input)) {
            case 'A'://добавление элемента
                fscanf (input, "%i", &array [i]);//этот массив заполняется не по порядку, а в соответствии с номером операции - это нужно, чтобы при операции замены первое число (x) == i + 1
                pile [last] = i;//присваиваем этому массиву координаты
                bunch [pile [last]] = last;//а этому массиву присваиваем координаты координат; обратите ВНИМАНИЕ, что эта запись эквивалентна: bunch [i] = last, так как pile [last] = i!!!!!
                last++;
                restoring (array, pile, bunch, last - 1);//восстанавливаем кучу
                break;
            case 'X'://удаление элемента
                if (last) {
                    fprintf (output, "%i\n", array [pile [0]]);//выводим минимальный элемент
                    pile [0] = pile [last - 1];//после удаления корня ложим на его место последний элемент и восстанавливаем свойства кучи
//                    bunch [pile [0]] = 0;//можно обойтись и без этой строки, так как ф-ции восстановления не оперируют значениями массива bunch, но нужна, если оперируете значениями bunch!!!!
                    last--;
                    heapify (array, pile, bunch, 0, last);
                }
                else {
                    fprintf (output, "*\n");
                }
                break;
            case 'D'://замена значения элемента
                fscanf (input, "%i %i", &num, &temp);
                array [num - 1] = temp;//заменяем значение новым и восстанавливаем свойства кучи
                restoring (array, pile, bunch, bunch [num - 1]);
                break;
        }

        while (getc (input) != '\n')
            continue;
    }

    if (fclose (input) != 0) {
        printf ("ERROR of exit from file input.txt\n");
        exit (EXIT_FAILURE);
    }

    if (fclose (output) != 0) {
        printf ("ERROR of exit from file output.txt\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void restoring (int array [], int pile [], int bunch [], int num)
{
    int leas = 0;
    int temp = 0;

    leas = (num - 1) / 2;//нахождение узла родителя

    if (array [pile [leas]] > array [pile [num]]) {//если родитель больше потомка, то меняем их местами
        temp = pile [num];
        pile [num] = pile [leas];
        pile [leas] = temp;

        //также не забываем менять местами и значения массива bunch - при этом обратите ВНИМАНИЕ: так как значения в pile уже поменялись - операции замены в bunch выглядят именно так
        bunch [pile [num]] = num;
        bunch [pile [leas]] = leas;

        /*temp = bunch [pile [num]];//а можно записать и так, но учтите, что в этом случае, нужно чтобы строка 56 была обязательно раскомментирована!!!!!!
        bunch [pile [num]] = bunch [pile [leas]];
        bunch [pile [leas]] = temp;
        */

        restoring (array, pile, bunch, leas);//рекурсия до 0-вого элемента
    }

    return;
}

void heapify (int array [], int pile [], int bunch [], int num, int lenght)
{
    int left = 0, right = 0;
    int leas = 0;
    int temp = 0;

    left = 2 * num + 1;
    right = 2 * num + 2;
    leas = num;

    if (left < lenght && array [pile [left]] < array [pile [leas]])//сдесь заменены знаки > на < !!!
        leas = left;
    if (right < lenght && array [pile [right]] < array [pile [leas]])
        leas = right;

    if (leas != num) {
        temp = pile [num];
        pile [num] = pile [leas];
        pile [leas] = temp;

        //точно то же, что и ваше в restoring
        bunch [pile [num]] = num;
        bunch [pile [leas]] = leas;

        heapify (array, pile, bunch, leas, lenght);
    }

    return;
}
