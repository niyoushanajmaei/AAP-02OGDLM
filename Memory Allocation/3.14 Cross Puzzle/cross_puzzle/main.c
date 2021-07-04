#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 20

char **read2D(char *name, int *p1,int *p2);
char **malloc2D(int r,int c);
void find(char **m,char **output,char *word, int r, int c);
int find_all (char **m,char **output,char *word,int x,int y,int r,int c);
void write_output (char *name,char **m,int r, int c);
void free2D(char **m,int r,int c);

int main()
{
    char **m;
    char word[MAX_S+1];
    char **output;
    int r,c;
    char *input_st = "input.txt";
    char *words_st = "words.txt";
    char *output_st = "output.txt";
    m = read2D(input_st,&r,&c);
    FILE *f_words = fopen(words_st,"r");
    if (f_words==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    output = malloc2D(r,c);
    while (fscanf(f_words,"%s",word)!= EOF){
        find(m,output,word,r,c);
    }
    write_output(output_st,output,r,c);
    free2D(output,r,c);
    free2D(m,r,c);
    fclose(f_words);
    return 0;
}


char **read2D(char *name, int *p1,int *p2){
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    fscanf(f,"%d %d\n++",p1,p2);
    int r = *p1;
    int c = *p2;
    char **m;
    m = malloc (r *sizeof(char *));
    if (m==NULL){
        fprintf(stderr,"Error opening file");
        exit(1);
    }
    for (int i=0;i<r;i++){
        m[i] = malloc(c *sizeof(char));
        if (m[i]==NULL){
            fprintf(stderr,"Error opening file");
            exit(1);
        }
    }
    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            fscanf(f,"%c",&m[i][j]);
        }
        fscanf(f,"%*c");
    }
    fclose(f);
    return m;
}

char **malloc2D(int r,int c){
    char **m;
    m = malloc (r *sizeof(char *));
    if (m==NULL){
        fprintf(stderr,"Error opening file");
        exit(1);
    }
    for (int i=0;i<r;i++){
        m[i] = malloc(c *sizeof(char));
        if (m[i]==NULL){
            fprintf(stderr,"Error opening file");
            exit(1);
        }
        for (int j=0;j<c;j++){
            m[i][j]=' ';
        }
    }
    return m;
}

void find(char **m,char **output,char *word, int r, int c){
    for(int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            if (find_all(m,output,word,i,j,r,c)){
                return;
            }
        }
    }
    return;
}

int find_all (char **m,char **output, char *word,int x,int y,int R,int C){
    int same;
    int found = 0;
    int r,c;
    int offset[2][8] = {{0,1,  1,1,0,-1,-1,-1},
                        {-1,-1,0,1,1, 1, 0,-1}};

    for (int i=0;i<8 && found == 0;i++){
        same = 0;
        for (int j=0;j<strlen(word);j++){
            r = x+j*offset[0][i];
            c = y+j*offset[1][i];
            if (r>=0 && r< R && c>=0 && c<C){
                if(word[j]==m[r][c]){
                    same++;
                }
            }
        }
        if(same == strlen(word)){
            found = 1;
            for(int j=0;j<strlen(word);j++){
                output[x+j*offset[0][i]][y+j*offset[1][i]] = word[j];
            }
        }
    }
    return found;
}

void write_output (char *name,char **m,int r, int c){
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file");
        exit(1);
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            fprintf(f,"%c",m[i][j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
    return;
}

void free2D(char **m,int r,int c){
    for(int i=0;i<r;i++){
        free(m[i]);
    }
    free(m);
    return;
}
