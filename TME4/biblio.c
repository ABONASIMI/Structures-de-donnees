#include "biblioH.h"

int	functionClef(char *auteur)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (auteur[i])
	{
		sum = sum + (int)(auteur[i]);
		i++;
	}
	return (sum);
}

LivreH	*creer_livre(int num, char *titre, char *auteur)
{
	LivreH	*l;

	l = malloc(sizeof(LivreH));
	if (!l)
		return (NULL);
	l->num = num;
	l->titre = strdup(titre);
	if (!l->titre)
	{
		free(l);
		return (NULL);
	}
	l->auteur = strdup(auteur);
	if (!l->auteur)
	{
		free(l->titre);
		free(l);
		return (NULL);
	}
	l->clef = functionClef(auteur);
	l->suivant = NULL;
	return (l);
}

void	liberer_liste(LivreH *l)
{
	LivreH	*tmp;

	if (!l)
		return ;
	while (l)
	{
		tmp = l->suivant;
		free(l->auteur);
		free(l->titre);
		free(l);
		l = tmp;
	}
}

void	liberer_livre(LivreH *l)
{
	if (!l)
		return ;
	free(l->auteur);
	free(l->titre);
	free(l);
}

BiblioH	*creer_biblio(int m)
{
	BiblioH	*b;
	int		i;

	if (m <= 0)
		return (NULL);
	b = malloc(sizeof(BiblioH));
	if (!b)
		return (NULL);
	b->T = malloc(sizeof(LivreH *) * m);
	if (!b->T)
	{
		free(b);
		return (NULL);
	}
	b->m = m;
	b->nE = 0;
	i = 0;
	while (i < m)
	{
		b->T[i] = NULL;
		i++;
	}
	return (b);
}

void	liberer_biblio(BiblioH *b)
{
	int	i;

	if (!b)
		return ;
	i = 0;
	while (b->m > i)
	{
		liberer_liste(b->T[i]);
		i++;
	}
	free(b->T);
	free(b);
}

int	fonctionHachage(int cle, int m)
{
	double	A;
	double	x;

	if (m <= 0)
		return (-1);
	A = (sqrt(5.0) - 1.0) / 2.0;
	x = cle * A;
	return ((int)(m * (x - floor(x))));
}

void	inserer(BiblioH *b, int num, char *titre, char *auteur)
{
	LivreH *l;
	int hash;

	if (!b)
		return ;

	l = creer_livre(num, titre, auteur);
	if (!l)
		return ;

	hash = fonctionHachage(l->clef, b->m);

	l->suivant = b->T[hash];
	b->T[hash] = l;
	b->nE++;
}

