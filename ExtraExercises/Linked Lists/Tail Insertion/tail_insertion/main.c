#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s{
    char *id;
    struct node_s *next;
}node;

void add_node_tail (node **head, node **tail, char *text);
void display (node *head);
node *new_node(void);

int main()
{
    node *head = NULL;
    node *tail = NULL;
    char strings[3][20] = {"first","second","third"};
    for (int i=0;i<3;i++){
        add_node_tail(&head,&tail,strings[i]);
    }
    display(head);

    while (head !=NULL){
        node *tmp  = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}

/* adding to tail so the order will be the same*/
void add_node_tail (node **head, node **tail, char *text){
    node *tmp = new_node();
    tmp->id = strdup(text);
    tmp->next = NULL;
    if (*head == NULL){
        *head = tmp;
        *tail = *head;
    }else{
        (*tail)->next = tmp;
        *tail = tmp;
    }
    return;
}

void display (node *head){
    node *tmp;
    for (tmp = head;tmp!=NULL;tmp = tmp->next){
        fprintf(stdout,"%s\n",tmp->id);
    }
    return;
}

node *new_node(void){
    node *tmp = malloc(sizeof(node));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return tmp;
}
