#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int disconnect_graph_r(graph_t *g, graph_t *removed,int n, int pos);
void print_edges(graph_t *g);
int check_solution(graph_t *g);
edge_t *tail_insert(edge_t *list,edge_t *node);
void dfs_r(graph_t *g,vertex_t *, int *p);
int count_edges(graph_t *g);

/*
    in graph g, white edges can be removed, grey edges can't be removed and black edges are already removed
    in  graph removed, black edges are removed and should be printed

*/

int main()
{
    graph_t *g;
    graph_t *removed;
    int n, found = 0;
    char *file_name = "input.txt";

    g = graph_load(file_name);
    removed = g;

    for (n=1;found==0 && n<=g->ne;n++){
        g = graph_load(file_name);
        if(disconnect_graph_r(g,removed,n,0)){
            print_edges(removed);
            found = 1;
        }
    }

    graph_dispose(g);
    return 0;
}

int disconnect_graph_r(graph_t *g, graph_t *removed,int n, int pos){
    vertex_t *v;
    edge_t *e, *e2, *e3;
    if (pos >=n){
        return check_solution(g);
    }
    for (v = g->g;v!=NULL;v=v->next){
        for (e=v->head;e!=NULL;e=e->next){
            if(e->color==WHITE){

                e->color = BLACK;
                e2 = graph_find_edge(g,e->dst->id,v->id);
                e2->color = BLACK;
                e3 = graph_find_edge(removed,v->id,e->dst->id);
                e3->color = BLACK;

                if(disconnect_graph_r(g,removed,n,pos+1)){
                    return n;
                }

                e->color = GREY;
                e2->color = GREY;
                e3->color = WHITE;
            }
        }
    }
    return 0;
}

void print_edges(graph_t *g){
    vertex_t *v;
    edge_t *e;
    fprintf(stdout,"removed edges:\n");
    for (v= g->g;v!=NULL;v=v->next){
        for (e=v->head;e!=NULL;e=e->next){
            if (e->color==BLACK)
                fprintf(stdout,"%c -> %c\n",(char)('A'+v->id),(char)('A'+e->dst->id));
        }
    }
    return;
}

edge_t *tail_insert(edge_t *list,edge_t *node){
    edge_t *ptr;
    for (ptr = list; ptr->next!=NULL;ptr=ptr->next);
    ptr->next = node;
    return list;
}

//DFS and check if the number of visited nodes is nv
int check_solution(graph_t *g){

    int visited = 1;
    vertex_t *v = graph_find(g,0);
    graph_all_white_vertices(g);
    v->color = GREY;
    dfs_r(g,v,&visited);
    return (visited == g->nv/2 || visited == (g->nv/2)+1);
}

void dfs_r(graph_t *g,vertex_t *v, int *p){
    edge_t *e;
    for (e=v->head;e!=NULL;e=e->next){
        if(e->dst->color==WHITE && e->color != BLACK){
            e->dst->color = GREY;
            (*p)++;
            dfs_r(g,e->dst,p);
        }
    }
    return;
}

int count_edges(graph_t *g){
    vertex_t *v;
    edge_t *e;
    int res = 0;
    for(v=g->g;v!=NULL;v=v->next){
        for (e=v->head;e!=NULL;e=e->next){
            if (e->color!=BLACK)
                res++;
        }
    }
    return res;
}
