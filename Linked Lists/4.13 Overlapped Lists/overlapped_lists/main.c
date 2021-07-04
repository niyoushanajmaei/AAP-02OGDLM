#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 20
#define ROW_LENGTH
#define NAME 1
#define MARK 2

typedef struct node_s{
    char *name;
    float mark;
    struct node_s *next_n;
    struct node_s *next_m;
}node;

node *new_element(void);
void read_file(node **hptr_n,node **hptr_m,char *file_name);
node *insert_n(node *hptr,node *tptr);
node *insert_m(node *hptr,node *tptr);
void write_output(char *name, node *hptr, int type);
void free_memory(node *hptr);


int main()
{
    // in place sorting of the list
    node *hptr_n,*hptr_m ;
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
            read_file(&hptr_n,&hptr_m,file_name);
        }else if(strcmp(cmd,"writeN")==0){
            scanf("%s",file_name);
            fprintf(stdout,"Writing file sorted by name.\n");
            write_output(file_name,hptr_n,NAME);
        }else if(strcmp(cmd,"writeM")==0){
            scanf("%s",file_name);
            fprintf(stdout,"Writing file sorted by mark.\n");
            write_output(file_name,hptr_m,MARK);
        }else if(strcmp(cmd,"stop")==0){
            fprintf(stdout,"Program terminated.\n");
            stop =1;
        }else{
            fprintf(stdout,"Wrong command.\n");
        }
    }
    free_memory(hptr_m);
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

void read_file(node **hptr_n,node **hptr_m,char *file_name){
    char temp_name[MAX_S+1];
    float temp_mark;
    node *tptr;
    FILE *f = fopen(file_name,"r");
    if(f ==NULL){
        fprintf(stderr,"Error opening file %s.\n",file_name);
        exit(1);
    }
    *hptr_m = NULL;
    *hptr_n = NULL;
    while (fscanf(f,"%s %f",temp_name,&temp_mark)!=EOF){
        tptr = new_element();
        tptr->name = strdup(temp_name);
        tptr->mark = temp_mark;
        *hptr_n = insert_n(*hptr_n,tptr);
        *hptr_m = insert_m(*hptr_m,tptr);
    }
    fclose(f);
    return;
}

node *insert_n(node *hptr,node *tptr){
    if(hptr==NULL || strcmp(tptr->name,hptr->name)<0){
        tptr->next_n = hptr;
        return tptr;
    }
    node *ptr1=hptr;
    node *ptr2 =hptr->next_n;
    while(ptr2!=NULL && strcmp(ptr2->name,tptr->name)<0){
        ptr1 = ptr2;
        ptr2 = ptr2->next_n;
    }
    tptr->next_n = ptr2;
    ptr1->next_n= tptr;
    return hptr;
}

node *insert_m(node *hptr,node *tptr){
    if(hptr==NULL || tptr->mark<hptr->mark){
        tptr->next_m = hptr;
        return tptr;
    }
    node *ptr1=hptr;
    node *ptr2 =hptr->next_m;

    while(ptr2!=NULL && ptr2->mark < tptr->mark){
        ptr1 = ptr2;
        ptr2 = ptr2->next_m;
    }
    tptr->next_m = ptr2;
    ptr1->next_m = tptr;
    return hptr;
}

void write_output(char *name, node *hptr,int type){
    node *tptr;
    FILE *f = fopen(name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file %s.",name);
        exit(1);
    }
    if (type == NAME){
        for (tptr = hptr;tptr!=NULL;tptr = tptr ->next_n){
            fprintf(f,"%s %.2f\n",tptr->name,tptr->mark);
        }
    }else if (type ==MARK){
        for (tptr = hptr;tptr!=NULL;tptr = tptr ->next_m){
            fprintf(f,"%s %.2f\n",tptr->name,tptr->mark);
        }
    }
    fclose(f);
    return;
}

void free_memory(node *hptr){
    node *tptr;
    while(hptr!=NULL){
        tptr = hptr;
        hptr = hptr->next_m;
        free(tptr);
    }
    return;
}
