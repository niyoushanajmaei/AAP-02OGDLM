#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 51
#define ID_LENGTH 17
#define DATE_LENGTH 11

typedef struct employee_s{
    char *name;
    char *date;
    char *id;
    int salary;
    struct employee_s *next;
    struct employee_s *prev;
}employee;

employee *read_input(char *file_name);
void search (employee *list,char *name, char *key);
void display(employee *node);
void free_memory(employee *hptr);
employee *new_emloyee(void);

int main(int argc, char *argv[])
{
    employee *list;
    if (argc != 4){
        fprintf(stderr,"Wrong number of arguments.");
        exit(1);
    }
    list = read_input(argv[1]);
    search(list, argv[2],argv[3]);
    free_memory(list);
    return 0;
}

employee *read_input(char *file_name){
    employee *hptr =NULL, *tmp;
    char t_name[MAX],t_id[ID_LENGTH],t_date[DATE_LENGTH], line[ 3* MAX];
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    while (fgets(line,3*MAX,f)!=NULL){
        tmp = new_emloyee();
        sscanf(line,"%s %s %s %d",t_name,t_id,t_date,&tmp->salary);
        tmp->name = strdup(t_name);
        tmp->id = strdup(t_id);
        tmp->date = strdup(t_date);

        if (hptr == NULL){
            tmp-> next = NULL;
            tmp->prev = NULL;
            hptr = tmp;
        }else{
            tmp->prev = NULL;
            tmp->next = hptr;
            hptr->prev = tmp;
            hptr = tmp;
        }
    }
    fclose(f);
    return hptr;
}

void search (employee *list,char *name, char *key){
    employee *tmp, *ptr;
    int found = 0;
    for (ptr=list;ptr !=NULL && found == 0;ptr = ptr->next){
        if (strcmp(name,ptr->name)==0){
            tmp = ptr;
            found = 1;
            display(tmp);
            for (int i=0;i<strlen(key);i++){
                if (key[i]=='+'){
                    if (tmp->next != NULL){
                        tmp = tmp->next;
                        display(tmp);
                    }else{
                        display(tmp);
                    }
                }else{
                    if (tmp->prev != NULL){
                        tmp = tmp->prev;
                        display(tmp);
                    }else{
                        display(tmp);
                    }
                }
            }
        }
    }
    return;
}

void display(employee *node){
    printf("%s %s %s %d\n",node->name,node->id,node->date, node->salary);
    return;
}

void free_memory(employee *hptr){
    while (hptr !=NULL){
        employee *tmp;
        tmp = hptr;
        hptr = hptr->next;
        free(tmp->name);
        free(tmp->date);
        free(tmp->id);
        free(tmp);
    }
    return;
}

employee *new_emloyee(void){
    employee *tmp = malloc(sizeof(employee));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    return tmp;
}
