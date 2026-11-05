#ifndef PERSONNE_H
#define PERSONNE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Personne {
    char *nom;
    char *address;
    int type; // 0 = Physique, 1 = Morale
    struct Personne *suiv;
    struct Personne *membres;
} Personne;

#endif