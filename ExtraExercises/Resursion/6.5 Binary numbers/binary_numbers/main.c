#include <stdio.h>
#include <stdlib.h>
#define BASE 2

void binary_r (int *v, int depth, int n);

int main()
{
    int *v;
    int n;
    fprintf(stdout,"Enter n:\n");
    scanf("%d",&n);
    v = malloc (n *sizeof(int));
    if (v==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    fprintf(stdout,"Binary numbers:\n");
    binary_r(v,0,n);
    free(v);
    return 0;
}

void binary_r (int *v, int depth, int n){
    if (depth >=n){
        for (int i=0;i<n;i++){
            fprintf(stdout,"%d",v[i]);
        }
        fprintf(stdout,"\n");
        return;
    }
    for (int i=0;i<BASE;i++){
        v[depth] = i;
        binary_r(v,depth+1,n);
    }
    return;
}
