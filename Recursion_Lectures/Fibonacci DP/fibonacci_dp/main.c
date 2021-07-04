#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 9;
    int known [10];
    for (int i=0;i<10;i++){
        known[i] = -1;
    }
    printf("nth term: %d",fib_dp(n,known));
    return 0;
}

int fib_dp(int n, int *known){
    if (known[n] < 0){
        if (n==0 || n==1){
            known[n] = n;
        }else{
            known[n] = fib_dp(n-1,known) +fib_dp(n-2,known);
        }
        printf(" %d th term is %d\n",n, known[n]);
    }
    return known[n];
}
