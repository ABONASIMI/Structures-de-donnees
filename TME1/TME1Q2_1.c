#include <stdlib.h>

int *alloue_tableau(int n){
    int *tab = malloc(sizeof(int) * n);
    return tab;
}

void alloue_tableau(int **T, int n) {
    *T = malloc(sizeof(int) * n);
}