#include <stdio.h>
#include <stdlib.h>

void main(void){
    int *p;
    int i = 0;
    p = &i;
    printf("%d\n", *p);

    p = (int *) malloc(sizeof(int));
    printf("%d\n", *p);

    free(p);
}