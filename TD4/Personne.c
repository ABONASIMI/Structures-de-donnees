#include "Personne.h"

typedef struct P
{
	char *nom;
	char *address;
} P;

void	envoyerAux(Personne *p, P visited[], int *count)
{
	int	i;
	int	find;

	while (p)
	{
		i = 0;
		find = 0;
		while (i < *count)
		{
			if (strcmp(p->nom, visited[i].nom) == 0 && strcmp(p->address,
					visited[i].address) == 0)
			{
				find = 1;
				break ;
			}
			i++;
		}
		if (find == 0)
		{
			if (*count >= 1000)
				return ;
			visited[*count].nom = p->nom;
			visited[*count].address = p->address;
			(*count)++;
			printf("The letter sent to %s at %s\n", p->nom, p->address);
			if (p->type == 1)
				envoyerAux(p->membres, visited, count);
		}
		p = p->suiv;
	}
}

void	envoyerCourrier(Personne *p)
{
	P	visited[1000];
	int	count;

	count = 0;
	envoyerAux(p, visited, &count);
}

void	suprrimeAux(Personne **head, char *nom, Personne *pre, Personne *suiv)
{
	Personne	*p;

	p = *head;
	while (p)
	{
		suiv = p->suiv;
		if (strcmp(p->nom, nom) == 0)
		{
			if (!pre)
				*head = suiv;
			else
				pre->suiv = suiv;
			free(p->nom);
			free(p->address);
			free(p);
			p = suiv;
			continue ;
		}
		if (p->type == 1)
			suprrimeAux(&p->membres, nom, NULL, NULL);
		pre = p;
		p = suiv;
	}
}

void	SupprimerPer(Personne **p, char *nom)
{
	if (!p || !nom)
		return ;
	suprrimeAux(p, nom, NULL, NULL);
}

/*

void	envoyerCourrier(Personne *p)
{
		struct P *suiv;
	int	find;
	P	*tmp;
	int	firstnum;

	typedef struct P {
		char* nom;
		char* address;
	} P;
	find = 0;
	tmp = NULL;
	firstnum = 0;
	P* first;
	while (p)
	{
		if (tmp)
		{
			tmp = first;
			while (tmp)
			{
				if ((strcmp(p->nom,tmp->nom) == 0) && (strcmp(p->address,
							tmp->address) == 0))
				{
					find = 1;
					break ;
				}
				tmp  = tmp->suiv;
			}
		}
		if (p->type == 0 && find == 0){
			printf("Send letter to %s at %s\n", p->nom, p->address);
		}
		else if (p->type == 1 && find == 0)
		{
			printf("Send letter to %s at %s\n", p->nom, p->address);
			envoyerCourrier(p->membres);
		}
		if (firstnum == 0)
		{
			firstnum == 1;
			first = tmp;
		}
		if (find == 0)
		{
			tmp->nom = p->nom;
			tmp->address = p->address;
			tmp = tmp->suiv;
		}
		else
			find = 0;
		p = p->suiv;
	}
}

*/