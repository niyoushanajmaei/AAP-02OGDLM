#include <stdio.h>
#include <stdlib.h>

int *merge3(int *a,int *b,int *c, int na,int nb,int nc);
int min3 (int a, int b,int c, int *pa, int *pb,int *pc);
int min2 (int a,int b, int *pa, int *pb);

int main()
{
    int a[5] = {1,2,5,6,10};
    int b[4] = {3,7,8,12};
    int c[1] = {2};
    int *res = merge3(a,b,c,5,4,1);
    for (int i=0;i<10;i++){
        fprintf(stdout,"%d ",res[i]);
    }
    return 0;
}

int *merge3(int *a,int *b,int *c, int na,int nb,int nc){
    int *res = malloc((na+nb+nc) * sizeof(int));
    int ia=0,ib=0,ic=0;
    int i;
    if (res == NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    for (i=0;i<na+nb+nc;i++){
        if (ia<na && ib<nb && ic<nc){
            res[i] = min3(a[ia],b[ib],c[ic],&ia,&ib,&ic);
        }
        else if (ia >= na){
            res [i] = min2(b[ib],c[ic],&ib,&ic);
        }
        else if (ib >= nb){
            res [i] = min2(a[ia],c[ic],&ia,&ic);
        }
        else if (ic >= nc){
            res [i] = min2(b[ib],a[ia],&ib,&ia);
        }
    }
    while(ia<na){
        res[i++] = a[ia++];
    }
    while(ib<nb){
        res[i++] = b[ib++];
    }
    while(ic<nc){
        res[i++] = c[ic++];
    }
    return res;
}

int min3 (int a, int b,int c, int *pa, int *pb,int *pc){
    if (a<=b && a<=c){
        (*pa)++;
        return a;
    }
    else if (b<a &&b<=c){
        (*pb)++;
        return b;
    }
    else {
        (*pc)++;
        return c;
    }
}

int min2 (int a,int b, int *pa, int *pb){
    if (a<=b){
        (*pa)++;
        return a;
    }
    else{
        (*pb)++;
        return b;
    }
}
