#include <stdio.h>
#include <stdlib.h>
#define N 5

int magicsquare_r (int m[N][N],int pos,int mark[N],int sum);
int check_answer(int m[N][N],int sum);

int main()
{
    int sum = N*((N*N)+1)/2;
    int m[N][N],mark[N*N];
    for(int i=0;i<N*N;i++){
        mark[i]=1;
        m[i/N][i%N] = -1;
    }
    if (magicsquare_r(m,0,mark,sum)){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(stdout,"%d ",m[i][j]);
            }
            fprintf(stdout,"\n");
        }
    }else{
        fprintf(stdout,"No magic square found.");
    }
    return 0;
}

int magicsquare_r(int m[N][N],int pos,int mark[N],int sum){
    if (pos == N*N){
        return check_answer(m,sum);
    }
    int tmp[N][N];
    for (int j=0;j<N;j++){
        for(int k=0;k<N;k++){
            tmp[j][k] = m[j][k];
        }
    }
    int r = pos/N;
    int c = pos % N;
    int i,s=0;
    if (c==N-1){
        for(i=0;i<N-1;i++){
            s+= m[r][i];
        }
        if (sum -s <=N*N && mark[sum-s-1]==1){
            m[r][c] = sum -s;
            mark[sum-s-1] = 0;
            if (magicsquare_r(m,pos+1,mark,sum)){
                return 1;
            }
            m[r][c] = -1;
            mark[sum-s-1] = 1;
        }
    }else{
        for (i=0;i<N*N;i++){
            if (mark[i]==1){
                m[r][c] = i+1;
                mark[i] = 0;
                if (magicsquare_r(m,pos+1,mark,sum)){
                   return 1;
                }
                m[r][c] = -1;
                mark[i] = 1;
            }
        }
    }
    return 0;
}

int check_answer(int m[N][N],int sum){
    int s,c,r;
    for (c=0;c<N;c++){
        for (r=0,s=0;r<N;r++){
            s+=m[r][c];
        }
        if (s!=sum){
            return 0;
        }
    }
    for (c=0,s=0;c<N;c++){
        for (r=0;r<N;r++){
            if (r==c){
                s+= m[r][c];
            }
        }
    }
    if (s!=sum){
        return 0;
    }
    for (c=0,s=0;c<N;c++){
        for (r=0;r<N;r++){
            if (r+c == N-1){
                s+= m[r][c];
            }
        }
    }
    if (s!=sum){
        return 0;
    }
    return 1;
}
