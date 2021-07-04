#include <stdio.h>
#include <stdlib.h>
#define DIM 20

void read_file(char *file_name, int m[DIM][DIM], int *ptr_r, int *ptr_c);
void expand (int m[DIM][DIM], int x,int y, int id);
void write_file (char *file_name,int m[DIM][DIM], int r,int c);

int main()
{
    char *input_file = "input.txt";
    char *output_file = "output.txt";
    int m [DIM][DIM];
    int r,c, n = 1;
    read_file(input_file,m,&r,&c);
    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            if (m[i][j] == 0){
                expand(m,i,j,n);
                n++;
            }
        }
    }
    write_file(output_file,m,r,c);
    fprintf(stdout,"number of regions is: %d",n-1);
    return 0;
}


void read_file(char *file_name, int m[DIM][DIM], int *ptr_r, int *ptr_c){
    char line[DIM+2];
    int r = 0, c= 0;
    FILE *f = fopen(file_name,"r");
    if (f ==NULL){
        fprintf(stderr,"Error opening file");
        exit(1);
    }
    while(fgets(line,DIM+2,f)!=NULL){
        c = 0;
        while (line[c]=='.' || line[c]=='*'){
            if (line[c]=='*'){
                m[r][c] = -1;
            }else{
                m[r][c] = 0;
            }
            c++;
        }
        r++;
    }
    *ptr_r = r;
    *ptr_c = c;
    fclose(f);
    return;
}

void expand (int m[DIM][DIM], int x,int y, int id){
    int offset[2][4] = {{0, 1, 0, -1},{-1, 0, 1, 0}};
    if (m[x][y] != 0){
        return;
    }
    m[x][y] = id;
    for (int i=0;i<4;i++){
        expand(m,x+offset[0][i],y+offset[1][i],id);
    }
    return;
}

void write_file (char *file_name,int m[DIM][DIM], int r,int c){
    FILE *f = fopen(file_name,"w");
    for (int i =0;i<r;i++){
        for (int j = 0; j <c;j++){
            if (m[i][j]==-1){
                fprintf(f,"*");
            }else{
                fprintf(f,"%d",m[i][j]);
            }
        }
        fprintf(f,"\n");
    }
    fclose(f);
    return;
}
