#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int hamilton_cycle_r(graph_t *g, vertex_t *n,graph_t *path, int starting_id);
vertex_t *tail_insert(vertex_t *list,vertex_t *node);
vertex_t *tail_remove(vertex_t *list);

int main()
{
    graph_t *g , *path;
    vertex_t *n,*ptr;
    int starting_id;
    char *file_name = "input.txt";

    fprintf(stdout,"Enter the id of the starting vertex:\n");
    scanf("%d",&starting_id);

    g = graph_load(file_name);
    path = new_graph(starting_id);
    n = graph_find(g,starting_id);

    if (hamilton_cycle_r(g,n,path,starting_id)){
        for (ptr = path->g;ptr!=NULL;ptr=ptr->next){
            fprintf(stdout,"%c ",(char)('A' + ptr->id));
        }
    }else{
        fprintf(stdout,"No hamilton cycle found\n");
    }

    return 0;
}


int hamilton_cycle_r(graph_t *g, vertex_t *n,graph_t *path, int starting_id){
    edge_t *e;

    // check if we have the cycle if we have reached the starting point
    if (n->id == starting_id ){
        if (path->nv==g->nv){
            return 1;
        }
    }

    //select the next edge and check till possibly reach the starting node
    //selected edges color: gray
    for (e=n->head;e!=NULL;e = e->next){
        if (e->dst->color ==WHITE){
            /*
            fprintf(stdout,"checking %c -> %c\n path is:\n", (char)('A'+n->id),(char)('A'+e->dst->id));
            */
           //tail insert the next node in path if white and back track
            path->g = tail_insert(path->g,new_node(NULL,e->dst->id));
            path->nv ++;
            e->dst->color = GREY;
            if(hamilton_cycle_r(g,e->dst,path,starting_id)){
                return 1;
            }
            path->g = tail_remove(path->g);
            path->nv --;
            e->dst->color = WHITE;
        }
    }

    return 0;
}

vertex_t *tail_insert(vertex_t *list,vertex_t *node){
    vertex_t *ptr;
    for (ptr = list; ptr->next!=NULL;ptr=ptr->next);
    ptr->next = node;
    return list;
}

vertex_t *tail_remove(vertex_t *list){
    vertex_t *ptr;
    for (ptr = list; ptr->next!=NULL;ptr=ptr->next);
    ptr = NULL;
    return list;
}
