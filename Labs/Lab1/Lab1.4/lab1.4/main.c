#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 5
int main()
{
    float m1[MAX_DIM][MAX_DIM],m2[MAX_DIM][MAX_DIM],m3[MAX_DIM][MAX_DIM];
    int r1,r2,c1,c2;
    printf("Enter r1 r2 c1 c2:\n");
    scanf("%d %d %d %d",&r1,&r2,&c1,&c2);
    if(r1>MAX_DIM||r2>MAX_DIM||c1>MAX_DIM||c2>MAX_DIM||r2!=c1){
        printf("wrong dimensions");
        return 1;
    }
    printf("Enter m1:\n");
    for (int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            scanf("%f",&m1[i][j]);
        }
    }
    printf("Enter m2:\n");
    for (int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            scanf("%f",&m2[i][j]);
        }
    }
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            int sum = 0;
            for (int k=0;k<c1;k++){
                sum+=m1[i][k]*m2[k][j];
            }
            m3[i][j] = sum;
        }
    }
    printf("\n");
    for (int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            printf("%.2f ",m3[i][j]);
        }
        printf("\n");
    }
    return 0;
}
