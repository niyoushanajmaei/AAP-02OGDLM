#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 5

void readDim(int *, int *);
int checkDim(int, int, int, int);
void readMatrix(float [][MAX_DIM], int, int);
void computeProduct(float [][MAX_DIM], int, int,
                       float [][MAX_DIM], int, int,
                       float [][MAX_DIM], int *, int *);
void writeMatrix(float [][MAX_DIM], int, int,
                    float [][MAX_DIM], int, int,
                    float [][MAX_DIM], int, int);

int main()
{
    float m1[MAX_DIM][MAX_DIM],m2[MAX_DIM][MAX_DIM],m3[MAX_DIM][MAX_DIM];
    int r1,r2,c1,c2,r3,c3;

    printf("Enter r1 and c1:\n");
    readDim(&r1,&c1);
    printf("Enter r2 and c2:\n");
    readDim(&r2,&c2);
    if (checkDim(r1,c1,r2,c2) == 1){
            printf("Wrong dimensions.\n");
        return 1;
    }
    printf("Enter m1 (%d x %d):\n",r1,c1);
    readMatrix(m1,r1,c1);
    printf("Enter m2 (%d x %d):\n",r2,c2);
    readMatrix(m2,r2,c2);

    computeProduct(m1,r1,c1,m2,r2,c2,m3,&r3,&c3);
    printf("\n");
    writeMatrix(m1,r1,c1,m2,r2,c2,m3,r3,c3);

    return 0;
}

void readDim(int *p1 , int *p2){
    scanf("%d %d",p1,p2);
}

int checkDim(int r1, int c1, int r2, int c2){
    if(r1>MAX_DIM||r2>MAX_DIM||c1>MAX_DIM||c2>MAX_DIM||r2!=c1){
        return 1;
    }else{
        return 0;
    }
}

void readMatrix(float m [][MAX_DIM] , int r, int c){
    for (int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%f",&m[i][j]);
        }
    }
}

void computeProduct(float  m1 [][MAX_DIM], int r1, int c1, float m2 [][MAX_DIM] , int r2, int c2, float m3 [][MAX_DIM] , int *p1, int *p2){
    *p1 = r1;
    *p2 = c2;
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            int sum = 0;
            for (int k=0;k<c1;k++){
                sum+=m1[i][k]*m2[k][j];
            }
            m3[i][j] = sum;
        }
    }
}

void writeMatrix(float m1 [][MAX_DIM] , int r1, int c1, float m2 [][MAX_DIM] , int r2, int c2, float m3 [][MAX_DIM] , int r3, int c3){
    for (int i=0;i<r1;i++){
        printf("|");
        for(int j=0;j<c2;j++){
            printf("%.2f",m1[i][j]);
            printf(" ");
        }
        printf("|");
        if (i == r1/2){
            printf("x");
        }else{
            printf(" ");
        }
        printf("|");
        for(int j=0;j<c2;j++){
            printf("%.2f",m2[i][j]);
            printf(" ");
        }
        printf("|");
        if (i == r1/2){
            printf("=");
        }else{
            printf(" ");
        }
        printf("|");
        for(int j=0;j<c2;j++){
            printf("%.2f",m3[i][j]);
            printf(" ");
        }
        printf("|\n");
    }
}
