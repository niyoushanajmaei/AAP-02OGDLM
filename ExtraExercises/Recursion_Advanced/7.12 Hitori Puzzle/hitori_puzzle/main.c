#include <stdio.h>
#include <stdlib.h>

int **read_input(char *file_name,int *ptr);
int solve(int **puzzle,int n, int r,int c,int pos);
int check_solution(int **puzzle,int n);
void write_output(char *file_name, int **sol,int n);

int main()
{
    char *input_file = "input.txt";
    char *output_file = "output.txt";
    int **puzzle;
    int n,res,found = 0;
    puzzle = read_input(input_file,&n);
    for (res = 0;res<n*n && found == 0;res++){
        if (solve(puzzle,n,0,0,res)){
            found = 1;
            fprintf(stdout,"solution: %d\n",res);
            write_output(output_file,puzzle,n);
        }
    }
    for (int i =0;i<n;i++){
        free(puzzle[i]);
    }
    free(puzzle);
    return 0;
}

int **read_input(char *file_name,int *ptr){
    int **puzzle,n;
    FILE *f= fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d",ptr);
    n = *ptr;
    puzzle = malloc(n*sizeof(int*));
    if (puzzle==NULL){
        fprintf(stderr,"Error allocating memory\n");
        exit(1);
    }
    for(int i=0;i<n;i++){
        puzzle[i] = malloc(n*sizeof(int));
        if (puzzle[i] == NULL){
            fprintf(stderr,"Error allocating memory\n");
            exit(1);
        }
    }
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            fscanf(f,"%d",&puzzle[i][j]);
        }
    }
    fclose(f);
    return puzzle;
}

int solve(int **puzzle,int n, int r0,int c0,int pos){
    int r,c,tmp;
    if (pos==0){
        return check_solution(puzzle,n);
    }
    for(r=r0;r<n;r++){
        for (c=((r==r0)?c0:0);c<n;c++){
            if (puzzle[r][c]!= -1){
                tmp = puzzle[r][c];
                puzzle[r][c] = -1;
                if (solve(puzzle,n,r,c,pos-1)){
                    return 1;
                }
                puzzle[r][c] = tmp;
            }
        }
    }
    return 0;
}

int check_solution(int **puzzle,int n){
    int mark[n];
    int r,c;
    for(r=0;r<n;r++){
        for (int i=0;i<n;i++){
            mark[i] = 0;
        }
        for (c=0;c<n;c++){
            if (puzzle[r][c]!=-1 && mark[puzzle[r][c]-1]!=0){
                return 0;
            }
            mark[puzzle[r][c]-1] = 1;
        }
    }
    for(c=0;c<n;c++){
        for (int i=0;i<n;i++){
            mark[i] = 0;
        }
        for (r=0;r<n;r++){
            if (puzzle[r][c]!=-1 && mark[puzzle[r][c]-1]!=0){
                return 0;
            }
            mark[puzzle[r][c]-1] = 1;
        }
    }
    return 1;
}

void write_output(char *file_name, int **sol,int n){
    FILE *f = fopen(file_name,"w");
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (sol[i][j]==-1){
                fprintf(f,"  ",sol[i][j]);
            }else{
                fprintf(f,"%d ",sol[i][j]);
            }
        }
        fprintf(f,"\n");
    }
    fclose(f);
    return;
}
