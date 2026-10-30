#include <stdio.h>

int xy(int n){
    if (n)
        return n * xy(n-1);
    else 
        return 1;
}

int main(){
    printf("%d", xy(5));
}