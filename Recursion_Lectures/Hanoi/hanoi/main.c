#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 3, src = 0, dest = 2;
    hanoi(n,src,dest);
    return 0;
}

void hanoi(int n, int src, int dest){
    if (n==1){
        printf("from %d to %d\n", src, dest);
        return;
    }
    int aux = 3 - (src+dest);
    hanoi(n-1,src,aux);
    printf("from %d to %d\n", src, dest);
    hanoi(n-1,aux,dest);
    return;
}
