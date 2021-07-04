#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **generate(int n);
void print_codes(int **codes,int n);
void free_mem(int **codes,int n);

int main()
{
    int n;
    int **codes;
    printf("Enter n:\n");
    scanf("%d",&n);
    codes = generate(n);
    print_codes(codes,n);
    free_mem(codes,n);
    return 0;
}

int **generate(int n){
    int **prev;
    int **codes;
    int c,i,j;
    if (n==1){
        int **ans;
        ans = malloc(sizeof(int*));
        if (ans==NULL){
            fprintf(stderr,"Error allocating memory.");
        }
        ans[0] = malloc(2*sizeof(int));
        if (ans[0]==NULL){
            fprintf(stderr,"Error allocating memory.");
        }
        ans[0][0] = 0;
        ans[0][1] = 1;
        return ans;
    }
    prev = generate(n-1);
    c = pow(2,n);
    codes = malloc(n*sizeof(int *));
    if (codes == NULL){
        fprintf(stderr,"error allocating memory");
    }
    for(i=0;i<n;i++){
        codes[i] = malloc(c * sizeof(int));
        if (codes[i]==NULL){
            fprintf(stderr,"error allocating memory");
        }
    }
    for (i=0;i<n-1;i++){
        for (j=0;j<c;j++){
            if (j<c/2){
                codes[i][j] = prev[i][j];
            }else{
                codes[i][j] = prev[i][c-j-1];
            }
        }
    }
    for (j=0;j<c;j++){
        if (j<c/2){
            codes[i][j] = 0;
        }else{
            codes[i][j] = 1;
        }
    }
    return codes;
}

void print_codes(int **codes,int n){
    for(int i=0;i<n;i++){
        for (int j=0;j<pow(2,n);j++){
            fprintf(stdout,"%d ",codes[i][j]);
        }
        fprintf(stdout,"\n");
    }
    return;
}

void free_mem(int **codes,int n){
    for(int i=0;i<n;i++){
        free(codes[i]);
    }
    free(codes);
    return;
}
