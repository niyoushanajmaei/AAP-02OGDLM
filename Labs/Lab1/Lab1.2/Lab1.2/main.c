#include <stdio.h>
#include <stdlib.h>
#define DIM 100

int min(int a,int b);
int max(int a,int b);

int main()
{
    int n1,n2;
    printf("Enter n1 and n2:\n");
    scanf("%d %d",&n1,&n2);
    if (n1 > DIM || n2 >DIM){
        printf("n1 and n2 need to be lower or equal to DIM");
        return 1;
    }
    int v1[n1], v2[n1];
    printf("Enter v1 of %d integer values:\n",n1);
    for(int i=0;i<n1;i++){
        scanf("%d",&v1[i]);
    }
    for (int i=0;i<n1;i++){
        int start = max(0,i-n2);
        int end = min(n1-1,i+n2);
        int sum = 0;
        int c =0;
        for(int j=start;j<=end;j++){
            sum += v1[j];
            c++;
        }
        printf("%.2f ",1.0*sum/c);
    }
    return 0;
}

int min(int a,int b){
    if(a<=b){
        return a;
    }else{
        return b;
    }
}

int max(int a,int b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
