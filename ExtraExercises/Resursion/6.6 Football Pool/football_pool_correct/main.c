#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num_choices;
    char *choices;
}level;

level *read_input(char *file_name,int *ptr);
void play(level *val, int *sol, int n, int pos);

int main()
{
    int n, pos = 0;
    char *file_name = "input.txt";
    level *val = read_input(file_name,&n);

    char *sol = malloc(n*sizeof(int));
    if (sol == NULL){
        fprintf(stdout,"Error allocating memory.");
        exit(1);
    }
    play(val,sol,n,pos);
    free(sol);
    free(val);
    return 0;
}

level *read_input(char *file_name,int *ptr){
    char line[4];
    char tmp;
    int length;
    level *val;
    int i, n = 0;
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stdout,"Error opening file.");
        exit(1);
    }
    while(fgets(line,4,f)!=NULL && line[0]!='\n'){
        n++;
    }
    f = fopen(file_name,"r");
    val = malloc(n *sizeof(level));
    while (fgets(line,4,f)!=NULL && line[0]!='\n'){
        sscanf(line,"%s",line);
        val[i].num_choices = strlen(line);
        val[i].choices = malloc(val[i].num_choices*sizeof(int));
        for (int j=0;line[j]!='\0';j++){
            val[i].choices[j] = line[j];
        }
        i++;
    }
    *ptr= n;
    fclose(f);
    return val;
}

void play(level *val, int *sol, int n, int pos){
    int i;
    if (pos >=n){
        for (i=0;i<n;i++){
            fprintf(stdout,"%c",sol[i]);
        }
        fprintf(stdout, "\n");
        return;
    }
    for (i=0;i<val[pos].num_choices;i++){
        sol[pos] = val[pos].choices[i];
        play(val,sol,n,pos+1);
    }
    return;
}
