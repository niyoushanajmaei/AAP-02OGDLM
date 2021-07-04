#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 101


 typedef struct vertex_s vertex_t;
 typedef struct graph_s graph_t;
 typedef struct edge_s edge_t;

 struct vertex_s{
    char *id;
    int visited;
    int atm;
    edge_t *head;
    vertex_t *next;
 };

 struct graph_s{
    vertex_t *g;
    int nv;
 };

 struct edge_s{
    vertex_t *dst;
    int weight;
    edge_t *next;
};

graph_t *read_graph(char *file_name);
void new_node(graph_t *g,char *id);
void new_edge(graph_t *g, char *srcid, char *dstid, int weight);
vertex_t *search_graph(graph_t *g, char *id);
void dispose_graph(graph_t *g);

int *place_atm(graph_t *g, int k);
void place_atm_r(graph_t *g,int k, int pos,int level, int *minpath_ptr, int *atm_pos, int *best_atm_pos);
int max_path(graph_t *g,int *atm_pos);
void min_path_r(graph_t *g, vertex_t *v, int *min_ptr, int curr);
void print_solution(graph_t *g, int *atm_pos);

int main(int argc, char *argv[])
{
    graph_t *g;
    int *atm_pos;
    int k;
    if (argc!=3){
        fprintf(stderr,"Wrong number of arguments.");
        exit(1);
    }
    g = read_graph(argv[1]);
    sscanf(argv[2],"%d",&k);
    atm_pos = place_atm(g,k);
    print_solution(g,atm_pos);
    dispose_graph(g);
    return 0;
}

graph_t *read_graph(char *file_name){
    FILE *f;
    char srcid[MAX],dstid[MAX];
    graph_t *g = malloc(sizeof(graph_t));
    int w;
    if(g==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    g->g = NULL;
    g->nv = 0;
    f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    while (fscanf(f,"%s %s %d",srcid,dstid,&w)!=EOF){
        if (search_graph(g,srcid)==NULL){
            new_node(g,srcid);
        }
        if (search_graph(g,dstid)==NULL){
            new_node(g,dstid);
        }
        new_edge(g,srcid,dstid,w);
    }
    fclose(f);
    return g;
}

void new_node(graph_t *g,char *id){
    vertex_t *v = malloc(sizeof(vertex_t));
    if (v==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    v->id = strdup(id);
    v->visited = 0;
    v->atm = 0;
    v->head = NULL;
    v->next = g->g;
    g->g = v;

    g->nv++;
    return;
}

void new_edge(graph_t *g, char *srcid, char *dstid, int weight){
    vertex_t *src,*dst;
    edge_t *e1,*e2;
    e1 = malloc(sizeof(edge_t));
    e2 = malloc(sizeof(edge_t));
    if (e1==NULL || e2 ==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    src = search_graph(g,srcid);
    dst = search_graph(g,dstid);

    e1->dst = dst;
    e1->weight = weight;
    e1->next = src->head;
    src->head = e1;

    e2->dst = src;
    e2->weight = weight;
    e2->next = dst->head;
    dst->head = e2;

    return;
}

vertex_t *search_graph(graph_t *g, char *id){
    vertex_t *v;
    for(v=g->g;v!=NULL;v=v->next){
        if(strcmp(id,v->id)==0){
            return v;
        }
    }
    return NULL;
}

void dispose_graph(graph_t *g){
    vertex_t *v = g->g,*tv;
    edge_t *e,*te;
    while (v!=NULL){
        tv = v;
        v=v->next;
        e= tv->head;
        while(e!=NULL){
            te=e;
            e=e->next;
            free(te);
        }
        free(tv);
    }
    return;
}

int *place_atm(graph_t *g, int k){
    int minpath = INT_MAX;
    int *atm_pos = malloc(g->nv *sizeof(int));
    int *best_atm_pos = malloc(g->nv *sizeof(int));
    if(atm_pos==NULL || best_atm_pos ==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    for(int i=0;i<g->nv;i++){
        atm_pos[i] = 0;
        best_atm_pos[i] = 0;
    }
    place_atm_r(g,k,0,0,&minpath,atm_pos, best_atm_pos);
    return best_atm_pos;
}

// atm position is 1 if there's an atm and 0 if no atm
void place_atm_r(graph_t *g,int k, int pos, int level, int *minpath_ptr, int *atm_pos, int *best_atm_pos){
    int i,max;
    if (level >= k){
        max = max_path(g,atm_pos);
        if (max <= *minpath_ptr){
            *minpath_ptr = max;
            for (i=0;i<g->nv;i++){
                best_atm_pos[i] = atm_pos[i];
            }
        }
        return;
    }
    if (pos < g->nv){
        atm_pos[pos] = 1;
        place_atm_r(g,k,pos+1,level+1,minpath_ptr,atm_pos,best_atm_pos);
        atm_pos[pos] = 0;
        place_atm_r(g,k,pos+1,level,minpath_ptr,atm_pos,best_atm_pos);
    }
    return;
}

int max_path(graph_t *g,int *atm_pos){
    int i = 0, min = INT_MAX,max= 0;
    vertex_t *v,*v2;
    for (v=g->g;v!=NULL;v=v->next){
        if (atm_pos[i++]==1){
            v->atm = 1;
        }
    }

    for (v=g->g;v!=NULL;v=v->next){
        min = INT_MAX;
        for (v2=g->g;v2!=NULL;v2=v2->next){
            v2->visited = 0;
        }
        v->visited =1;
        min_path_r(g,v,&min,0);
        if (min > max){
            max = min;
        }
    }

    i = 0;
    for (v=g->g;v!=NULL;v=v->next){
        if (atm_pos[i++]==1){
            v->atm = 0;
        }
    }

    return max;
}

void min_path_r(graph_t *g, vertex_t *v, int *min_ptr, int curr){
    edge_t *e;
    if (v->atm == 1){
        if (curr<*min_ptr){
            *min_ptr = curr;
        }
        return;
    }
    for (e=v->head;e!=NULL;e=e->next){
        if (e->dst->visited == 0){
            e->dst->visited = 1;
            min_path_r(g,e->dst,min_ptr,curr+e->weight);
            e->dst->visited = 0;
        }
    }
    return;
}

void print_solution(graph_t *g, int *atm_pos){
    vertex_t *v;
    int i=0;

    for (v=g->g;v!=NULL;v=v->next){
        if (atm_pos[i++]==1){
            fprintf(stdout,"ATM at %s\n",v->id);
        }
    }
    return;
}
