#include <stdio.h>
#include <stdlib.h>
#define N 7
#define OUT -1
#define FULL 1
#define EMPTY 0

int move(int board[N][N],int moves[31][4], int n);
void display(int moves[31][4]);

int main()
{
    int moves[31][4],board[N][N];
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if ((i<2 && j<2)||(i>N-3 && j<2)||(i>N-3 && j>N-3)||(i<2 && j>N-3)){
                board[i][j] = OUT;
            }else{
                board[i][j] = FULL;
            }
        }
    }
    if (move(board,moves,0)==31){
        display(moves);
    }else{
        fprintf(stdout,"No solution found");
    }
    return 0;
}

int move(int board[N][N],int moves[31][4], int n){
    int offset[2][4] = {{1,-1,0,0},{0,0,1,-1}};
    int ii,jj,iii,jjj;
    if (n == 31){
        return n;
    }
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if (board[i][j]==FULL){
                for(int k=0;k< 4;k++){
                   ii = i+offset[0][k];
                   jj = j+offset[1][k];
                   iii = i+2*offset[0][k];
                   jjj = j+2*offset[1][k];

                   if(board[ii][jj]==FULL && board[iii][jjj] ==EMPTY){
                        board[i][j] = EMPTY;
                        board[ii][jj] = EMPTY;
                        board[iii][jjj] = FULL;
                        if (move(board,moves,n+1)!= -1){
                            moves[n][0] = i;
                            moves[n][1] = j;
                            moves[n][2] = iii;
                            moves[n][2] = jjj;
                            return n;
                        }
                        board[i][j] = FULL;
                        board[ii][jj] = FULL;
                        board[iii][jjj] = EMPTY;
                   }
                }
            }
        }
    }
    return -1;
}

void display(int moves[31][4]){
    for (int i=0;i<31;i++){
        fprintf("%d %d -> %d %d\n",moves[i][0],moves[i][1],moves[i][2],moves[i][3]);
    }
    return;
}
