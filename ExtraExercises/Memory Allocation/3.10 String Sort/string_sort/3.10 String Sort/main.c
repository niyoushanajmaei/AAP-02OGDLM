#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 60

char **read_input(char *name,int *p);
void sort(char **strings,int n);
void write_output (char *name,char **strings, int n);


int main()
{
    char *st_input = "input.txt";
    char *st_output = "output.txt";
    char **strings;
    int n;
    strings = read_input(st_input,&n);
    sort(strings,n);
    write_output(st_output,strings,n);

    for (int i=0;i<n;i++){
        free(strings[i]);
    }
    free(strings);
    return 0;
}

char **read_input(char *name,int *p){
    char ** strings;
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    int i=0;
    while (fscanf(f,"%*s")!=EOF){
        i++;
    }
    *p = i;
    f = fopen(name,"r");
    strings = malloc(*p *sizeof(char*));
    if (strings==NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    for (int i=0;i<*p;i++){
        strings[i] = malloc((MAX_S+1) * sizeof(char));
        if (strings[i]==NULL){
            fprintf(stderr,"Error allocating memory");
            fclose(f);
            exit(1);
        }
    }
    for (int i=0;i<*p && fscanf(f,"%s",strings[i]) != EOF;i++);
    fclose(f);
    return strings;
}

void sort(char **strings,int n){
    char *temp [MAX_S+1];
    int i,j;
    for(i=1;i<n;i++){
        strcpy(temp,strings[i]);
        for (j=i-1;j>=0 && strcmp(strings[j],temp)>0;j--){
            strcpy(strings[j+1],strings[j]);
        }
        strcpy(strings[j+1],temp);
    }
    return;
}

void write_output (char *name,char **strings, int n){
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    for (int i=0;i<n;i++){
        fprintf(f,"%s\n",strings[i]);
    }
    fclose(f);
}
