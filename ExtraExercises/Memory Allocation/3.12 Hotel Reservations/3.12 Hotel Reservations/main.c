#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_S 60
#define DAY 365

typedef struct{
    char name [MAX_S+1];
    char surname [MAX_S+1];
    int in;
    int out;
    int nights[DAY];
} guest;

guest *read_input(char *name,int *p, int *min, int *max);
int rooms(guest *guests,int n,int min, int max);
void write_output(char *name,int rooms,guest *guests,int n,int min, int max);

int main()
{
    char *st_input = "input.txt";
    char *st_output = "output.txt";
    guest *guests;
    int n,room;
    int min = INT_MAX;
    int max = 0;
    guests = read_input(st_input,&n,&min,&max);
    room = rooms(guests,n,min,max);
    write_output(st_output,room,guests,n,min,max);

    free(guests);
    return 0;
}

guest *read_input(char *name,int *p,int *min,int *max){
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file");
        exit(1);
    }
    guest *guests;
    fscanf(f,"%d",p);
    guests = malloc(*p *sizeof(guest));
    if (guests == NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    for (int i=0; i<*p  ;i++){
        fscanf(f,"%s %s %d %d",guests[i].name,guests[i].surname,&guests[i].in,&guests[i].out);
        if (guests[i].in <*min){
            *min = guests[i].in;
        }
        if (guests[i].out - 1 >*max){
            *max = guests[i].out - 1;
        }
        for(int j=0;j<DAY;j++){
            if ( j >=guests[i].in && j< guests[i].out){
                guests[i].nights[j] = 1;
            }else{
                guests[i].nights[j] = 0;
            }
        }
    }
    fclose(f);
    return guests;
}

int rooms(guest *guests,int n,int min,int max){
    int arr[DAY];
    for (int i=min;i<max;i++){
        arr[i] = 0;
    }
    int room = 0;
    for (int i=0;i<n;i++){
        for (int j=guests[i].in;j<guests[i].out;j++){
            arr[j]++;
        }
    }
    for(int i=min;i<max;i++){
        if (arr[i]>room){
            room = arr[i];
        }
    }
    return room;
}

void write_output(char *name,int rooms,guest *guests,int n,int min, int max){
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file");
        exit(1);
    }
    fprintf(f,"Number of required rooms = %d\n",rooms);
    for (int i=0;i<rooms;i++){
        fprintf(f,"Room number %d\n",i+1);
        for (int j=min;j<=max;j++){
            for (int k=0;k<n;k++){
                if (guests[k].in >=min && guests[k].out-1 <= max && guests[k].nights[j] ==1){
                    fprintf(f,"day=%d %s %s\n",j,guests[k].name,guests[k].surname);
                    guests[k].nights[j]= 0;
                    break;
                }
            }
        }
    }
    return;
}

