#include <stdio.h>
#include <stdlib.h>

/*
    gray edges are removed
    gray vertices are visited
*/

enum {WHITE,GRAY,BLACK};

typedef struct graph_s graph_t;
typedef struct edge_s edge_t;
typedef struct vertex_s vertex_t;

struct graph_s{
    vertex_t *g;
    int nv;
    int ne;
};

struct vertex_s{
    int id;
    int color;
    edge_t *head;
    vertex_t *next;
};

struct edge_s{
    int color;
    vertex_t *dst;
    edge_t *next;
};

graph_t *graph_load(char *file_name);
graph_t *graph_init( int n);
vertex_t *graph_find(graph_t *g, int id);
void new_node(graph_t *g, int id);
void new_edge(graph_t *g,int src,int dst);
int disconnect_r(graph_t *g,int n,int pos);
int is_disconnected(graph_t *g);
void dfs_r(graph_t *g,vertex_t *v,int *p);

int main()
{
    char *file_name = "input.txt";
    graph_t *g;
    int res,done = 0;

    g = graph_load(file_name);

    for (res = 1;done == 0 && res<=g->ne;res++){
        if(disconnect_r(g,res,0)){
            fprintf(stdout,"minimum number of edges to be removed: %d\n",res);
            done = 1;
        }
    }

    return 0;
}

graph_t *graph_load(char *file_name){
    graph_t *g;
    int n,r,c,t;
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }

    fscanf(f,"%d",&n);
    g = graph_init(n);

    for(r=0;r<n;r++){
        for(c=0;c<n;c++){
            fscanf(f,"%d",&t);
            if (t){
                new_edge(g,r,c);
                g->ne ++;
            }
        }
    }

    fclose(f);
    return g;
}

graph_t *graph_init(int n){
    graph_t *g = malloc(n*sizeof(graph_t));
    if(g==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    g->nv = n;
    g->ne = 0;
    g->g = NULL;
    for (int i =n-1;i>=0;i--){
        new_node(g,i);
    }

    return g;
}

void new_node(graph_t *g, int id){
    vertex_t *v = malloc(sizeof(vertex_t));
    if (v==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    v->id = id;
    v->color = WHITE;
    v->head = NULL;
    v->next = g->g;
    g->g = v;

    return;
}

void new_edge(graph_t *g,int src,int dst){
    vertex_t *v1,*v2;
    edge_t *e;
    v1 = graph_find(g,src);
    v2 = graph_find(g,dst);

    e = malloc(sizeof(edge_t));
    if(e==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    e->color = WHITE;
    e->dst = v2;
    e->next = v1->head;
    v1->head = e;

    return;
}

vertex_t *graph_find(graph_t *g, int id){
    vertex_t *v;

    for(v=g->g;v!=NULL;v=v->next){
        if (id == v->id){
            return v;
        }
    }

    return NULL;
}

int disconnect_r(graph_t *g,int n,int pos){
    vertex_t *v;
    edge_t *e;
    if (pos>=n){
        return is_disconnected(g);
    }
    for(v=g->g;v!=NULL;v=v->next){
        for (e=v->head;e!=NULL;e=e->next){
           // fprintf(stdout,"removing: %c->%c\n",'A' + v->id,'A' + e->dst->id);
            e->color = GRAY;
            if (disconnect_r(g,n,pos+1)){
                return 1;
            }
            e->color = WHITE;
        }
    }
    return 0;
}

int is_disconnected(graph_t *g){
    int n = 1;
    vertex_t *v;
    for (v=g->g;v!=NULL;v=v->next){
        v->color = WHITE;
    }
    g->g->color = GRAY;
    dfs_r(g,g->g,&n);
    return (n != g->nv);
}

void dfs_r(graph_t *g,vertex_t *v, int *p){
    edge_t *e;

    for(e=v->head;e!=NULL;e=e->next){
        if(e->dst->color == WHITE && e->color == WHITE){
            //fprintf(stdout,"dfs: %c->%c\n",'A' + v->id,'A' + e->dst->id);
            e->dst->color = GRAY;
            (*p)++;
            dfs_r(g,e->dst,p);
            e->dst->color = BLACK;
        }
    }
    return;
}
