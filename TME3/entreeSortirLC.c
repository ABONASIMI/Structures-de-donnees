#include "entreeSortirLC.h"

BiblioLC	*charger_n_entrees(char *nomfic, int n)
{
    BiblioLC *b = creer_biblio();
    if (!b)
        return NULL;
    FILE *f = fopen(nomfic, "r");
    if (!f){
        free(b);
        return NULL;
    }
    int i = 0;
    int num;
    char titre[256];
    char auteur[256];
    int succ = 1;
    LivreLC *l = NULL;
    LivreLC *tmp= NULL;
    while (i < n && succ == 1)
    {
        if (!(fscanf(f, "%d %255s %255s", &num, titre, auteur) == 3)){
            succ = 0;
            break;
        }
        tmp = creer_livre(num, titre, auteur);
        if (!tmp)
        {
            liberer_biblio(b);
            fclose(f);
            return NULL;
        }
        else if (!l)
        {
            l = tmp;
            b->l = l;
        }
        else {
            l->suiv = tmp;
            l = l->suiv;
            l->suiv = NULL;
        }
        i++;
    }
    fclose(f);
    return b;
}


void enregistrer_biblio(BiblioLC *b, char *nomfic)
{
    if (!b)
        return ;
    FILE *f = fopen(nomfic, "w");
    if (!f)
        return ;
    LivreLC *l = b->l;
    while (l)
    {
        fprintf(f, "%d %s %s\n", l->num, l->titre, l->auteur);
        l = l->suiv;
    }
    fclose(f);
}







/*
**31/10/2026**

This is the code I wrote when I misunderstood the question and thought 
I had to read from a string instead of a file It's all part of my programming 
journey. These mistakes help me pay more attention and improve my code
I really enjoyed writing this code and developing my own algorithm That's 
why I don't want to delete it. I want to keep it here as a memorable part of my journey.

{
	int i = 0;
	int numline = 1;
	BiblioLC *b = malloc(sizeof(BiblioLC));
	if (!b)
		return (NULL);

	int num;
	char titre[256];
	char auteur[256];
	int j = 0;
	int k = 0;
	int spacevu = 0;
	int first = 0;
	LivreLC *tmp;
	while (nom[i] && numline <= 9)
	{
		if (nom[i] >= 0 && <= 9)
			num = num * 10 + (nom[i] - '0');
		else if (spacevu == 0)
		{
			titre[j] = nom[i];
			j++;
		}
		else if (spacevu == 1)
		{
			auteur[k] = nom[i];
			k++;
		}
		else if (nom[i] == " " || nom[i] == "\t")
			;
		spacevu = 1;
		else if (nom[i] == "\n")
		{
			j = 0;
			k = 0;
			spacevu = 0;
			numline += 1;
			LivreLC *li = malloc(sizeof(LivreLC));
			if (!li)
			{
				liberer_biblio(b);
				return (NULL);
			}
			li->num = num;
			li->titre = strdup(titre);
			if (!li->titre)
			{
				free(li);
				liberer_biblio(b);
				return (NULL);
			}
			li->auteur = strdup(auteur);
			if (!li->auteur)
			{
				free(li->titre);
				free(li);
				liberer_biblio(b);
				return (NULL);
			}
			if (first == 0)
			{
				tmp = li;
				b->l = tmp;
				first += 1;
			}
			else
			{
				tmp->suiv = li;
				tmp = tmp->suiv;
				tmp->suiv = NULL;
			}
		}
		i++;
	}
	return (b);
}
*/
