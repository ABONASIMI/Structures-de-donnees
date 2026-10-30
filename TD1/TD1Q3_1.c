#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int size = 6;
	int *tab = malloc(sizeof(int) * size);
	int i = 0;

    while (i < size)
    {
        tab[i] = rand();
        i++;
    }
    
    i = 0;
	while (i < size)
	{
		printf("%d\t", tab[i]);
		i++;
	}
    free(tab);
	return (0);
}