#include <stdio.h>
#include <stdlib.h>
#define DIM1 5
#define DIM2 3

int min(int a,int b);
int max(int a,int b);

int main()
{
    char m1[DIM1][DIM1],m2[DIM2][DIM2],m3[DIM1][DIM1];
    printf("Enter m1:\n");
    for (int i=0;i<DIM1;i++){
        char temp[DIM1+1];
        gets(temp);
        for(int j=0;j<DIM1;j++){
            m1[i][j]=temp[j];
        }
    }
    printf("Enter m2:\n");
    for (int i=0;i<DIM2;i++){
        char temp[DIM2+1];
        gets(temp);
        for(int j=0;j<DIM2;j++){
            m2[i][j]=temp[j];
        }
    }
    for(int i=0;i<DIM1-DIM2;i++){
        for(int j=0;j<DIM1-DIM2;j++){
            int flag=1;
            for(int k=i;k<=i+DIM2;k++){
                for(int l=j;l<=j+DIM2;l++){
                    if(!(k==i && l==j) && m2[k][l]!=m1[i][j]){
                        flag=0;
                    }
                }
            }
            if(flag==1){
                for(int k=i;k<=i+DIM2;k++){
                    for(int l=j;l<=j+DIM2;l++){
                        m3[k][l]=m1[k][l];
                    }
                }
            }
        }
    }
    for(int i=0;i<DIM1;i++){
        for(int j=0;j<DIM1;j++){
            printf("%c",m3[i][j]);
        }
    }
    return 0;
}

int min(int a,int b){
    if(a<=b){
        return a;
    }else{
        return b;
    }
}
int max(int a,int b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
