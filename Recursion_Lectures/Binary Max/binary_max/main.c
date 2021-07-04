#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[4] = {10,3,40,6};
    printf("%d",max(a,0,3));
    return 0;
}

int max (int *a, int l, int r){
    int u,v,c;
    if (l>=r){
        return a[l];
    }
    c = (l+r)/2;
    u = max(a,l,c);
    v = max(a,c+1,r);
    if (u>v){
        return u;
    }else{
        return v;
    }
}
