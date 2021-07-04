#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 20
#define ROW_LENGTH 100

typedef struct node_s{
    char *name;
    float mark;
    struct node_s *next;
}node;

node *new_element(void);
node *read_input(node *hptr, char* name);
void sort_m(node *hptr);
void sort_n(node *hptr);
void write_output(char *name, node *hptr);
void free_memory(node *hptr);


int main()
{
    // in place sorting of the list
    node *hptr ;
    char cmd[MAX_S+1];
    char file_name[MAX_S+1];
    int stop = 0;

    while (stop == 0){
        fprintf(stdout,"Commands:\n");
        fprintf(stdout,"read filename -> read the file\n");
        fprintf(stdout,"writeN filename -> sorts by name and writes in the file\n");
        fprintf(stdout,"writeM filename -> sorts by mark and writes in the file\n");
        fprintf(stdout,"stop -> terminates the program\n");
        scanf("%s",cmd);
        if(strcmp(cmd,"read")==0){
            scanf("%s",file_name);
            fprintf(stdout,"Reading file.\n");
            hptr = read_input(hptr,file_name);
        }else if(strcmp(cmd,"writeN")==0){
            scanf("%s",file_name);
            fprintf(stdout,"Writing file sorted by name.\n");
            sort_n(hptr);
            write_output(file_name,hptr);
        }else if(strcmp(cmd,"writeM")==0){
            scanf("%s",file_name);
            fprintf(stdout,"Writing file sorted by mark.\n");
            sort_m(hptr);
            write_output(file_name,hptr);
        }else if(strcmp(cmd,"stop")==0){
            fprintf(stdout,"Program terminated.\n");
            stop =1;
        }else{
            fprintf(stdout,"Wrong command.\n");
        }
    }
    free_memory(hptr);
    return 0;
}

node *new_element(void){
    node *ptr;
    ptr = malloc(sizeof(node));
    if (ptr == NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return ptr;
}

node *read_input(node *hptr, char* name){
    char temp_name[MAX_S+1];
    float temp_mark;
    node *tptr;
    FILE *f = fopen(name,"r");
    if(f ==NULL){
        fprintf(stderr,"Error opening file %s.\n",name);
        exit(1);
    }
    hptr = NULL;
    while (fscanf(f,"%s %f",temp_name,&temp_mark)!=EOF){
        tptr = new_element();
        tptr->name = strdup(temp_name);
        tptr->mark = temp_mark;
        tptr->next = hptr;
        hptr = tptr;
    }
    fclose(f);
    return hptr;
}

void sort_m(node *hptr){
    node *endptr,*ptr1,*ptr2,*ptr3;
    char tname[MAX_S+1];
    float tmark;
    if (hptr == NULL || hptr->next ==NULL){
        return;
    }
    endptr = NULL;
    for(ptr1=hptr;ptr1->next!=NULL;ptr1 = ptr1->next){
        for(ptr2=hptr, ptr3 = ptr2->next;ptr3!=endptr;ptr2 = ptr3,ptr3 =ptr3->next){
            if (ptr2->mark > ptr3->mark){
                strcpy(tname,ptr2->name);
                tmark = ptr2->mark;
                strcpy(ptr2->name,ptr3->name);
                ptr2->mark = ptr3->mark;
                strcpy(ptr3->name,tname);
                ptr3->mark = tmark;
            }
        }
        endptr = ptr2;
    }
    return;
}

void sort_n(node *hptr){
    node *endptr,*ptr1,*ptr2,*ptr3;
    char tname[MAX_S+1];
    float tmark;
    if (hptr == NULL || hptr->next ==NULL){
        return;
    }
    endptr = NULL;
    for(ptr1=hptr;ptr1->next!=NULL;ptr1 = ptr1->next){
        for(ptr2=hptr, ptr3 = ptr2->next;ptr3!=endptr;ptr2 = ptr3,ptr3 =ptr3->next){
            if (strcmp(ptr2->name,ptr3->name)>0){
                strcpy(tname,ptr2->name);
                tmark = ptr2->mark;
                strcpy(ptr2->name,ptr3->name);
                ptr2->mark = ptr3->mark;
                strcpy(ptr3->name,tname);
                ptr3->mark = tmark;
            }
        }
        endptr = ptr2;
    }
    return;
}

void write_output(char *name, node *hptr){
    node *tptr;
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file %s.",name);
        exit(1);
    }
    for (tptr = hptr;tptr!=NULL;tptr = tptr ->next){
        fprintf(f,"%s %.2f\n",tptr->name,tptr->mark);
    }
    fclose(f);
    return;
}

void free_memory(node *hptr){
    node *tptr;
    while(hptr!=NULL){
        tptr = hptr;
        hptr = hptr->next;
        free(tptr);
    }
    return;
}
