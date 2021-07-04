#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R 3
#define C 5

int factorial(int n);
int power(int a,int b);

int main()
{
    int m2[R][C];
    printf("Enter m1: (%d x %d)\n",R, C);
    for(int i = 0;i<R;i++){
        for(int j=0;j<C;j++){
            int temp;
            scanf("%d",&temp);
            if (temp == 0){
                m2[i][j] = 0;
            }else if (temp <0){
                m2[i][j] = factorial(-1 * temp);
            }else{
                m2[i][j] = power(10,ceil(log10(temp)));
                // for some reason doesn't work with pow function. 99 instead of 100
            }
        }
    }
    printf("\n");
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            printf("%d ",m2[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int factorial(int n){
    int res=1;
    for(int i=1;i<=n;i++){
        res=res*i;
    }
    return res;
}

int power(int a,int b){
    int res = 1;
    if (b ==0){
        return 1;
    }else{
        for(int i = 0;i <b;i++){
            res = res*a;
        }
        return res;
    }
}
