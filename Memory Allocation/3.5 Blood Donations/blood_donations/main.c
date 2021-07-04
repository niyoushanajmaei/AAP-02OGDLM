#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 20
#define L 5

typedef struct Doner{
    char name[MAX_S+1];
    char surname[MAX_S+1];
    char id [L+1];
    int amount;
    int c;
}doner;

doner *read_voluntary(char *name, int *ptr);
void read_donation(char *name, doner *doners, int n);
int search_doner(doner *doners,char id[], int n);
void display_doner(doner *doners, int n);

int main()
{
    char *name_donation = "donation.txt";
    char *name_voluntary = "voluntary.txt";
    int n=0;
    doner *doners = read_voluntary(name_voluntary,&n);
    read_donation(name_donation,doners, n);
    display_doner(doners,n);
    free(doners);
    return 0;
}

doner *read_voluntary(char *name, int *ptr){
    FILE *f = fopen(name,"r");
    if (f ==NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }
    int i;
    char *temp;
    while(fscanf(f,"%s %*s %*s %*s",temp)==1){
        (*ptr)++;
    }
    doner *doners = malloc (*ptr * sizeof(doner));
    if (doners == NULL){
        fprintf(stderr,"Error allocating memory\n");
        exit(1);
    }
    fclose(f);
    f = fopen(name,"r");
    for(i = 0;fscanf(f,"%s %*s %s %s",doners[i].id,doners[i].name,doners[i].surname)==3;i++){
        doners[i].c=0;
        doners[i].amount = 0;
    }
    fclose(f);
    return doners;
}

void read_donation(char *name,doner *doners, int n){
    int j;
    char temp [L+1];
    int t;
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }
    while (fscanf(f,"%s %d",temp,&t)==2){
        int done = 0;
        for (int i=0;i<n && done ==0;i++){
            j = search_doner(doners,temp,n);
            doners[j].c ++;
            doners[j].amount += t;
            done = 1;
        }
    }
    fclose(f);
}

int search_doner(doner *doners,char id[], int n){
    for(int i=0;i<n;i++){
        if (strcmp(doners[i].id,id)==0){
            return i;
        }
    }
    return -1;
}

void display_doner(doner *doners, int n){
    for (int i=0;i<n;i++){
        printf("%s %s %s: %d donation(s) - %d cc\n",doners[i].id, doners[i].name,doners[i].surname,doners[i].c,doners[i].amount);
    }
}
