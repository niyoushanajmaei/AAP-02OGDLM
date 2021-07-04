#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_s{
    char *name;
    char *surname;
    struct list_s *next;
}list_t;

int list_insert_in_order(list_t **headP ,char *surname, char *name);
void print_list(list_t *headP);
int find (list_t *hptr, char *surname, char *name);

int main()
{
    list_t *list = NULL;
    int flag = 1;
    char name [21];
    char surname [21];
    while (flag){
        printf("Enter 1 to insert data and 0 to end\n");
        scanf("%d",&flag);
        if (flag){
            printf("Enter name:\n");
            scanf("%s",name);
            printf("Enter surname:\n");
            scanf("%s",surname);
            list_insert_in_order(&list,surname,name);
        }
        print_list(list);
    }
    return 0;
}

int list_insert_in_order(list_t **headP, char *surname, char *name){
    list_t *hptr = *headP;
    list_t *tmp,*ptr;
    if (find(hptr,surname,name)){
        return 0;
    }
    tmp = malloc(sizeof(list_t));
    if(tmp==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    for (ptr = hptr;ptr!=NULL;ptr=ptr->next){
        if (ptr->)
    }
    tmp->name = name;
    tmp->surname = surname;
    tmp->next = hptr;
    hptr = tmp;

    *headP = hptr;
    return 1;
}

void print_list(list_t *headP){
    list_t *ptr;
    for (ptr = headP;ptr !=NULL;ptr = ptr->next){
        printf("%s %s\n",ptr->name,ptr->surname);
    }
    return;
}

int find (list_t *hptr, char *surname, char *name){
    list_t *ptr;
    for (ptr = hptr; ptr!=NULL; ptr = ptr->next){
        if (strcmp(name,ptr->name)== 0 && strcmp(surname,ptr->surname)==0){
            return 1;
        }
    }
    return 0;
}
