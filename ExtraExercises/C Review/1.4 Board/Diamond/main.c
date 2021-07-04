#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter n:\n");
    scanf("%d",&n);
    int m = n/2;
    for(int i = 0 ; i<n ;i++){
        for(int j=0;j<n;j++){
            if (j == m-i || j == m+i || j == m-(n-1-i)||j == m+n-1-i){
                printf("+");
            }else{
                printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}
