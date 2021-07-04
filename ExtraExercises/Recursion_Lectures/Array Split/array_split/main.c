#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v[8] = {1,2,3,4,5,6,7,8};
    split(v ,0, 7);
    return 0;
}

void split(int *v,int l,int r){
    for (int i=l;i<=r;i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    if (l >= r){
        return;
    }
    int c = (l+r)/2;
    split(v,l,c);
    split(v,c+1,r);
    return;
}
