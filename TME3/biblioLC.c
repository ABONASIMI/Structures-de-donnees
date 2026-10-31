#include "biblioLC.h"

LivreLC	*creer_livre(int num, char *titre, char *auteur)
{
	LivreLC	*li;

	li = malloc(sizeof(LivreLC));
	if (!li)
		return (NULL);
	li->num = num;
	li->titre = strdup(titre);
	if (!li->titre)
	{
		free(li);
		return (NULL);
	}
	li->auteur = strdup(auteur);
	if (!li->auteur)
	{
		free(li->titre);
		free(li);
		return (NULL);
	}
	li->suiv = NULL;
	return (li);
}

void	liberer_livre(LivreLC *l)
{
	LivreLC	*tmp;

	if (!l)
		return ;
	tmp = l->suiv;
	free(l->auteur);
	free(l->titre);
	free(l);
	l = tmp;
}

void	liberer_livres(LivreLC *l)
{
	LivreLC	*tmp;

	if (!l)
		return ;
	while (l)
	{
		tmp = l->suiv;
		free(l->auteur);
		free(l->titre);
		free(l);
		l = tmp;
	}
}

BiblioLC	*creer_biblio(void)
{
	BiblioLC	*bi;

	bi = malloc(sizeof(BiblioLC));
	if (!bi)
		return (NULL);
    bi->l = NULL;
	return (bi);
}

void	liberer_biblio(BiblioLC *b)
{
	if (!b)
		return ;
	liberer_livres(b->l);
	free(b);
}
void	inserer_en_tete(BiblioLC *b, int num, char *titre, char *auteur)
{
	if (!b)
		return ;
	LivreLC *l = b->l;
	LivreLC *tmp = creer_livre(num, titre, auteur);
    if(!tmp)
        return ;
	tmp->suiv = l;
	b->l = tmp;
}