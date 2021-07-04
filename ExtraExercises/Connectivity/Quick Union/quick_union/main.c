#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
    FILE *f = fopen("file.txt","r");
    int p,q,i;
    int id[N];

    for(i=0;i<N;i++){
        id[i]=i;
    }
    while(fscanf(f,"%d %d",&p,&q)==2){
        while(id[p]!=p){
            p = id[p];
        }
        while(id[q]!=q){
            q = id[q];
        }
        if (id[p]!=id[q]){
            id[p] = q;
        }
    }

    for(i=0;i<N;i++){
        printf("%d ",id[i]);
    }

    return 0;
}
