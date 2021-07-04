#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
    FILE *f = fopen("file.txt","r");
    int p,q,i,t;
    int id[N];

    for(i=0;i<N;i++){
        id[i]=i;
    }
    while(fscanf(f,"%d %d",&p,&q)==2){
        if (id[p]!=id[q]){
            for(t=id[p], i=0;i<N;i++){
                // at this point we need to define t
                // if we don't we will only replace until we reach p
                if(id[i]==t){
                    id[i]=id[q];
                }
            }
        }
    }

    for(i=0;i<N;i++){
        printf("%d ",id[i]);
    }

    return 0;
}
