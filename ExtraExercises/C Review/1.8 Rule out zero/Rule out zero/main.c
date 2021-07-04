#include <stdio.h>
#include <stdlib.h>
#define DIM 10

int main()
{
    int arr[DIM];
    printf("Enter the array of %d dimension:\n",DIM);
    for(int i = 0;i<DIM;i++){
        scanf("%d",&arr[i]);
    }
    int c = 0;
    for(int i = 0;i<DIM;i++){
        if(arr[i]!=0){
            arr[c] = arr[i];
            c++;
        }
    }

    for(int i=0;i<c;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
