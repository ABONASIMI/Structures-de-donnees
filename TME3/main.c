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

void	fusionner_bibliotheque(BiblioLC *b1, BiblioLC *b2)
{
	LivreLC	*tmp;

	if (!b1 || !b2 || b1 == b2)
		return ;
	if (!b1->l)
		b1->l = b2->l;
	else
	{
		tmp = b1->l;
		while (tmp->suiv)
			tmp = tmp->suiv;
		tmp->suiv = b2->l;
	}
	b2->l = NULL;
	free(b2);
}

BiblioLC	*doublons(BiblioLC *b)
{
	BiblioLC	*bb;
	LivreLC		*l;
	LivreLC		*tmp;
	LivreLC		*last;
	LivreLC		*copy;
	int			found;

	if (!b)
		return (NULL);
	bb = creer_biblio();
	if (!bb)
		return (NULL);
	l = b->l;
	last = NULL;
	while (l)
	{
		found = 0;
		tmp = b->l;
		while (tmp)
		{
			if (tmp != l && strcmp(l->titre, tmp->titre) == 0
				&& strcmp(l->auteur, tmp->auteur) == 0)
			{
				found = 1;
				break ;
			}
			tmp = tmp->suiv;
		}
		if (found == 1)
		{
			copy = creer_livre(l->num, l->titre, l->auteur);
			if (!copy)
			{
				liberer_biblio(bb);
				return (NULL);
			}
			if (!last)
				bb->l = copy;
			else
				last->suiv = copy;
			last = copy;
		}
		l = l->suiv;
	}
	return (bb);
}

void menu(void)
{
    printf("\n========== LIBRARY MANAGEMENT ==========\n");
    printf("1 - Display all books\n");
    printf("2 - Insert a new book\n");
    printf("3 - Search by book number\n");
    printf("4 - Search by title\n");
    printf("5 - Search by author\n");
    printf("6 - Delete a book\n");
    printf("7 - Merge two libraries\n");
    printf("8 - Find duplicate books\n");
    printf("9 - Save the library to a file\n");
    printf("0 - Exit\n");
    printf("========================================\n");
    printf("Choose an option: ");
}


int main(int ac, char **av)
{
    BiblioLC *b;
    int rep;

    if (ac != 3)
    {
        printf("The program needs 2 arguments\n");
        return (1);
    }

    b = charger_n_entrees(av[1], atoi(av[2]));
    if (!b)
        return (1);

    do
    {
        menu();

        if (scanf("%d", &rep) != 1)
            break;

        switch (rep)
        {
            case 0:
                break;

            case 1:
                printf("Affichage:\n");
                afficher_biblio(b);
                break;

            case 2:
            {
                int num;
                char titre[256];
                char auteur[256];

                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage.\n");

                if (scanf("%d %255s %255s", &num, titre, auteur) == 3)
                {
                    inserer_en_tete(b, num, titre, auteur);
                    printf("Ajout fait.\n");
                }
                else
                {
                    printf("Erreur format\n");
                    rep = 0;
                }
                break;
            }
			case 3:
			{
			    int num;
			    LivreLC *l;
			
			    printf("Enter the book number: ");
			    if (scanf("%d", &num) != 1)
			    {
			        printf("Invalid number\n");
			        rep = 0;
			        break;
			    }
			
			    l = rechercher_par_num(b, num);
			    if (l)
			        affiche_livre(l);
			
			    break;
			}

            default:
                printf("Option not implemented yet.\n");
                break;
        }

    } while (rep != 0);

    enregistrer_biblio(b, "copie_biblio.txt");
    liberer_biblio(b);

    printf("Merci, et au revoir.\n");
    return (0);
}
