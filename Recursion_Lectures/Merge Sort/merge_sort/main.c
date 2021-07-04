#include <stdio.h>
#include <stdlib.h>
#define N 8
int main()
{
    int A[N] = {12,6,4,5,9,2,3,1};
    merge_sort(A,N);
    for(int i=0;i<N;i++){
        fprintf(stdout,"%d ",A[i]);
    }
    return 0;
}

void merge_sort(int *A, int n){
    int l = 0, r= n-1;
    int *B = malloc(n*sizeof(int));
    if (B==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    merge_sort_r(A,B,l,r);
    free(B);
}

void merge_sort_r(int *A,int *B, int l, int r){
    if (l>=r){
        return;
    }
    int c = (l+r)/2;
    merge_sort_r(A,B,l,c);
    merge_sort_r(A,B,c+1,r);
    merge(A,B,l,c,r);
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
