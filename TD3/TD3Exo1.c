#include <stdio.h>

int	g(int x1, int x2, int x3, int x4, int x5, int x6)
{
	int	T[6] = {x1, x2, x3, x4, x5, x6};
	int	h;

	h = 0;
	for (int i = 0; i < 6; i++)
	{
		h = (h * 101 + T[i]) % 100000;
	}
	return (h);
}

int main(){
    printf("%d\n", g(02, 04, 10, 01, 00, 17));
    printf("%d\n", g(02, 10, 00, 02, 09, 05));
    printf("%d\n", g(00, 01, 17, 04, 02, 10));
    return 0;
}