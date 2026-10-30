#include <stdio.h>
#include <stdlib.h>

void alloue(int ***tab, int size)
{
    int i = 0;
    *tab = malloc(sizeof(int *) * size);
    while (i < size)
    {
        (*tab)[i] = malloc(sizeof(int) * size);
        i++;
    }
}

int **alloue2(int size)
{
    int i = 0;
    int **tab = malloc(sizeof(int *)* size);
    while (i < size)
    {
        tab[i] = malloc(sizeof(int) * size);
        i++; 
    }
    return tab;
}