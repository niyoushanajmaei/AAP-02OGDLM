#include <stdio.h>
#include <stdlib.h>
#define N 10

void print_array(int arr[],int n);

int main()
{
    int arr[N];
    int i,j,c;
    printf("Enter the array:\n");
    for(i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    for(i=1;i<N;i++){
        c = arr[i];
        for(j=i-1;arr[j]>c&&j>=0;j--){
            arr[j+1]=arr[j];
        }
        arr[j+1]=c;
        print_array(arr,N);
    }
    return 0;
}

void print_array(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
