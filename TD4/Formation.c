#include "Formation.h"

void affiche(Catalogue *c)
{
    for (int i = 0; i < c->numFormation; i++)
    {
        printf("%s\n", c->f[i].name);
    }
}


void afficher_formation(Formation *f)
{
    Formation *f2;
    while (f)
    {
        printf("%s\n", f->name);
        afficher_formation(f->contenu);
        f= f->suiv;
    }
}


int calculer(Formation *f)
{
    Formation *ff;
    int sum;

    if (!f)
        return (0);

    sum = f->hours;
    ff = f->contenu;

    while (ff)
    {
        sum = sum + calculer(ff);
        ff = ff->suiv;
    }

    return (sum);
}
