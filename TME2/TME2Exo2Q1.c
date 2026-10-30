#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int *alloue_tableau(int n)
{
    int *tab = (int *) malloc(sizeof(int) * n);
    return tab;
}

void alloue_tableau1(int **T, int n)
{
    *T = (int *) malloc(sizeof(int) * n);
}


void desalloue_tableau(int *T)
{
    free(T);
}

void remplir_tableau(int *tab, int size, int v)
{
    int val;
    int i = 0;

    while (i < size)
    {
        val = rand() % v;
        tab[i] = val;
        i++;
    }
}

void afficher_tableau(int *tab, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("%d\n", tab[i]);
        i++;
    }
}

