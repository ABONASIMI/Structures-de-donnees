#include "TD2Exo2.h"

Poste	*creerBureauPoste(int n)
{
	Poste	*p;
	Guichet	*tmp;
	Guichet	*tmp1;
	int		i;
	Guichet	*e;
	Guichet	*next;

	if (n < 0)
		return (NULL);
	p = malloc(sizeof(Poste));
	if (!p)
		return (NULL);
	p->nbg = n;
	p->pg = NULL;
	p->dg = NULL;
	if (n == 0)
	{
		p->dg = NULL;
		p->pg = NULL;
		return (p);
	}
	i = 0;
	while (i < n)
	{
		tmp = malloc(sizeof(Guichet));
		if (!tmp)
		{
			e = p->pg;
			while (e)
			{
				next = e->suiv;
				free(e);
				e = next;
			}
			free(p);
			return (NULL);
		}
		tmp->num = i;
		tmp->dc = NULL;
		tmp->pc = NULL;
		if (i == 0)
		{
			p->pg = tmp;
			tmp->pre = NULL;
			tmp->suiv = NULL;
			if (n == 1)
				p->dg = tmp;
		}
		else
		{
			p->dg = tmp;
			tmp->pre = tmp1;
			tmp1->suiv = tmp;
			tmp->suiv = NULL;
		}
		tmp1 = tmp;
		i++;
	}
	return (p);
}

void	afficherPoste(Poste *p)
{
	client	*c;
	Guichet	*g;

	if (!p)
		return ;
	g = p->pg;
	while (g)
	{
		printf("Guichet %d : ", g->num);
		c = g->pc;
		while (c)
		{
			printf("%d", c->numm);
			if (c->suiv)
				printf(" ");
			c = c->suiv;
		}
		g = g->suiv;
		printf("\n");
	}
}

void	ajouterAuGuichet(Poste *p, int numGuichet, int numClient)
{
	Guichet	*gg;
	client	*cc;
	client	*c;
	int		find;

	if (!p)
		return ;
	gg = p->pg;
	c = malloc(sizeof(client));
	if (!c)
		return ;
	c->numm = numClient;
	c->pre = NULL;
	c->suiv = NULL;
	find = 0;
	while (gg)
	{
		if (gg->num == numGuichet)
		{
			cc = gg->pc;
			if (cc == NULL)
			{
				gg->dc = c;
				gg->pc = c;
				c->suiv = NULL;
				c->pre = NULL;
			}
			else
			{
				c->suiv = cc;
				cc->pre = c;
				gg->pc = c;
				c->pre = NULL;
			}
			find = 1;
		}
		gg = gg->suiv;
	}
	if (find == 0)
		free(c);
}

int	applerAuGuichet(Poste *p, int numguichet)
{
	Guichet	*g;
	client	*c;
	client	*c1;

	if (!p)
		return ;
	g = p->pg;
    int val = 0;
	while (g)
	{
		if (g->num == numguichet)
		{
            if (g->dc == NULL && g->pc == NULL)
				printf("No one is in the file attend");
			else if (g->dc == g->pc)
			{
                c = g->dc;
                val = c->numm;
				printf("Number %d au guichet %d\n", c->numm, g->num);
				free(c);
				g->dc = NULL;
				g->pc = NULL;
			}
			else
			{
				c = g->dc;
				c1 = c->pre;
                c1->suiv = NULL;
                g->dc = c1;
                val = c->numm;
                printf("Number %d au guichet %d\n", c->numm, g->num);
				free(c);
			}
		}
        g = g->suiv;
	}
    return val;
}
