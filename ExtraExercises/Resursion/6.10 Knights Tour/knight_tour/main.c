#include <stdio.h>
#include <stdlib.h>
#define n 8

/*
    board : tiles met are marked with 1, other ones with 0
    x and y: the initial positions
    moves: the array of the offsets
    available: whether possible positions have been already visited
    r: number of tiles met so far
    board: path taken so far is
*/
int knight_tour(int board[n][n],int x,int y,int moves[2][8],int r, int sol[n*n][2]);

int main()
{
    int x,y;
    int board[n][n],sol[n*n][2];
    fprintf(stdout,"Enter the initial coordinates:\n");
    scanf("%c %d",&y,&x);
    x = 8-x;
    y = y -'a';
    fprintf(stdout,"A Knight tour:\n");
    int moves[2][8] = {{-2,-1,1,2,2, 1,-1,-2},
                        {1, 2,2,1,-1,-2,-2,-1}};
    for(int i=0;i<n;i++){
        for (int j = 0;j<n;j++){
            board[i][j] = 0;
        }
    }
    sol[0][0]= x;
    sol[0][1] = y;
    board[x][y] =1 ;
    int res = knight_tour(board, x,y,moves,1,sol);
    if (res==-1){
        fprintf(stdout,"no knight tour found");
    }
    return 0;
}

int knight_tour(int board[n][n],int x, int y,int moves[2][8],int r,int sol[n*n][2]){
    int c = 0;
    int xx,yy;
    for (int i=0;i<8;i++){
        xx = x+moves[0][i];
        yy = y+moves[1][i];
        if(xx >=0 && yy>=0 && xx<n && yy<n && board[xx][yy]==0){
            c++;
        }
    }
    if (c==0){
        //no more available moves.
        return -1;
    }
    if (r >= n*n -1){
        //solution found.
        for (int i=0;i<8;i++){
            xx = x+moves[0][i];
            yy = y+moves[1][i];
            if (xx >=0 && yy>=0 && xx<n && yy<n && board[xx][yy]==0){
                board[xx][yy] =1;
                sol[r][0] = xx;
                sol[r][1] = yy;
                for (int i=0;i<n*n;i++){
                    fprintf(stdout,"%d.  %c %d\n",i+1,sol[i][1]+'a', 8-sol[i][0]);
                }
                return 0;
            }
        }
    }
    for (int i=0;i<8;i++){
        xx = x+moves[0][i];
        yy = y+moves[1][i];
        if (xx >=0 && yy>=0 && xx<n && yy<n && board[xx][yy]==0){
            board[xx][yy] =1;
            sol[r][0] = xx;
            sol[r][1] = yy;
            if (knight_tour(board,xx,yy,moves,r+1,sol)==0){
                return 0;
            }
            board[xx][yy] = 0;
        }
    }
    return -1;
}
