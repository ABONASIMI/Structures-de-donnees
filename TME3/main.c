#include "entreeSortirLC.h"

void	affiche_livre(LivreLC *l)
{
	if (!l)
		printf("the Livre is empty\n");
	else
		printf("%d %s %s\n", l->num, l->titre, l->auteur);
}

void	afficher_biblio(BiblioLC *b)
{
	LivreLC	*l;

	if (!b)
	{
		printf("Library is empty\n");
		return ;
	}
	l = b->l;
	while (l)
	{
		affiche_livre(l);
		l = l->suiv;
	}
}

LivreLC	*rechercher_par_num(BiblioLC *b, int num)
{
	LivreLC	*l;
	int		founded;

	if (!b)
		return (NULL);
	l = b->l;
	founded = 0;
	while (l)
	{
		if (l->num == num)
		{
			founded = 1;
			break ;
		}
		l = l->suiv;
	}
	if (founded == 0)
	{
		printf("The Livre With %d is not in our Bibliothique", num);
		return (NULL);
	}
	return (l);
}

LivreLC	*rechercher_par_titre(BiblioLC *b, char *titre)
{
	LivreLC	*l;
	int		founded;

	if (!b)
		return (NULL);
	l = b->l;
	founded = 0;
	while (l)
	{
		if (strcmp(l->titre, titre) == 0)
		{
			founded = 1;
			break ;
		}
		l = l->suiv;
	}
	if (founded == 0)
	{
		printf("The Livre With %s is not in our Bibliothique", titre);
		return (NULL);
	}
	return (l);
}

BiblioLC	*rechercher_par_auteur(BiblioLC *b, char *auteur)
{
	BiblioLC	*bb;
	LivreLC		*l;
	LivreLC		*ll;
	LivreLC		*tmp;
	int			first;

	if (!b)
		return (NULL);
	bb = creer_biblio();
	if (!bb)
		return (NULL);
	l = b->l;
	first = 0;
	while (l)
	{
		if (strcmp(l->auteur, auteur) == 0)
		{
			ll = creer_livre(l->num, l->titre, l->auteur);
			if (!ll)
			{
				liberer_biblio(bb);
				return (NULL);
			}
			if (first == 0)
			{
				bb->l = ll;
				tmp = ll;
				first = 1;
			}
			else
			{
				tmp->suiv = ll;
				tmp = ll;
			}
		}
		l = l->suiv;
	}
	return (bb);
}

void	supprimer_livre(BiblioLC *b, int num, char *titre, char *auteur)
{
	LivreLC	*l;
	LivreLC	*tmp;
	LivreLC	*tmp2;

	if (!b)
		return ;
	l = b->l;
	tmp = NULL;
	while (l)
	{
		if (l->num == num && (strcmp(l->titre, titre) == 0)
			&& (strcmp(l->auteur, auteur) == 0))
		{
			if (!tmp)
			{
				tmp2 = l->suiv;
				b->l = tmp2;
			}
			else
			{
				tmp2 = l->suiv;
				tmp->suiv = tmp2;
			}
			liberer_livre(l);
			break ;
		}
		tmp = l;
		l = l->suiv;
	}
}

int	main(int ac, char **av)
{
	BiblioLC	*b;

	if (ac != 3)
	{
		printf("The program needs 2 arguments\n");
		return (1);
	}
	b = charger_n_entrees(av[1], atoi(av[2]));
	if (!b)
		return (1);
	enregistrer_biblio(b, "copie_biblio.txt");
	liberer_biblio(b);
	return (0);
}
