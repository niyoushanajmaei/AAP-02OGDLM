#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

 typedef struct vertex_s vertex_t;
 typedef struct graph_s graph_t;
 typedef struct edge_s edge_t;

 struct vertex_s{
    char *id;
    int color;
    edge_t *head;
    vertex_t *next;
 };

 struct graph_s{
    vertex_t *g;
    int nv;
 };

 struct edge_s{
    vertex_t *dst;
    edge_t *next;
};

graph_t *read_graph(char *file_name);
void new_node(graph_t *g,char *id);
void new_edge(graph_t *g, char *srcid, char *dstid);
vertex_t *search_graph(graph_t *g, char *id);
void vertex_coloring(graph_t *g);
void vertex_coloring_r(graph_t *g, vertex_t *v);
void write_colors(graph_t *g);
void dispose_graph(graph_t *g);

int main(int argc, char *argv[])
{
    graph_t *g;
    if (argc!=2){
        fprintf(stderr,"Wrong number of arguments.");
        exit(1);
    }
    g = read_graph(argv[1]);
    vertex_coloring(g);
    write_colors(g);
    dispose_graph(g);
    return 0;
}

graph_t *read_graph(char *file_name){
    FILE *f;
    char srcid[MAX],dstid[MAX];
    graph_t *g = malloc(sizeof(graph_t));
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
    while (fscanf(f,"%s %s",srcid,dstid)!=EOF){
        if (search_graph(g,srcid)==NULL){
            new_node(g,srcid);
        }
        if (search_graph(g,dstid)==NULL){
            new_node(g,dstid);
        }
        new_edge(g,srcid,dstid);
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
    v->color = -1;
    v->head = NULL;
    v->next = g->g;
    g->g = v;

    g->nv++;
    return;
}

void new_edge(graph_t *g, char *srcid, char *dstid){
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
    e1->next = src->head;
    src->head = e1;

    e2->dst = src;
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

void vertex_coloring(graph_t *g){
    g->g->color = 0;
    vertex_coloring_r(g,g->g);
    return;
}

void vertex_coloring_r(graph_t *g, vertex_t *v){

    int found,same,c;
    edge_t *e1,*e2;

    int f = 0;
    for (e1 = v->head;f==0 && e1!=NULL;e1=e1->next){
        if (e1->dst->color == -1){
            f = 1;
        }
    }
    if (f==0){
        return;
    }

    for (e1 = v->head;e1!=NULL;e1=e1->next){
        if (e1->dst->color == -1){
            found = 0;
            for (c=0;found==0;c++){
                same = 0;
                for (e2=e1->dst->head;same == 0 && e2!=NULL;e2=e2->next){
                    if (e2->dst->color == c){
                        same = 1;
                    }
                }
                if (same == 0){
                    found = 1;
                    e1->dst->color = c;
                }
            }
            vertex_coloring_r(g,e1->dst);
        }
    }
    return;
}

void write_colors(graph_t *g){
    vertex_t *v;
    for (v=g->g;v!=NULL;v=v->next){
        fprintf(stdout,"%s color: %d\n",v->id,v->color);
    }
    return;
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
