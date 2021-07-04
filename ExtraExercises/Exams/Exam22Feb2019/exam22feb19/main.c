#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

/*
    store museums in a list
    visitors in a BST
    each visitor has a list of reservations
*/

typedef struct museum_s museum;
typedef struct person_s person;
typedef struct reservation_s reservation;
typedef struct time_s time;
typedef struct timest_s timesl;

struct museum_s{
    char *name;
    timesl *time_slot;
    museum *next;
};

struct person_s{
    char *name;
    reservation *reservations;
    person *left;
    person *right;
};

struct reservation_s{
    char *museum;
    int date;
    timesl *time_slot;
    reservation *next
};

struct timesl_s{
    int n;
    time start;
    time finish
    timesl *next;
};

struct time_s{
    int hour;
    int minute;
};

museum *read_file (char *file_name);
person *people_init(void);
void add_reservation(person *people, char *name,reservation *res);
int is_available(reservation *res, museum *museums);
person *find_person(person *people, char *name);
void write_reservations(person *people, char *name);
void quit(museum *museums, person *people);
time new_time(int h1,int h2, int m1, int m2);

int main()
{
    museum *museums;
    person *people;
    reservation *tmp;
    timesl *tsl;
    int stop = 0, cmd;
    char name [MAX], museum[MAX];
    int h1,m1,h2,m2;
    char *file_name = "input.txt";

    museums = read_file(file_name);
    people = people_init();

    while(stop == 0){
        fprintf("Enter 1 to add a new reservation, 2 to print all reservations, 0 to quit.\n");
        scanf("%d",&cmd);
        if(cmd==1){
            tmp = malloc(sizeof(reservation));
            tsl = malloc(sizeof(timesl));
            if(tmp==NULL || timesl == NULL){
                fprintf(stderr,"Error allocating memory.");
                exit(1);
            }
            tmp->time_slot = tsl;
            fprintf(stdout,"Enter -museum_name, date, starting time, finishing time, number_of_visitors-\n");
            scanf("%s, %d, %d.%d-%d.%d, %d, %s", museum,&(tmp->date),&h1,&m1,&h2,&m2,&n, )
        }else if (cmd==2){
            fprintf(stdout,"Enter the name of the visitor:\n");
            scanf("%s",name);
            write_reservations(people,name);
        }else if(cmd==0){
            stop = 1;
        }else{
            fprintf(stdout,"Wrong command.\n");
        }
    }

    quit(museums, people);
    return 0;
}

museum *read_file (char *file_name){
    museum *museums;
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }


    fclose(f);
    return museums;
}

void add_reservation(person *people, char *name,reservation *res);
person *people_init(void);
int is_available(reservation *res, museum *museums);
person *find_person(person *people, char *name);
void write_reservations(person *people, char *name);
void quit(museum *museums, person *people);
time new_time(int h1,int h2, int m1, int m2);
