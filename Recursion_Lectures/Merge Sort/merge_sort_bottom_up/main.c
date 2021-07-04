#include <stdio.h>
#include <stdlib.h>
#define N 7
int main()
{
    int A[N] = {12, 6, 4, 5, 9, 2, 3};
    merge_sort_bu(A,0,N-1);
    for (int i=0;i<N;i++){
        fprintf(stdout,"%d ",A[i]);
    }
    return 0;
}


void merge_sort_bu(int *A, int l,int r){
    int *B = malloc (r-l+1 * sizeof(int));
    if(B==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    for (int m = 1;m<=N;m= 2*m){
        for(int i =l;i<r-m;i+= 2*m){
            merge(A,B,i,i+m-1,min(i+2*m-1,r));
        }
    }
    free(B);
    return;
}

void merge(int *A, int *B, int l,int c, int r){
    int i1 = l, i2= c+1, i3 =l;
    while(i1<=c && i2<=r){
        if (A[i1]<=A[i2]){
            B[i3++] = A[i1++];
        }else{
            B[i3++] = A[i2++];
        }
    }
    while (i1<=c){
        B[i3++] = A[i1++];
    }
    while (i2<=r){
        B[i3++] = A[i2++];
    }
    for (int i=l;i<=r;i++){
        A[i] = B[i];
    }
    return;
}

int min(int a, int b){
    if (a<b){
        return a;
    }
    return b;
}
