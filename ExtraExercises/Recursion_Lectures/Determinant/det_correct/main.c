#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 3

int main()
{
    int mat[N][N] = {{-2,2,-3},{-1,1,3},{2,0,-1}};
    printf("%d",det(mat,N));
    return 0;
}

int det(int m[][N],int n){
    if (n == 1){
        return m[0][0];
    }
    int sum = 0;
    int r;
    int m2[N][N];
    for (int k=0;k<n;k++){
        for (int i=1;i<n;i++){
            r = 0;
            for (int j=0;j<n;j++){
                if (k!=j){
                    m2[i-1][r] = m[i][j];
                    r++;
                }
            }
        }
        sum += pow(-1,k) * m[0][k] * det(m2,n-1);
    }
    return sum;
}
