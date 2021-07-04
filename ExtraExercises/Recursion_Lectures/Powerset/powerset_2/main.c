#include <stdio.h>
#include <stdlib.h>

int main()
{
    int val[3] = {1,2,3};
    int sol[3];
    int n = 3;
    printf("%d",powerset_2(val,sol,n));
    return 0;
}

int powerset_2 (int *val,int *sol,int n){
    int count,k;
    count = 1;
    for (k=1;k<=n;k++){
        count += powerset_2_r(val,sol,n,k,0,0);
    }
    return count;
}

int powerset_2_r(int *val,int *sol, int n,int k, int start, int pos){
    int count = 0,i;
    if (pos >=k){
        /* print the answer*/
        return 1;
    }
    for (i=start ; i<n;i++){
        sol[pos] = val[i];
        count += powerset_2_r(val,sol,n,k,i+1,pos+1);
    }
    return count;
}
