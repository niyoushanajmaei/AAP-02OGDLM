#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

/*
    WHITE: vertex can be chosen
    GRAY: vertex can not be chosen
    BLACK: vertex in path
*/

enum {WHITE,GRAY,BLACK};

typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;
typedef struct sol_s sol_t;

struct edge_s{
    int weight;
    vertex_t *dst;
    struct edge_s *next;
};

struct graph_s{
    vertex_t *g;
    int n;
};

struct vertex_s{
    char *id;
    int ein;
    int eout;
    int color;
    edge_t *head;
    vertex_t *next;
};

struct sol_s{
    vertex_t *path;
    int length;
};

graph_t *graph_load(char *file_name);
vertex_t *graph_find(graph_t *g,char *id);
void new_node(graph_t *g, char *id);
void new_edge(graph_t *g,char *src, int weight, char *dst);
int graph_check_regularity(graph_t *g);
void graph_dispose(graph_t *g);
void write_sol(sol_t *solution);
void find_path(graph_t *g, vertex_t *v, sol_t *best);
void find_path_r(graph_t *g, vertex_t *v, sol_t *curr, sol_t *best);
void free_sol(sol_t *s);

int main(int argc, char *argv[])
{
    graph_t *g;
    vertex_t *v;
    sol_t *best;
    char id[MAX];

    if (argc!=2){
        fprintf(stderr,"wrong number of arguments.\n");
        exit(1);
    }

    g = graph_load(argv[1]);
    /*
    fprintf(stdout,"graph is of size: %d\nvertices are:\n",g->n);
    for(v=g->g;v!=NULL;v=v->next){
        fprintf(stdout,"%s\n",v->id);
    }
    */
    if (graph_check_regularity(g)){
        fprintf(stdout,"The graph is regular.\n");
    }else{
        fprintf(stdout,"The graph is not regular\n");
    }

    best = malloc(sizeof(sol_t));
    if (best==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    fprintf(stdout,"Enter the starting vertex id, end to terminate \n");
    scanf("%s",id);
    while (strcmp(id,"end")){
        v = graph_find(g,id);
        if (v==NULL){
            fprintf(stdout,"vertex not found.\n");
        }else{
            find_path(g,v,best);
            if (best->length!=-1){
                write_sol(best);
            }else{
                fprintf(stdout,"no path found\n");
            }
        }
        fprintf(stdout,"Enter the starting vertex id, end to terminate \n");
        scanf("%s",id);
    }

    graph_dispose(g);
    free_sol(best);
    return 0;
}

graph_t *graph_load(char *file_name){
    graph_t *g;
    FILE *f;
    char src[MAX],dst[MAX], tmp[2*MAX+5];
    int weight;

    g = malloc(sizeof(graph_t));
    if (g==NULL){
        fprintf(stderr,"Error allocating memory\n");
        exit(1);
    }
    g->g = NULL;
    g->n = 0;

    f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }

    while (fgets(tmp,2*MAX+5,f)!=NULL){

        sscanf(tmp,"%s %d %s",src,&weight,dst);
        new_node(g,src);
        new_node(g,dst);
        new_edge(g,src,weight,dst);
    }
    fclose(f);
    return g;
}

vertex_t *graph_find(graph_t *g,char *id){
    vertex_t *v;
    for(v=g->g;v!=NULL;v=v->next){
        if(strcmp(v->id,id)==0){
            return v;
        }
    }
    return NULL;
}

void new_node(graph_t *g, char *id){
    vertex_t *v = malloc(sizeof(vertex_t));
    if (v==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    if(graph_find(g,id)==NULL){
        v->color = WHITE;
        v->ein = 0;
        v->eout = 0;
        v->head = NULL;
        v->id = strdup(id);
        v->next = g->g;
        g->g = v;
        g->n++;
    }
    return;
}

void new_edge(graph_t *g,char *srcid, int weight, char *dstid){
    vertex_t *src, *dst;
    edge_t *e = malloc(sizeof(edge_t));
    if (e==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    src = graph_find(g,srcid);
    dst = graph_find(g,dstid);

    e->dst = dst;
    e->weight = weight;
    e->next = src->head;
    src->head = e;
    src->eout ++;
    dst->ein ++;

    return;
}

int graph_check_regularity(graph_t *g){
    vertex_t *v, *ref = g->g;
    if (ref->ein!=ref->eout){
        return 0;
    }
    for (v=g->g;v!=NULL;v=v->next){
        if (v->ein != ref->ein || v->eout != ref->eout){
            return 0;
        }
    }
    return 1;
}

void graph_dispose(graph_t *g){
    vertex_t *v = g->g, *tv;
    edge_t *e, *te;
    while(v!=NULL){
        tv = v;
        v=v->next;
        e = tv->head;
        while (e!=NULL){
            te = e;
            e=e->next;
            free(te);
        }
        free(tv);
    }
    free(g);
    return;
}

void write_sol(sol_t *solution){
    vertex_t *v;
    fprintf(stdout,"solution length: %d\n",solution->length);
    for (v=solution->path;v!=NULL;v=v->next){
        fprintf(stdout,"%s -> %s , weight: %d\n",v->id,v->head->dst->id,v->head->weight);
    }
    return;
}

void find_path(graph_t *g, vertex_t *v, sol_t *best){
    vertex_t *tmp;
    sol_t *curr  = malloc(sizeof(sol_t));
    if (curr==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }

    for (tmp=g->g;tmp!=NULL;tmp=tmp->next){
        tmp->color = WHITE;
    }
    best->length = -1;
    best->path = NULL;
    curr->path = NULL;
    curr->length = 0;

    find_path_r(g,v,curr,best);

    free_sol(curr);
    return;
}

void find_path_r(graph_t *g, vertex_t *v, sol_t *curr, sol_t *best){
    edge_t *e;
    vertex_t *tmp;

    //complete path, check if best
    if (curr->length > best->length){
        best ->length = curr->length;
        best->path = curr->path;
    }

    for (e=v->head;e!=NULL;e=e->next){
        if (e->dst->color == WHITE){
            tmp = malloc(sizeof(vertex_t));
            if (tmp==NULL){
                fprintf(stderr,"Error allocating memory\n");
                exit(1);
            }
            e->dst->color = BLACK;
            curr->length+=e->weight;
            tmp->head = e;
            tmp->id = v->id;
            tmp->next = curr->path;
            curr->path = tmp;

            find_path_r(g,e->dst,curr,best);

            e->dst->color = WHITE;
            curr->length-=e->weight;
            curr->path = curr->path->next;
        }
    }

    return;
}

void free_sol(sol_t *s){
    vertex_t *v;
    while (s->path!=NULL){
        v = s->path;
        s->path = s->path->next;
        free(v->head);
        free(v);
    }
    free(s);
    return;
}
