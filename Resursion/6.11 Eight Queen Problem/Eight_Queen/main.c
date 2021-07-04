#include <stdio.h>
#include <stdlib.h>
#define N 8

/* the brute force approach
    Selecting every possible 8 positions. */

int place_queen(int board[N][N], int r0,int c0,int pos);
int check_solution(int board[N][N]);

int main()
{
    int board[N][N];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            board[i][j] = 0;
        }
    }
    if (place_queen(board,0,-1,0)){
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                fprintf(stdout,"%d ",board[i][j] );
            }
            fprintf(stdout,"\n");
        }
    }else{
        fprintf(stdout,"No solution Found.\n");
    }
    return 0;
}

int place_queen(int board[N][N],int r0,int c0 ,int pos){
    if (pos >= N){
        return check_solution(board);
    }
    for (int r = r0;r<N;r++){
        for (int c = ((r==r0)?(c0+1):0);c<N;c++){
            board[r][c] = pos+1;
            if (place_queen(board,r,c,pos+1)==1){
                return 1;
            }
            board[r][c] = 0;
        }
    }
    return 0;
}

/* check whether the solution is valid. */
int check_solution(int board[N][N]){
    /* check rows*/
    int n,r,c,d;
    for (r = 0;r<N;r++){
        for(n=0, c = 0;c<N;c++){
            if(board[r][c]){
                n++;
            }
        }
        if (n>1){
            return 0;
        }
    }

    /* check cols*/
    for (c = 0;c<N;c++){
        for(n=0, r = 0;r<N;r++){
            if(board[r][c]){
                n++;
            }
        }
        if (n>1){
            return 0;
        }
    }

    /* check diagonals*/

    for (d = 0;d<2*N-1;d++){
        for(n=0,r = 0;r<N;r++){
            c = d-r;
            if(c>=0 && c< N && board[r][c]){
                n++;
            }
        }
        if (n>1){
            return 0;
        }
    }

    /*check inverse diagonals*/

    for (d = 0;d<2*N-1;d++){
        for(n=0 ,r = 0;r<N;r++){
            c = r-d+N-1;
            if(c>=0 && c< N && board[r][c]){
                n++;
            }
        }
        if (n>1){
            return 0;
        }
    }
    return 1;
}
