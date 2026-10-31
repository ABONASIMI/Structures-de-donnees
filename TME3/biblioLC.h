#ifndef BIBLIOLC_H
# define BIBLIOLC_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct Livre
{
	int				num;
	char			*titre;
	char			*auteur;
	struct Livre	*suiv;
}					LivreLC;

typedef struct Biblio
{
	LivreLC			*l;
}					BiblioLC;

LivreLC	*creer_livre(int num, char *titre, char *auteur);
void	liberer_livre(LivreLC *l);
void	liberer_livres(LivreLC *l);
BiblioLC	*creer_biblio(void);
void	liberer_biblio(BiblioLC *b);
void	inserer_en_tete(BiblioLC *b, int num, char *titre, char *auteur);

#endif