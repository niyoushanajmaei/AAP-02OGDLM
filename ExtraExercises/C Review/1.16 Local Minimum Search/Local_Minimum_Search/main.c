#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R 5
#define C 5

int min(int a,int b);
int max(int a,int b);

int main()
{
    int m[R][C];
    int r_start,r_end,c_start,c_end;

    printf("Enter m:\n");
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            scanf("%d",&m[i][j]);
            while(m[i][j]<=0){
                printf("Must Enter strictly positive numbers\n");
                scanf("%d",&m[i][j]);
            }
        }
    }
    printf("\n");
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            int flag = 1;
            r_start=max(i-1,0);
            r_end=min(i+1,R-1);
            c_start=max(j-1,0);
            c_end=min(j+1,C-1);
            for(int k=r_start;k<=r_end;k++){
                for(int l=c_start;l<=c_end;l++){
                    if(!(k==i && l==j) && m[k][l]<=m[i][j]){
                        flag=0;
                    }
                }
            }
            if(flag==1){
                printf("Local Minimum (value=%d) at row=%d, column=%d\n",m[i][j],i+1,j+1);
            }
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
