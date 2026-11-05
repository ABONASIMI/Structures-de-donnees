#ifndef MAISONDESASSOCIATIONS_H
# define MAISONDESASSOCIATIONS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct members
{
	char			*nom;
	struct members	*suiv;
}					members;

typedef struct Asso
{
	char			*nomass;
	members			*lesmembres;
	struct Asso	*suiv;
}					Asso;

typedef struct MaisonAssoc
{
    Asso *associations;
} MaisonAssoc;

#endif