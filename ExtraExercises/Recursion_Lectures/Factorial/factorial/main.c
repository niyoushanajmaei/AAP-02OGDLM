#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 5;
    printf("%d",factorial(n));
    return 0;
}

int factorial(int n){
    if (n==1){
        return 1;
    }
    return n*factorial(n-1);
}
