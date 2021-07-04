#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ST 30

typedef struct{
    char name[MAX_ST+1];
    int code;
    int laps;
    float *times;
    float average;
}cyclist;

cyclist *read_input(char *name,int *p);
void run_commands(cyclist *cyclists,int n);
void list(cyclist *cyclists,int n);
void details(cyclist *cyclists,char *name,int n);
void best(cyclist *cyslists,int n);


int main()
{
    cyclist *cyclists;
    int n;
    char st[31];
    fprintf(stdout,"Enter the file name: ");
    //memory allocate st if defined dynamically?
    scanf("%s",st);
    cyclists = read_input(st,&n);
    run_commands(cyclists,n);

    for(int i=0;i<n;i++){
        free(cyclists[i].times);
    }
    free(cyclists);
    return 0;
}

cyclist *read_input(char *name,int *p){
    cyclist *cyclists;
    FILE *f = fopen(name,"r");
    float sum = 0;
    if(f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    fscanf(f,"%d",p);
    cyclists = malloc(*p *sizeof(cyclist));
    if (cyclists==NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    for (int i=0;i<*p;i++){
        fscanf(f,"%s %d %d",cyclists[i].name,&cyclists[i].code,&cyclists[i].laps);
        cyclists[i].times = malloc(cyclists[i].laps * sizeof(float));
        if (cyclists[i].times == NULL){
            fprintf(stderr,"Error allocating memory");
            fclose(f);
            exit(1);
        }
        sum = 0;
        for(int j=0;j<cyclists[i].laps;j++){
            fscanf(f,"%f",&(cyclists[i].times[j]));
            sum += cyclists[i].times[j];
        }
        cyclists[i].average = sum / cyclists[i].laps;
    }
    fclose(f);
    return cyclists;
}

void run_commands(cyclist *cyclists,int n){
    char temp[40];
    char command [8];
    do{
        fprintf(stdout,"command? ");
        int done =0;
        while (done ==0){
            gets(temp);
            sscanf(temp,"%s",command);
            if(!strcmp(command,"list")){
                list(cyclists,n);
                done = 1;
            }else if(!strcmp(command,"details")){
                char name[MAX_ST+1];
                sscanf(temp,"%*s %s",name);
                details(cyclists,name,n);
                done = 1;
            }else if(!strcmp(command,"best")){
                best(cyclists,n);
                done = 1;
            }
        }
    }while (strcmp(command,"stop"));
}

void list(cyclist *cyclists,int n){
    fprintf(stdout,"Number of cyclists: %d\n",n);
    for(int i=0; i<n;i++){
        fprintf(stdout,"%d . name: %s  id: %d  laps: %d\n",i+1,cyclists[i].name,cyclists[i].code,cyclists[i].laps);
    }
    return;
}

void details(cyclist *cyclists,char *name,int n){
    for (int i=0;i<n;i++){
        if (!strcmp(name,cyclists[i].name)){
            fprintf(stdout,"id: %d  laps: %d  times: ",cyclists[i].code,cyclists[i].laps);
            for (int j=0;j<cyclists[i].laps;j++){
                fprintf(stdout,"%.2f ",cyclists[i].times[j]);
            }
            fprintf(stdout,"\n");
            return;
        }
    }
}

void best(cyclist *cyclists,int n){
    int min = 0;
    for (int i=1;i<n;i++){
        if(cyclists[i].average<cyclists[min].average){
            min = i;
        }
    }
    fprintf(stdout,"name: %s  id: %d  times: ",cyclists[min].name, cyclists[min].code);
    for(int i=0;i<cyclists[min].laps;i++){
        fprintf(stdout,"%.2f ",cyclists[min].times[i]);
    }
    fprintf(stdout,"average: %.2f\n",cyclists[min].average);
    return;
}

