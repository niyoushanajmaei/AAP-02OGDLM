#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
    FILE *f = fopen("file.txt","r");
    int p,q,i;
    int id[N],sz[N];

    for(i=0;i<N;i++){
        id[i]=i;
        sz[i] = 1;
    }
    while(fscanf(f,"%d %d",&p,&q)==2){
        while(id[p]!=p){
            p = id[p];
        }
        while(id[q]!=q){
            q = id[q];
        }
        if (p!=q){
            if(sz[p]<=sz[q]){
                id[p] = q;
                sz[q] += sz[p];
            }else {
                id[q] = p;
                sz[p] += sz[q];
            }
        }
    }

    for(i=0;i<N;i++){
        printf("%d ",id[i]);
    }

    return 0;
}
