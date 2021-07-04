#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate(char *val,char *sol, int *left, int n, int pos);

int main()
{
    char *val,*sol;
    int *left, n;
    char word[11];
    fprintf(stdout,"Enter the word: \n");
    scanf("%s",word);
    fprintf("Anagrams are:\n");
    n = strlen(word);
    val = malloc(n*sizeof(char));
    sol = malloc(n*sizeof(char));
    left = malloc(n*sizeof(char));
    if (val==NULL ||sol==NULL ||left==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    for (int i=0;i<n;i++){
        left[i] = 1;
        val[i] = word[i];
    }
    generate(val,sol,left,n,0);
    free(val);
    free(sol);
    free(left);
    return 0;
}

void generate(char *val,char *sol, int *left, int n, int pos){
    int i;
    if (pos>=n){
        for (i=0;i<n;i++){
            fprintf(stdout,"%c",sol[i]);
        }
        fprintf(stdout,"\n");
        return;
    }
    for (i=0;i<n;i++){
        if (left[i]==1){
            left[i] = 0;
            sol[pos] = val[i];
            generate(val,sol,left,n,pos+1);
            left[i] = 1;
        }
    }
    return;
}
