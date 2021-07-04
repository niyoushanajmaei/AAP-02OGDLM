#include <stdio.h>
#include <stdlib.h>
#define n 8

int main()
{
    int A[n]={25,17,2,6,4,1,0,13};
    quicksort(A,n);
    for(int i = 0;i<n;i++){
        fprintf(stdout,"%d ",A[i]);
    }
    return 0;
}

void quicksort(int *A, int N){
    int l = 0, r=N-1;
    quicksort_r(A,l,r);
    return;
}

void quicksort_r(int * A,int l,int r){
    if (r-l<1){
        return;
    }
    int c = partition(A,l,r);
    quicksort_r(A,l,c-1);
    quicksort_r(A,c+1,r);
    return;
}

int partition (int *A, int l, int r){
    int i = l-1,j = r;
    int pivot = A[r];
    while (i<j){
        while (A[++i]<pivot);
            while (j >0 && A[--j]>pivot);
            if (i<j){
                swap(A,i,j);
            }
    }
    swap(A,i,r);
    for (int i=0; i<n ;i++){
        fprintf(stdout,"%d ",A[i]);
    }
    fprintf(stdout,"\n");
    return i;
}

void swap (int *A, int i, int j){
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
    return;
}
