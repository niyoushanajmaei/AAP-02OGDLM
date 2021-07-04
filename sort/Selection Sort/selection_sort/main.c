#include <stdio.h>
#include <stdlib.h>
#define N 10

void print_array(int arr[],int n);

int main()
{
    int arr[N];
    int i,j,c,temp;
    printf("Enter the array:\n");
    for(i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    for(i=0;i<N-1;i++){
        c = i;
        for(j=i+1;j<N;j++){
            if(arr[j]<arr[c]){
                c = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[c];
        arr[c] = temp;
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
