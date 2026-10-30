#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int	cal_som(int *T, int size)
{
	int	sum;
	int	i;
	int	j;

	sum = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			sum = sum + ((T[i] - T[j]) * (T[i] - T[j]));
			j++;
		}
		i++;
	}
	return (sum);
}

int	sumcal(int *tab, int size)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += tab[i];
		i++;
	}
	return (sum * sum);
}

int	sumcal2(int *tab, int size)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
	{
		sum = sum + tab[i] * tab[i];
		i++;
	}
	return (sum);
}
int	cal_sum(int *tab, int size)
{
	int	sum;

	// sum = sumcal(tab, size) * sumcal(tab, size); // a^2
	// sum = sum + (sumcal(tab, size) * sumcal(tab, size)); // a^2 + b^2
	// sum = sum - (2 * (sumcal(tab, size) * sumcal(tab, size))); // a^2 +b^2- 2ab
	sum = 2 * size * sumcal2(tab, size) - 2 * (sumcal(tab, size));
	return (sum);
}

int	main(void)
{
	int		size;
	int		*T;
	int		j;
	clock_t	temps_initial;
	clock_t	temps_final;
	double cputime;
	double cputime2;

	size = 5;
	j = 0;

	// printf("Print of the n^2 : %d\n", cal_som(T, size));
	// printf("Print of the n : %d\n", cal_sum(T, size));
	// temps_initial = clock();
	// cal_som(T, size);
	// temps_final = clock();
	// cputime = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
	// printf("Time of the n^2 complixity : %f\n", cputime);
	// temps_initial = clock();
	// cal_sum(T, size);
	// temps_final = clock();

	// cputime = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
	// printf("Time of the n complixity : %f\n", cputime);
	
	FILE *f = fopen("Vitess.txt", "w");
	if (!f)
	{
		printf("Probleme avec le fichier");
		return 0;
	}
	int tabsi[] = {100, 500, 1000, 5000, 10000};
	int i = 0;
	while (i < size)
	{
		T = malloc(sizeof(int) * tabsi[i]);
		j = 0;
		while (j < tabsi[i])
		{
			T[j] = j + 1;
			j++;
		}
		temps_initial = clock();
		cal_som(T, tabsi[i]);
		temps_final = clock();
		cputime = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
		temps_initial = clock();
		cal_sum(T, tabsi[i]);
		temps_final = clock();
		cputime2 = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
		fprintf(f, "%d %f %f\n", tabsi[i], cputime, cputime2);
		i++;
		free(T);
	}
	fclose(f);
	return (0);
}
