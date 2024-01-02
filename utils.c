#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"
#include "controls.h"

void clear_screen(void)
{
    printf("\e[1;1H\e[2J");
}

char rt_getchar(void)
{
    return getchar();
}

char *dyn_gets(void)
{
    end_bad_things();

    int used = 0;
    int size = 10;

    char *text = (char *)malloc(size * sizeof(char));

    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (used == size - 1)
        {
            size *= 2;
            text = (char *)realloc(text, size * sizeof(char));
        }

        if (text == NULL)
            allocation_fault();

        text[used] = c;
        used++;
    }

    text[used] = '\0';

    start_bad_things();

    return text;
}

char *get_valid_string()
{
    char *text = NULL;
    do
    {
        free(text);
        text = dyn_gets();
    } while (text[0] == '\0' || text[0] == '\n');

    return text;
}

bool **create_bool_matrix(int n)
{
    bool **matrix = (bool **)malloc(sizeof(bool *) * n);
    if (matrix == NULL)
        allocation_fault();

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (bool *)calloc(n, sizeof(bool));
        if (matrix[i] == NULL)
            exit(1);
    }

    return matrix;
}

int sum_bool_matrix(bool **matrix, int n)
{
    return count_active_cells(matrix, 0, n - 1, 0, n - 1);
}

int count_active_cells(bool **matrix, int from_i, int to_i, int from_j, int to_j)
{

    int count = 0;

    for (int i = from_i; i <= to_i; i++)
        for (int j = from_j; j <= to_j; j++)
            count += matrix[i][j];

    return count;
}

void allocation_fault()
{
    puts("*** Allocation fault! ***");
    exit(1);
}