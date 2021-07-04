#include <stdio.h>
#include <stdlib.h>
#define N 10
#define K 8

void print_array(int arr[],int n);

int main()
{
    int A[N];
    int C[K];
    int B[N];
    int i;
    printf("Enter the array:\n");
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    for(i=0;i<K;i++){
        C[i] = 0;
    }
    for(i=0;i<N;i++){
        C[A[i]]++;
    }
    for(i=1;i<K;i++){
        C[i]+=C[i-1];
    }
    print_array(C,K);
    for(i=N-1;i>=0;i--){
    //should start from the last one if we want it to be stable
        B[C[A[i]]-1]=A[i];
        C[A[i]]--;
    }
    for(i=0;i<N;i++){
        A[i] = B[i];
    }
    print_array(A,N);
    return 0;
}

void print_array(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
