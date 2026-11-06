#ifndef BIBLIOH_H
#define BIBLIOH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct livreh {
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table {
    int nE;
    int m;
    LivreH **T;
} BiblioH;

#endif