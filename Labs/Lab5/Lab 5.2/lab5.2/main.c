#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 20

char ***read_input(char *name,int *p1, int *p2);
char **merge_strings(char ***m,int r, int c);
void write_output(char *name, char **m,int n);

int main()
{
    int r,c;
    char ***m;
    char **merged;
    char *st_input ="input.txt";
    char *st_output = "output.txt";
    m = read_input(st_input,&r,&c);
    merged = merge_strings(m,r,c);
    write_output(st_output,merged,r*c);
    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            free(m[i][j]);
        }
        free(m[i]);
    }
    free(m);
    for (int i=0;i<r*c;i++){
        free(merged[i]);
    }
    free(merged);
    return 0;
}


char ***read_input(char *name,int *p1, int *p2){
    char ***m;
    char temp[MAX_S+1];
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    fscanf(f,"%d %d",p1,p2);
    m = malloc(*p1 * sizeof(char**));
    if (m==NULL){
        fprintf(stderr,"Error allocating memory.");
        fclose(f);
        exit(1);
    }
    for (int i=0;i<*p1;i++){
        m[i] = malloc(*p2 *sizeof(char*));
        if (m[i]==NULL){
            fprintf(stderr,"Error allocating memory.");
            fclose(f);
            exit(1);
        }
    }
    for (int i =0;i<*p1;i++){
        for (int j=0;j<*p2;j++){
            fscanf(f,"%s",temp);
            m[i][j] = strdup(temp);
        }
    }
    fclose(f);
    return m;
}

char **merge_strings(char ***m,int r, int c){
    int *min;
    min = calloc(r, sizeof(int));
    int k = 0;
    int min_id;
    char *temp;
    char **merged = malloc((r*c) * sizeof(char *));
    if (merged ==NULL || min == NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    while (k < r*c){
        temp = strdup(m[0][min[0]]);
        min_id = 0;
        for (int i=1;i<r;i++){
            if (min[i] < c && strcmp(m[i][min[i]],temp) < 0){
                temp = strdup(m[i][min[i]]);
                min_id = i;
            }
        }
        merged[k] = strdup(m[min_id][min[min_id]]);
        min[min_id]++;
        k++;
    }
    return merged;
}

void write_output(char *name, char **m,int n){
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        fclose(f);
        exit(1);
    }
    fprintf(f,"%d\n",n);
    for (int i=0;i<n;i++){
        fprintf(f,"%s\n",m[i]);
    }
    fclose(f);
    return;
}
