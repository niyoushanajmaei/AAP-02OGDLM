#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 4


typedef struct element_s{
    float value;
    int used;
}element_t;

void min_dif_r(float arr[N],float res[N],element_t elements[N],int pos,int min);
float check_sol(float arr[N]);

int main()
{
    float arr[N] = {+10,-5,+7,-8};
    float res[N];
    element_t elements[N];
    for (int i=0;i<N;i++){
        elements[i].used = 0;
        elements[i].value = arr[i];
        res[i] = arr[i];
    }
    min_dif_r(arr,res,elements,0,INT_MAX);
    for (int i=0;i<N;i++){
        fprintf(stdout,"%.2f ",res[i]);
    }
    return 0;
}

void min_dif_r(float arr[N],float res[N],element_t elements[N],int pos,int min){
    if(pos == N){
        if (check_sol(arr)<check_sol(res)){
            for (int i=0;i<N;i++){
                res[i] = arr[i];
            }
        }
        return;
    }
    for (int i=0;i<N;i++){
        if (elements[i].used==0){
            elements[i].used=1;
            arr[pos] = elements[i].value;
            min_dif_r(arr,res,elements,pos+1,min);
            elements[i].used =0;
        }
    }
    return;
}

float check_sol(float arr[N]){
    float max =0,min =0,cur = 0;
    for (int i=0;i<N;i++){
        cur += arr[i];
        if (cur <min)
            min = cur;
        if (cur >max)
            max = cur;
    }
    return max-min;
}
