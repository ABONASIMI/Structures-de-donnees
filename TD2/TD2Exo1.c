#include "TD2Exo1.h"

Element	*creerElement(int val)
{
	Element	*p;

	p = malloc(sizeof(Element));
	if (!p)
		return (NULL);
	p->pre = NULL;
	p->val = val;
	p->suiv = NULL;
	return (p);
}

void	initialiserListe(List *l)
{
	l->p = NULL;
	l->d = NULL;
}

List	*creerListe(void)
{
	List	*l;

	l = malloc(sizeof(List));
	if (!l)
		return (NULL);
	initialiserListe(l);
	return (l);
}

int	listVide(List *l)
{
	if (!l->d && !l->p)
		return (1);
	return (0);
}

void	insererEnTete(List *l, Element *e)
{
	Element	*pp;

	if (!l || !e)
		return ;
	e->pre = NULL;
	if (!l->p)
	{
		e->suiv = NULL;
		l->p = e;
		l->d = e;
		return ;
	}
	pp = l->p;
	e->suiv = pp;
	pp->pre = e;
	l->p = e;
}

void	insererEnFin(List *l, Element *e)
{
	Element	*e1;

	if (!l || !e)
		return ;
	e->suiv = NULL;
	if (!l->d)
	{
		e->pre = NULL;
		l->p = e;
		l->d = e;
		return ;
	}
	e1 = l->d;
	e->pre = e1;
	e1->suiv = e;
	l->d = e;
}

void	affiche(List *l)
{
	Element	*e;

	if (!l || listVide(l))
	{
		printf("List est Vide\n");
		return ;
	}
	e = l->d;
	while (e)
	{
		printf("%d\n", e->val);
		e = e->pre;
	}
}

Element	*rechercher(List *l, int val)
{
	Element	*ee;

	if (!l || listVide(l))
		return (NULL);
	ee = l->p;
	while (ee)
	{
		if (ee->val == val)
			return (ee);
		ee = ee->suiv;
	}
	return (NULL);
}

void	supprimerElement(List *l, Element *e)
{
	Element	*ee;
	Element	*tmp1;
	Element	*tmp2;

	if (!l || !e || listVide(l))
		return ;
	ee = l->p;
	while (ee)
	{
		if (ee == e)
		{
			if (ee->pre && ee->suiv)
			{
				tmp1 = ee->pre;
				tmp2 = ee->suiv;
				tmp2->pre = tmp1;
				tmp1->suiv = tmp2;
			}
			else if (ee->pre && !ee->suiv)
			{
				tmp1 = ee->pre;
				tmp1->suiv = NULL;
				l->d = tmp1;
			}
			else if (!ee->pre && ee->suiv)
			{
				tmp2 = ee->suiv;
				tmp2->pre = NULL;
				l->p = tmp2;
			}
			else if (!ee->pre && !ee->suiv)
			{
				l->p = NULL;
				l->d = NULL;
			}
			free(ee);
			return ;
		}
		ee = ee->suiv;
	}
}

int	supprimerEnTete(List *l)
{
	Element	*e;
	int		val;
	Element	*tmp;

	if (!l || listVide(l))
		return (0);
	e = l->p;
	if (e->suiv)
	{
		val = e->val;
		tmp = e->suiv;
		l->p = tmp;
		tmp->pre = NULL;
		free(e);
		return (val);
	}
	else if (!e->suiv)
	{
		val = e->val;
		l->p = NULL;
		l->d = NULL;
		free(e);
		return (val);
	}
	return (0);
}

int	supprimerFin(List *l)
{
	Element	*e;
	Element	*tmp;
	int		val;

	if (!l || listVide(l))
		return (0);
	e = l->d;
	if (e->pre)
	{
		val = e->val;
		tmp = e->pre;
		tmp->suiv = NULL;
		l->d = tmp;
		free(e);
		return (val);
	}
	if (!e->pre)
	{
		val = e->val;
		l->p = NULL;
		l->d = NULL;
		free(e);
		return (val);
	}
	return (0);
}

void	disAlloueListe(List *l)
{
	Element	*e;
	Element	*tmp;

	if (!l)
		return ;
	if (!l->p)
	{
		free(l);
		return ;
	}
	e = l->p;
	while (e)
	{
		tmp = e->suiv;
		free(e);
		e = tmp;
	}
	free(l);
}

int	main(void)
{
	Element *e = creerElement(10);
	Element *e1 = creerElement(20);
	Element *e2 = creerElement(30);
	List *l = creerListe();
	insererEnTete(l, e);
	insererEnFin(l, e1);
	insererEnFin(l, e2);
	affiche(l);
	supprimerElement(l, e2);
	affiche(l);
	supprimerEnTete(l);
	affiche(l);
	supprimerFin(l);
	affiche(l);
	disAlloueListe(l);
	return (0);
}