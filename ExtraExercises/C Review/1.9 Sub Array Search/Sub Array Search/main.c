#include <stdio.h>
#include <stdlib.h>
#define DIM1 10
#define DIM2 3

int main()
{
    int arr1[DIM1];
    int arr2[DIM2];
    int pos[DIM1];
    int overlapping = 0;
    int c = 0;

    printf("Enter the array 1 of %d dimension:\n",DIM1);
    for(int i = 0;i<DIM1;i++){
        scanf("%d",&arr1[i]);
    }
    printf("Enter the array 2 of %d dimension:\n",DIM2);
    for(int i = 0;i<DIM2;i++){
        scanf("%d",&arr2[i]);
    }

    for (int i=0;i<DIM1-DIM2;i++){
        int flag = 1;
        for(int j=0;j<DIM2;j++){
            if (arr2[j] != arr1[i+j]){
                flag = 0;
            }
        }
        if (flag == 1){
            pos[c] = i;
            c++;
            if (overlapping == 0){
                i = i + DIM2 - 1;
            }
        }
    }

    for (int i=0;i<c;i++){
        printf("%d ", pos[i]);
    }
    return 0;
}
