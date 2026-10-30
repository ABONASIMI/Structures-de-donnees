#ifndef TD2Exo2_h
# define TD2Exo2_h

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct client
{
	struct client	*suiv;
	int				numm;
	struct client	*pre;
}					client;

typedef struct Guichet
{
	struct Guichet	*pre;
	struct Guichet	*suiv;
	int				num;
	client			*pc;
	client			*dc;
}					Guichet;

typedef struct Poste
{
	int				nbg;
	Guichet			*pg;
	Guichet			*dg;
}					Poste;

#endif
