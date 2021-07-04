#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter n:\n");
    scanf("%d", &n);

    for(int i = 0 ; i<n+2 ;i++){
        printf("-");
    }
    printf("\n");
    for(int i = 1;i<n+1;i++){
        printf("|");
        for(int j =0;j<n;j++){
            if((i+j)%2==1){
                printf("#");
            }else{
                printf(" ");
            }
        }
        printf("|\n");
    }
    for(int i = 0 ; i<n+2 ;i++){
        printf("-");
    }
    return 0;
}
