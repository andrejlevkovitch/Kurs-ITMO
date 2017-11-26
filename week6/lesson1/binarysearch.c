//binarysearch.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int binary (int array [], int size, int digit);

int main (void)
{
    FILE *input;
    FILE *output;

    int size = 0;
    int *array = NULL;
    int *koordArr = NULL;
    int inquirys = 0;
    int digit = 0;
    int rezult = 0;
    int first = 0, last = 0;
    int top = 0;

    if ((input = fopen ("input.txt", "r")) == NULL) {
        printf ("ERROR of open file input.txt\n");
        exit (EXIT_FAILURE);
    }

    fscanf (input, "%i", &size);

    array = malloc (size * sizeof *array);
    koordArr = malloc ((size + 1) * sizeof *array);//это на случай если все элементы в массиве разные

    for (unsigned int i = 0; i < size; ++i) {
        fscanf (input, "%i", &digit);
        if (!top || digit > array [top - 1]) {//в массив заносятся только не повторяющиеся элементы
            array [top] = digit;
            koordArr [top] = i + 1;//начальные адреса элементов заносятся в специальный массив
            top++;
        }
    }
    koordArr [top] = size + 1;//последний элемент хранит в себе окончание массива; сдесь + 1 из-за того, что ниже происходит отнимание

    fscanf (input, "%i", &inquirys);

    if ((output = fopen ("output.txt", "w")) == NULL) {
        printf ("ERROR of open file output.txt\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < inquirys; ++i) {
        fscanf (input, "%i", &digit);

        if ((rezult = binary (array, top, digit)) == EOF) {
            fprintf (output, "%i %i\n", EOF, EOF);
        }
        else {
            first = koordArr [rezult];//первая координата равна соответсвтующему значению координатного массива
            last = koordArr [rezult + 1] - 1;//вторая равна -1 от координаты следующего элемента
            fprintf (output, "%i %i\n", first, last);
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

    return EXIT_SUCCESS;
}

int binary (int array [], int size, int digit)
{
    int left = 0;
    int right = size;
    int midle = 0;

    if (size == 0) {
        return EOF;
    }
    else
        if (array [0] > digit) {
            return EOF;
        }
        else
            if (array [size - 1] < digit) {
                return EOF;
            }

    while (left < right) {
        midle = left + (right - left) / 2;

        if (digit <= array [midle])
            right = midle;
        else
            left = midle + 1;
    }

    if (array [right] == digit)
        return right;
    else
        return EOF;
}
