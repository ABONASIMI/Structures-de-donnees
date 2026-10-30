#include <stdio.h>

void incrementer(int *val){
    *val += 1;
}

int main (){
    int val = 0;
    printf("%d\n", val);

    incrementer(&val);

    printf("%d\n", val);
    return 0;
}

