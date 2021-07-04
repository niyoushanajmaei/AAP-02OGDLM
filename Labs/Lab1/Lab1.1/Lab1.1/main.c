#include <stdio.h>
#include <stdlib.h>
#define DIM 15

int main()
{
    int arr [DIM];
    int start = 0;
    int start_max = 0;
    int len = 1;
    int len_max = 1;

    printf("Enter the array:\n");
    for(int i=0;i<DIM;i++){
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<DIM-1;i++){
        if(arr[i+1]>arr[i]){
            len++;
        }else{
            len = 1;
            start = i+1;
        }
        if(len>len_max){
            start_max = start;
            len_max = len;
        }
    }

    for(int i=start_max;i<start_max + len_max;i++){
        printf("%d ",arr[i]);
    }

    return 0;
}
