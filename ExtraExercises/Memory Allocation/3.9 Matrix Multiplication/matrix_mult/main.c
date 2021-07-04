#include <stdio.h>
#include <stdlib.h>

int **read_matrix(char *name,int *p1, int *p2);
int **computeProduct(int **M1, int r1, int c1,
                       int **M2, int r2, int c2,
                    int *p1, int *p2);
void writeMatrix(char *name,int **m3,int r3,int c3);


int main()
{
    int **m1;
    int **m2;
    int **m3;
    int r1,r2,c1,c2,r3,c3;
    char *st1 = "file1.txt";
    char *st2 = "file2.txt";
    char *st3 = "output.txt";
    m1 = read_matrix(st1,&r1,&c1);
    m2 = read_matrix(st2,&r2,&c2);
    if (c1!=r2){
        fprintf(stderr,"Error in matrix dimensions\n");
        exit(1);
    }
    m3 = computeProduct(m1,r1,c1,m2,r2,c2,&r3,&c3);
    writeMatrix(st3,m3,r3,c3);

    for(int i=0;i<r1;i++){
        free(m1[i]);
    }
    free(m1);
    for(int i=0;i<r2;i++){
        free(m2[i]);
    }
    free(m2);
    for(int i=0;i<r3;i++){
        free(m3[i]);
    }
    free(m3);
    return 0;
}

int **read_matrix(char *name,int *p1, int *p2){
    int **m;
    FILE *f =fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d %d",p1,p2);
    m = malloc(*p1 * sizeof(int *));
    if (m==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    for (int i=0; i<*p1;i++){
        m[i] = malloc(*p2 *sizeof(int));
        if (m[i]==NULL){
            fprintf(stderr,"Error allocating memory\n");
            exit(1);
        }
        for (int j=0;j<*p2;j++){
            fscanf(f,"%d",&m[i][j]);
        }
    }
    fclose(f);
    return m;
}

int **computeProduct(int **m1, int r1, int c1, int **m2 , int r2, int c2, int *p1, int *p2){
    *p1 = r1;
    *p2 = c2;
    int **m3;
    m3 = malloc(r1*sizeof(int *));
    if(m3==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    for (int i=0;i<r1;i++){
        m3[i] = malloc((c2*sizeof(int)));
        if (m3[i]==NULL){
            fprintf(stderr,"Error allocating memory.\n");
            exit(1);
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
    return m3;
}

void writeMatrix(char *name,int **m3,int r3,int c3){
    FILE *f = fopen(name,"w");
    if (f == NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }
    fprintf(f,"%d %d\n",r3,c3);
    for (int i=0;i<r3;i++){
        for (int j=0;j<c3;j++){
            fprintf(f,"%d ",m3[i][j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
    return;
}

