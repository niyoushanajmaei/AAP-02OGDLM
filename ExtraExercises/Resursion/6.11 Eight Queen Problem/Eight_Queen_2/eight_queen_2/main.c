#include <stdio.h>
#include <stdlib.h>
#define N 5

/* place queen number n on row n and check the threatened
    tiles every time we place */

int place_queen(int queen[N],int col[N],int diag[2*N-1],int revdiag[2*N-1], int pos);
void set_queen(int queen[N],int col[N],int diag[2*N-1],int revdiag[2*N-1],int r,int c);
void rem_queen(int queen[N],int col[N],int diag[2*N-1],int revdiag[2*N-1],int r,int c);

int main()
{
    int queen[N],col[N],diag[2*N-1],revdiag[2*N-1];
    for (int i=0;i<N;i++){
        queen[i]=-1;
        col[i]=-1;
    }
    for (int i=0;i<2*N-1;i++){
        diag[i]=-1;
        revdiag[i]=-1;
    }
    if (place_queen(queen,col,diag,revdiag,0)){
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                if (queen[i] == j){
                    fprintf(stdout,"Q");
                }else{
                    fprintf(stdout,".");
                }
            }
            fprintf(stdout,"\n");
        }
    }else{
        fprintf(stdout,"No solution Found.\n");
    }
    return 0;
}

int place_queen(int queen[N],int col[N],int diag[2*N-1],int revdiag[2*N-1],int pos){
    int r = pos;
    if (pos >= N){
        return 1;
    }
    for (int c =0;c<N;c++){
        if (col[c]==-1 && diag[r+c]==-1 && revdiag[N-1+r-c]==-1){
            set_queen(queen,col,diag,revdiag,r,c);
            if (place_queen(queen,col,diag,revdiag,pos+1)==1){
                return 1;
            }
            rem_queen(queen,col,diag,revdiag,r,c);
        }
    }
    return 0;
}

void set_queen(int queen[N],int col[N],int diag[2*N-1],int revdiag[2*N-1],int r,int c){
    queen[r] = c;
    col[c]  = 1;
    diag[r+c] = 1;
    revdiag[N-1+r-c] = 1;
    return;
}

void rem_queen(int queen[N],int col[N],int diag[2*N-1],int revdiag[2*N-1],int r,int c){
    queen[r] = -1;
    col[c]  = -1;
    diag[r+c] = -1;
    revdiag[N-1+r-c] = -1;
    return;
}
