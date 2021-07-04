#include <stdio.h>
#include <stdlib.h>
#define N 10

void print_array(int arr[],int n);

int main()
{
    int arr[N];
    int i,j,c;
    int h =1;
    printf("Enter the array:\n");
    for(i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    while (h < n/3){
        h = 3*h+1;
    }
    while (h>=1){
        for(i=h;i<N;i++){
            c = arr[i];
            j = i - h;
            while(arr[j]>c&&j>=0){
                arr[j+h]=arr[j];
                j -=h;
            }
            arr[j+h]=c;
            h = h/3;
            print_array(arr,N);
        }
    }
    return 0;
}

void print_array(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
