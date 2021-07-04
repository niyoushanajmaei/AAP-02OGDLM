#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALIVE 1
#define DEAD 0
#define CHILD 2
#define MAX 19

typedef struct {
    char name[MAX+1];
    int state;
} organism;


organism *read_input(char *name,int *ptr);
void merge(organism *organisms, int i,int j);
int likeness (organism *organisms, int i, int j);
int max_likeness (organism *organisms,int n, int*p1,int *p2);
int evolve (organism *organisms,int n);

int main()
{
    organism *organisms;
    int n;
    char *input_file = "input.txt";
    FILE *f_out = fopen("output.txt","w");
    organisms = read_input(input_file,&n);
    int i;
    int c =1;
    if (f_out == NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }
    while (!(evolve(organisms,n))){
        fprintf(f_out,"Generation: %d\n",c);
        c++;
        for (i=0;i<n;i++){
            if (organisms[i].state != DEAD){
                fprintf(f_out,"%s\n",organisms[i].name);
                organisms[i].state=ALIVE;
            }
        }
    }
    fclose(f_out);
    free(organisms);
    return 0;
}

organism *read_input(char *name,int *ptr){
    FILE *f = fopen(name,"r");
    int i=0;
    if (f==NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }
    fscanf(f,"%d",ptr);
    organism *organisms = malloc(*ptr *sizeof(organism));
    if (organisms == NULL){
        fprintf(stderr,"Error memory allocating.\n");
        exit(1);
    }
    while(fscanf(f,"%s",organisms[i].name)==1){
        organisms[i].state = ALIVE;
        i++;
    }
    fclose(f);
    return organisms;
}

void merge(organism *organisms, int i,int j){
    for (int k=0;k<MAX;k++){
        if(organisms[i].name[k] > organisms[j].name[k]){
            organisms[i].name[k] = organisms[j].name[k];
        }
    }
    organisms[i].state=CHILD;
    organisms[j].state = DEAD;
}

int likeness (organism *organisms, int i, int j){
    int res = 0;
    for (int k=0;k<MAX;k++){
        if(organisms[i].name[k] == organisms[j].name[k]){
            res++;
        }
    }
    return res;
}

int max_likeness (organism *organisms,int n,int *p1,int *p2){
    int max=0;
    int like;
    for (int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if (organisms[i].state==ALIVE && organisms[j].state==ALIVE ){
                like = likeness(organisms,i,j);
                if (like>max){
                    *p1 =i;
                    *p2 =j;
                    max = like;
                }
            }
        }
    }
    return max;
}

int evolve (organism *organisms,int n){
    int i,j;
    int flag = 1;
    while(max_likeness(organisms,n,&i,&j)>0){
        merge(organisms,i,j);
        flag =0;
    }
    return flag;
}
