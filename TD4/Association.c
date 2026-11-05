#include "MaisonDesAssociations.h"

Asso	*creerAssociation(char *nom)
{
	Asso	*ma;

	ma = malloc(sizeof(Asso));
	if (!ma)
		return (NULL);
	ma->nomass = strdup(nom);
	if (!ma->nomass)
	{
		free(ma);
		return (NULL);
	}
	ma->lesmembres = NULL;
	ma->suiv = NULL;
	return (ma);
}

void	ajouterPersonne(Asso *ma, char *nom)
{
	members	*m;
	members	*tmp;

	if (!ma)
		return ;
	m = malloc(sizeof(members));
	if (!m)
		return ;
	m->nom = strdup(nom);
	if (!m->nom)
	{
		free(m);
		return ;
	}
	tmp = ma->lesmembres;
	m->suiv = tmp;
	ma->lesmembres = m;
}

void	supprimerPersonne(Asso *ma, char *nom)
{
	members	*m;
	members	*tmp;
	members	*tmp2;

	if (!ma)
		return ;
	m = ma->lesmembres;
	tmp = NULL;
	while (m)
	{
		if (strcmp(m->nom, nom) == 0)
		{
			tmp2 = m->suiv;
			if (tmp == NULL)
				ma->lesmembres = tmp2;
			else
				tmp->suiv = tmp2;
			free(m->nom);
			free(m);
			break ;
		}
		tmp = m;
		m = m->suiv;
	}
}

MaisonAssoc *creerMaisonAssociation(void)
{
	MaisonAssoc *ma = malloc(sizeof(MaisonAssoc));
	if(!ma)
		return NULL;
	ma->associations = NULL;
	return ma;
}


void ajouterAssociation(MaisonAssoc *ma, Asso *a)
{
    if (!ma || !a)
        return;
	Asso *tmp = ma->associations;
    a->suiv = tmp;
    ma->associations = a;
}

void supprimerLesMemebre(Asso *a)
{
    members *m;
    members *tmp;

    if (!a)
        return;

    m = a->lesmembres;
    while (m)
    {
        tmp = m->suiv;
        free(m->nom);
        free(m);
        m = tmp;
    }
}

void supprimerAssociation(MaisonAssoc *ma, char *nom)
{
	if (!ma || !nom)
    	return;
	Asso *a = ma->associations;
	Asso *tmp = NULL;
	Asso *tmp2;

	while(a)
	{
		if (strcmp(a->nomass, nom) == 0)
		{
			tmp2 = a->suiv;
			if (!tmp)
			{
				ma->associations = tmp2;
				free(a->nomass);
				supprimerLesMemebre(a);
				free(a);
				return ;
			}
			free(a->nomass);
			free(a);
			tmp->suiv = tmp2;
			return ;
		}
		tmp = a;
		a = a->suiv;
	}
}