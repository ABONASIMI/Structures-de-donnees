#ifndef TD2EXO1_H
# define TD2EXO1_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct Element
{
	struct Element	*pre;
	int				val;
	struct Element	*suiv;
}					Element;

typedef struct List
{
	Element			*p;
	Element			*d;
}					List;

#endif
