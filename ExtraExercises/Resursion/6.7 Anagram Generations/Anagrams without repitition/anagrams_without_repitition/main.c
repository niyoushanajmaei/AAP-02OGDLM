#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate(char *val,char *sol, int *left,int k, int n, int pos);

int main()
{
    char *val,*sol;
    int *left, n=0, k=0;
    char word[11];
    fprintf(stdout,"Enter the word: \n");
    scanf("%s",word);
    fprintf(stdout, "Anagrams are:\n");
    val = malloc(n*sizeof(char));
    sol = malloc(n*sizeof(char));
    left = malloc(n*sizeof(char));
    if (val==NULL ||sol==NULL ||left==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    for (int i=0;i<strlen(word);i++){
        int found = 0;
        for (int j=0;j<k && found ==0;j++){
            if (val[j]==word[i]){
                found =1;
                left[j]++;
            }
        }
        if (found == 0){
            val[k] = word[i];
            left[k] = 1;
            k++;
        }
    }
    n = strlen(word);
    generate(val,sol,left,k,n,0);
    free(val);
    free(sol);
    free(left);
    return 0;
}

void generate(char *val,char *sol, int *left,int k, int n, int pos){
    int i;
    if (pos>=n){
        for (i=0;i<n;i++){
            fprintf(stdout,"%c",sol[i]);
        }
        fprintf(stdout,"\n");
        return;
    }
    for (i=0;i<k;i++){
        if (left[i]>0){
            left[i] --;
            sol[pos] = val[i];
            generate(val,sol,left,k,n,pos+1);
            left[i] ++;
        }
    }
    return;
}
