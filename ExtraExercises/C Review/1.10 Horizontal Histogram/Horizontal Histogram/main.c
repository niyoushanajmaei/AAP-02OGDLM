#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c = 0;
    int temp;
    int hist[10];

    for(int i = 0 ; i<10 ;i++){
        hist[i]=0;
    }

    printf("Enter the numbers:\n");
    scanf("%d",&temp);
    while(temp > 0 && temp < 99){
        hist[temp/10]++;
        scanf("%d",&temp);
    }
    for (int i=0; i<10 ; i++){
        if (i==0){
            printf(" 0- 9 ");
        }else{
            printf("%d-%d ",i*10,(i+1)*10-1);
        }
        for(int j=0;j<hist[i];j++){
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
