#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 101

/*
    visit all edges and count at least one of the vertices as included.
    increase incl of the graph until is nv
    store the added vertices in a best from curr if the number of chosen vertices is less than min
*/

typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;

struct graph_s{
    vertex_t *g;
    int nv;
    int incl;
};

struct vertex_s{
    char *id;
    int f;
    edge_t *head;
    vertex_t *next;
};

struct edge_s{
    vertex_t *dst;
    int visited;
    edge_t *next;
};

graph_t *read_file(char *file_name);
void new_node(graph_t *g, char *id);
void new_edge(graph_t *g, char *srcid, char *dstid);
vertex_t *find(graph_t *g, char *id);
void dispose(graph_t *g);
vertex_t *vertex_cover(graph_t *g, int *sol_size_ptr);
void vertex_cover_r(graph_t *g, vertex_t *curr, vertex_t *best, int *sol_size_ptr, int pos);
void write_sol ( vertex_t *sol, int sol_size);
edge_t *find_edge(graph_t *g, char *srcid, char* dstid);

int main(int argc, char *argv[])
{
    graph_t *g;
    vertex_t *sol;
    int sol_size = INT_MAX;
    if (argc!=2){
        fprintf(stderr,"Wrong number of arguments.\n");
        exit(1);
    }
    g = read_file(argv[1]);
    sol = vertex_cover(g,&sol_size);
    write_sol(sol,sol_size);
    dispose(g);
    return 0;
}

graph_t *read_file(char *file_name){
    FILE *f;
    char src[MAX],dst[MAX];
    graph_t *g = malloc(sizeof(graph_t));
    if (g==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    g->g = NULL;
    g->nv = 0;
    g->incl = 0;
    f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    while (fscanf(f,"%s %s",src,dst)==2){
        if (find(g,src)==NULL){
            new_node(g,src);
        }
        if (find(g,dst)==NULL){
            new_node(g,dst);
        }
        new_edge(g,src,dst);
    }
    fclose(f);
    return g;
}

void new_node(graph_t *g, char *id){
    vertex_t *v = malloc(sizeof(vertex_t));
    if (v==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    v->id = strdup(id);
    v->f = 0;
    v->head = NULL;
    v->next = g->g;
    g->g = v;
    g->nv++;

    return;
}

void new_edge(graph_t *g, char *srcid, char *dstid){
    vertex_t *src, *dst;
    edge_t *e1 = malloc(sizeof(edge_t));
    edge_t *e2 = malloc(sizeof(edge_t));
    if(e1==NULL||e2==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    src = find(g,srcid);
    dst = find(g,dstid);

    e1->dst = dst;
    e1->visited = 0;
    e1->next = src->head;
    src->head = e1;

    e2->dst = src;
    e2->visited = 0;
    e2->next = dst->head;
    dst->head = e2;

    return;
}

vertex_t *find(graph_t *g, char *id){
    vertex_t *v;
    for (v=g->g;v!=NULL;v=v->next){
        if (strcmp(id,v->id)==0){
            return v;
        }
    }
    return NULL;
}

void dispose(graph_t *g){
    vertex_t *tv;
    edge_t *te;
    while(g->g!=NULL){
        tv = g->g;
        g->g = g->g->next;
        while (tv->head !=NULL){
            te=  tv->head;
            tv->head = tv->head->next;
            free(te);
        }
        free(tv);
    }
    free(g);
    return;
}

vertex_t *vertex_cover(graph_t *g, int *sol_size_ptr){
    vertex_t *best, *curr;
    best = malloc(g->nv * sizeof(vertex_t));
    curr = malloc(g->nv * sizeof(vertex_t));

    if(best==NULL || curr==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    vertex_cover_r(g,curr,best,sol_size_ptr,0);
    return best;
}

void vertex_cover_r(graph_t *g, vertex_t *curr, vertex_t *best, int *sol_size_ptr, int curr_size){
    int i;
    vertex_t *v;
    edge_t *e, *e2;
    if (g->incl == g->nv){
        if (curr_size < *sol_size_ptr){
            fprintf(stdout,"changing %d to %d\n", *sol_size_ptr,curr_size);
            for (i=0;i<curr_size;i++){
                best[i].id = strdup(curr[i].id);
            }
            *sol_size_ptr = curr_size;
        }
        return;
    }
    for (v=g->g;v!=NULL;v=v->next){
        for (e=v->head;e!=NULL;e=e->next){
            if (e->visited == 0){
                e->visited = 1;
                e2 = find_edge(g,e->dst->id,v->id);
                e2->visited = 1;
                if (v->f==0 && e->dst->f==0){
                    g->incl += 2;
                    v->f = 1;
                    e->dst->f = 1;
                    fprintf(stdout,"added : %s %s\n",v->id,e->dst->id);
                    curr[curr_size].id = strdup(v->id);
                    vertex_cover_r(g,curr,best,sol_size_ptr,curr_size+1);
                    fprintf(stdout,"removed : %s %s\n",v->id,e->dst->id);
                    fprintf(stdout,"added : %s %s\n",e->dst->id,v->id);
                    curr[curr_size].id = strdup(e->dst->id);
                    vertex_cover_r(g,curr,best,sol_size_ptr,curr_size+1);
                    fprintf(stdout,"removed: %s %s\n",e->dst->id,v->id);
                    /*
                    g->incl -= 2;
                    v->f = 0;
                    e->dst->f = 0;
                    */
                }else if(v->f==0 && e->dst->f == 1){
                    v->f = 1;
                    g->incl++;
                }else if(e->dst->f==0 && v->f == 1){
                    e->dst->f = 1;
                    g->incl++;
                }
            }
        }
    }
    return;
}

void write_sol (vertex_t *sol, int sol_size){
    int i;
    fprintf(stdout,"{");
    for(i=0;i<sol_size;i++){
        fprintf(stdout,"%s ",sol[i].id);
    }
    fprintf(stdout,"}\n");
    return;
}

edge_t *find_edge(graph_t *g, char *srcid, char* dstid){
    for (vertex_t *v=g->g;v!=NULL;v=v->next){
        for (edge_t *e=v->head;e!=NULL;e=e->next){
            if(strcmp(e->dst->id,dstid)==0 && strcmp(v->id,srcid)==0){
                return e;
            }
        }
    }
    return NULL;
}
