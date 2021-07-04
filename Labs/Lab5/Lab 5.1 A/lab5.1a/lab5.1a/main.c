#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 60

typedef struct{
    char *str;
}string;


string *read_input(char *name,int *p);
void sort(string *strings,int n);
void write_output (char *name,string *strings, int n);


int main()
{
    char *st_input = "input.txt";
    char *st_output = "output.txt";
    string *strings;
    int n;
    strings = read_input(st_input,&n);
    sort(strings,n);
    write_output(st_output,strings,n);

    for (int i=0;i<n;i++){
        free(strings[i].str);
    }
    free(strings);
    return 0;
}

string *read_input(char *name,int *p){
    string *strings;
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    fscanf(f,"%d",p);
    f = fopen(name,"r");
    strings = malloc(*p *sizeof(string));
    if (strings==NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    for (int i=0;i<*p;i++){
        strings[i].str = malloc((MAX_S+1) * sizeof(char));
        if (strings[i].str==NULL){
            fprintf(stderr,"Error allocating memory");
            fclose(f);
            exit(1);
        }
    }
    for (int i=0;i<*p && fscanf(f,"%s",strings[i].str) != EOF;i++);
    fclose(f);
    return strings;
}

void sort(string *strings,int n){
    char *temp [MAX_S+1];
    int i,j;
    for(i=1;i<n;i++){
        strcpy(temp,strings[i].str);
        for (j=i-1;j>=0 && strcmp(strings[j].str,temp)>0;j--){
            strcpy(strings[j+1].str,strings[j].str);
        }
        strcpy(strings[j+1].str,temp);
    }
    return;
}

void write_output (char *name,string *strings, int n){
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    for (int i=0;i<n;i++){
        fprintf(f,"%s\n",strings[i].str);
    }
    fclose(f);
}
