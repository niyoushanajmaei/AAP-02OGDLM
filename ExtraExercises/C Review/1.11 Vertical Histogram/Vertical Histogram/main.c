#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c = 0;
    int temp;
    int hist[10];
    int done = 0;

    for(int i = 0 ; i<10 ;i++){
        hist[i]=0;
    }

    printf("Enter the numbers:\n");
    scanf("%d",&temp);
    while(temp > 0 && temp < 99){
        hist[temp/10]++;
        scanf("%d",&temp);
    }
    while(done != 10){
        for (int i=0; i<10 ; i++){
            if(hist[i]!=0){
                printf("#");
                hist[i]--;
                if(hist[i]==0){
                    done++;
                }
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
