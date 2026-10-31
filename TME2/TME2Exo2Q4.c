#include <stdio.h>
#include <stdlib.h>

void alloue_matrice(int ***T, int size){
    *T = malloc(sizeof(int *) * size);
    int i = 0;
    while (i < size)
    {
        (*T)[i] = malloc(sizeof(int)*size);
        i++;
    }
}

int **alloue_matrice2(int size)
{
    int i = 0;
    int **T = malloc(sizeof(int *) * size);
    while (i < size)
    {
        T[i] = malloc(sizeof(int) * size);
        i++;
    }
    return T;
}

void desalloue_matrice(int ***T, int size)
{
    int i = 0;
    while (i < size)
    {
        free((*T)[i]);
        i++;
    }
    free(*T);
}

void remplir_matrice(int **T, int size, int v)
{
    int i = 0;
    int j;

    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            T[i][j] = rand() % v;
            j++;
        }
        i++;
    }
}


void affiche_matrix(int **T, int size)
{
    int i = 0;
    int j;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            printf("%d\t", T[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}