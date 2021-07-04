#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char **read_input(char *file_name, int *ptr_r, int *ptr_c);
void find_init(char **maze,int r,int c, int *ptr_r,int *ptr_c);
int find_one_r(char **maze, int r,int c,int r0,int c0,int *ptr_l);
void write_maze(char **maze, int r,int c);
int find_all_r(char **maze, int r,int c,int r0,int c0,int *ptr_l);
int find_best_r(char **maze, int r,int c,int r0,int c0,int *ptr_l);


int main()
{
    int r,c,len =0,r0,c0;
    char cmd;
    char **maze;
    char *input_file = "input.txt";
    fprintf(stdout,"Enter 'o' for one path, 'a' for all paths and 's' for the shortest path\n");
    scanf("%c",&cmd);
    maze = read_input(input_file,&r,&c);
    find_init(maze,r, c,&r0,&c0);
    if (cmd =='o'){
        find_one_r(maze,r,c,r0,c0,&len);
        if (len){
            fprintf(stdout,"A solution of length %d was found.\n",len);
            write_maze(maze,r,c);
        }else{
            fprintf(stdout,"No path found.\n");
        }
    }else if(cmd == 'a'){
        if(find_all_r(maze,r,c,r0,c0,&len)==0){
            fprintf(stdout,"No path found.\n");
        }
    }else if (cmd =='s'){

    }else{
        fprintf(stdout,"wrong command.");
    }
    for (int i=0;i<r;i++){
        free(maze[i]);
    }
    free(maze);
    return 0;
}


char **read_input(char *file_name, int *ptr_r, int *ptr_c){
    int r,c,i;
    char **maze;
    char *line,*tmp;
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    fscanf(f,"%d %d",&r,&c);
    line = malloc ((c+1)*sizeof(char));
    tmp = malloc ((c+1)*sizeof(char));
    maze = malloc (r *sizeof(char*));
    if (line ==NULL || tmp == NULL || maze ==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    for(i=0;i<r;i++){
        maze[i] = malloc((c+1)*sizeof(char));
        if (maze[i]==NULL){
            fprintf(stderr,"Error allocating memory");
            exit(1);
        }
    }
    i=0;
    fgets(tmp,"%s",f);
    while(fgets(line,"%s",f)!=NULL){
        strcpy(maze[i++],line);
    }
    *ptr_r = r;
    *ptr_c = c;
    return maze;
}

int find_one_r(char **maze, int r,int c,int x0,int y0,int *ptr_l){
    int moves_x[4] = {1,-1,0,0};
    int moves_y[4] = {0,0,1,-1};
    int x,y;
    for (int i=0;i<4;i++){
        x = x0+moves_x[i];
        y = y0+moves_y[i];
        if(maze[x][y]=='#'){
            return 1;
        }
    }
    for (int i=0;i<4;i++){
        x = x0+moves_x[i];
        y = y0+moves_y[i];
        if(maze[x][y]==' '){
            maze[x][y]='.';
            (*ptr_l)++;
            if (find_one_r(maze,r,c,x,y,ptr_l)){
                return 1;
            }
            maze[x][y] = ' ';
            (*ptr_l)--;
        }
    }
    return 0;
}

void find_init(char **maze,int r, int c, int *ptr_r,int *ptr_c){
    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            if(maze[i][j]=='@'){
                *ptr_r = i;
                *ptr_c = j;
                return;
            }
        }
    }
}

void write_maze(char **maze, int r,int c){
    for (int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            fprintf(stdout,"%c",maze[i][j]);
        }
        fprintf(stdout,"\n");
    }
}
