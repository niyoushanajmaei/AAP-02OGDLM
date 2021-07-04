#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef struct product_s{
    char *name;
    int price;
    char *id;
    struct product_s *next;
}product;

typedef struct producer_s{
    char *name;
    char *id;
    struct product_s *products;
    struct producer_s *next;
}producer;

producer *read_producers(char *file_name);
void read_products(char *file_name, producer **list_ptr);
void search(producer **list_ptr,product *item);
void display(producer *list);
producer *new_producer(void);
product *new_product(void);
void free_memory(producer *list);


int main(int argc, char *argv[])
{
    producer *list;
    if (argc!=3){
        fprintf(stderr,"wrong number of arguments.");
        exit(1);
    }
    list = read_producers(argv[1]);
    read_products(argv[2],&list);
    display(list);
    free_memory(list);
    return 0;
}

producer *read_producers(char *file_name){
    producer *hptr = NULL, *tmp;
    char line[100],t_name[MAX],t_id[MAX];
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    while (fgets(line,100,f)!=NULL){
        tmp = new_producer();
        sscanf(line,"%s %s",t_name,t_id);
        tmp->name = strdup(t_name);
        tmp->id = strdup(t_id);
        tmp->products = NULL;
        tmp->next = hptr;
        hptr = tmp;
    }
    fclose(f);
    return hptr;
}

void read_products(char *file_name, producer **list_ptr){
    product *hptr , *tmp;
    char line[100],t_name[MAX],t_id[MAX];
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    while (fgets(line,100,f)!=NULL){
        tmp = new_product();
        sscanf(line,"%s %s %d",t_id,t_name,&tmp->price);
        tmp->name = strdup(t_name);
        tmp->id = strdup(t_id);
        search(list_ptr,tmp);
    }
    fclose(f);
    return;
}

/* finds the item in the list and adds it to the products list
    of the corresponding producer and returns the modified list*/
void search(producer **list_ptr,product *item){
    producer *hptr = *list_ptr, *ptr;
    product *product_hptr;
    for (ptr = hptr;ptr !=NULL;ptr = ptr->next){
        // printf("comparing item %s with producer %s\n",item->id,ptr->id);
        if (strcmp(item->id,ptr->id)==0){
            item->next = ptr->products;
            ptr->products = item;
            *list_ptr = hptr;
            return;
        }
    }
    fprintf(stderr,"Producer not found in the list.");
    exit(1);
    return;
}

void display(producer *list){
    producer *ptr;
    product *product_ptr;
    for (ptr = list;ptr!=NULL;ptr = ptr->next){
        fprintf(stdout,"%s %s: \n",ptr->name,ptr->id);
        for (product_ptr=ptr->products;product_ptr!=NULL;product_ptr = product_ptr->next){
            fprintf(stdout,"    %s %d\n",product_ptr->name,product_ptr->price);
        }
        fprintf(stdout,"\n");
    }
    return;
}

producer *new_producer(void){
    producer *tmp  = malloc(sizeof(producer));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return tmp;
}

product *new_product(void){
    product *tmp = malloc(sizeof(product));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return tmp;
}

void free_memory(producer *list){
    producer *tmp;
    product *tmp2;
    while (list!=NULL){
        tmp = list;
        list = list->next;
        free(tmp->name);
        free(tmp->id);
        while (tmp->products!=NULL){
            tmp2 = tmp->products;
            tmp->products = tmp->products->next;
            free(tmp2->name);
            free(tmp2->id);
            free(tmp2);
        }
        free(tmp);
    }
    return;
}
