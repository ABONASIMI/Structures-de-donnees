#ifndef FORMATION_H
# define FORMATION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
typedef struct Formation
{
	int					hours;
	char				*name;
	struct Formation	*contenu;
	struct Formation	*suiv;
}						Formation;

typedef struct Catalogue
{
	Formation			*f;
	int					numFormation;
	int					maxFormation;
}						Catalogue;
#endif