#include <stdio.h>
#include <stdlib.h>

char **read_input(char *name, int *p1, int *p2);
void search(char **m, int *p_n,int *p_min,int *p_max, int r, int c);
int snake_length (char **m,int x,int y, int r, int c);

int main()
{
    char **m;
    int r,c,n,min,max;
    char *file_st = "input.txt";
    m = read_input(file_st,&r,&c);
    search(m,&n,&min,&max,r,c);
    fprintf(stdout, "number of snakes %d\n",n);
    fprintf(stdout, "Min length: %d\n",min);
    fprintf(stdout, "Max length: %d\n",max);
    for (int i=0;i<r;i++){
        free(m[i]);
    }
    free(m);
    return 0;
}

char **read_input(char *name, int *p1, int *p2){
    char **m;
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d %d",p1, p2);
    m = malloc(*p1 *sizeof(char *));
    if (m==NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    for (int i=0;i<*p1 ;i++){
        m[i] = malloc(*p2 *sizeof(char));
        if (m[i]==NULL){
            fprintf(stderr,"Error allocating memory");
            fclose(f);
            exit(1);
        }
    }
    for (int i=0;i<*p1;i++){
        for (int j=0;j<*p2;j++){
            fscanf(f,"%c",&m[i][j]);
        }
        fscanf(f,"%*c");
    }
    fclose(f);
    return m;
}

void search(char **m, int *p_n,int *p_min,int *p_max, int r, int c){
    int min,max;
    int n = 0;
    int l;
    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            if (m[i][j]=='+'){
                l = snake_length(m,i,j,r,c);
                n++;
            }
            if (n==1){
                min = l;
                max = l;
            }else if(l>max){
                max = l;
            }else if(l<min){
                min = l;
            }
        }
    }
    *p_n = n;
    *p_min = min;
    *p_max = max;
    return;
}

int snake_length (char **m,int x,int y, int r, int c){
    int l = 1;
    int offset [2][8] = {{-1,-1,0,1,1,1,0,-1},
                         {0 ,1,1,1,0,-1,-1,-1}};
    int found = 1;
    int xp,yp;
    while (found == 1){
        found = 0;
        for (int i=0;i<8 && found ==0;i++){
            xp = x+offset[0][i];
            yp = y+offset[1][i];
            if (xp>=0 && xp <r && yp >=0 && yp < c && m[xp][yp]=='*'){
                m[x][y] = ".";
                x =xp;
                y = yp;
                l++;
                found = 1;
            }
        }
    }
    return l;
}
