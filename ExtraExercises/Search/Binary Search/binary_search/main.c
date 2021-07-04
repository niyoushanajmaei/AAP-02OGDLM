#include <stdio.h>
#include <stdlib.h>
#define N 15

int BinarySearch(int v[], int l,int r,int k);

int main()
{
    int arr[N];
    int k;
    printf("Enter the array:\n");
    for (int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    printf("Enter k:\n");
    scanf("%d",&k);
    int res = BinarySearch(arr,0,N-1,k);
    printf("result: %d",res);
    return 0;
}

int BinarySearch(int v[], int l,int r,int k){
    while (l<=r){
        int c = (l+r)/2;
        if (v[c]==k){
            return c;
        }else if(v[c]>k){
            r = c-1;
        }else{
            l = c+1;
        }
    }
    return -1;
}
