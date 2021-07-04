
#include <stdio.h>
#include <stdlib.h>
#define N 10

void print_array(int arr[],int n);

int main()
{
    int arr[N];
    int i,j,temp;
    printf("Enter the array:\n");
    for(i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    for (i=N-1;i>=1;i--){
        for(j=0;j<i;j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
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
