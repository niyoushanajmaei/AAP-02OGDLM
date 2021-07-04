#include <stdio.h>
#include "queuePublic.h"
#include "graph.h"

/* function prototypes */
int graph_bfs_count (graph_t *, vertex_t *);
int graph_bfs_distance (graph_t *, vertex_t *);
void graph_dfs_type(graph_t *, vertex_t *, int arr[4]);
int graph_dfs_depth(graph_t *,vertex_t *);
int graph_dfs_r (graph_t *, vertex_t *, int,int arr[4]);
int graph_dfs_r_depth(graph_t *g, vertex_t *n, int currTime, int *ptr);
int graph_dfs_r_max_path (graph_t *, vertex_t *, int, int *,int *);

/*
 *  main program
 */
int main (int argc, char *argv[]) {
  graph_t *g;
  vertex_t *src, *n;
  int i, bfs,distance,arr[4];

  for (int i = 0; i<4;i++){
    arr[i] = 0;
  }

  util_check_m(argc>=2, "missing parameter.");
  g = graph_load (argv[1]);

  printf("Initial vertex? ");
  scanf("%d", &i);

  printf ("Incoming/Outgoing Edges\n");
  src = graph_find (g, i);

  /* DFS */
  printf ("DFS\n");
  // Redundant after load
  graph_attribute_init (g);
  graph_dfs_type(g,src,arr);

  /* BFS */
  printf ("BFS\n");
  graph_attribute_init (g);
  bfs = graph_bfs_count (g, src);
  distance = graph_bfs_distance(g,src);
    fprintf(stdout,"the number of visited nodes:%d and the farthest distance is %d\n",bfs,distance);
  /* print reachable nodes with info */
  n = g->g;
  printf("List of vertices:\n");
  while (n != NULL) {
    if (n->color != WHITE) {
      printf("%2d: [%d] (%d)\n", n->id, n->dist, n->pred ? n->pred->id : -1);
    }
    n = n->next;
  }

  graph_dispose (g);

  return EXIT_SUCCESS;
}

/*
 *  perform BFS from vertex n
 */
int graph_bfs_count (graph_t *g, vertex_t *n) {
  queue_t *qp;
  vertex_t *d;
  edge_t *e;
  static int res = 1;

  qp = queue_init (g->nv);
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);
    e = n->head;
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
	d->color = GREY;
	d->dist = n->dist + 1;
	d->pred = n;
	queue_put (qp, (void *)d);
	res++;
      }
      e = e->next;
    }
    n->color = BLACK;
  }
  queue_dispose (qp, NULL);

  return res;
}


int graph_bfs_distance (graph_t *g, vertex_t *n) {
  queue_t *qp;
  vertex_t *d;
  edge_t *e;
  static int res = 1;

  qp = queue_init (g->nv);
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  while (!queue_empty_m (qp)) {
    int max = 1;
    queue_get (qp, (void **)&n);
    e = n->head;
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
	d->color = GREY;
	d->dist = n->dist + 1;
	d->pred = n;
	queue_put (qp, (void *)d);
	res++;
      }
      e = e->next;
    }
    n->color = BLACK;
  if (max>res){
    res = max;
  }
  }
  queue_dispose (qp, NULL);

  return res;
}

/*
 *  perform recursive DFS from vertex i:
 *  labels nodes with td/tq, edges as T/F/B/C
 */
int graph_dfs_r(graph_t *g, vertex_t *n, int currTime, int arr[4]) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: printf("%d -> %d : T\n", n->id, tmp->id); arr[0]++; break;
      case GREY : printf("%d -> %d : B\n", n->id, tmp->id); arr[2]++; break;
      case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                    arr[1]++;
                  } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                    arr[3]++;
                  }
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_r (g, tmp, currTime,arr);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;

  return currTime;
}

void graph_dfs_type(graph_t *g, vertex_t *n, int arr[4]){
      int currTime=0;
  vertex_t *tmp, *tmp2;

  printf("List of edges:\n");
  currTime = graph_dfs_r (g, n, currTime,arr);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    if (tmp->color == WHITE) {
      currTime = graph_dfs_r (g, tmp, currTime,arr);
    }
  }

  printf("List of vertices:\n");
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    tmp2 = tmp->pred;
    printf("%2d: %2d/%2d (%d)\n",
      tmp->id, tmp->disc_time, tmp->endp_time,
      (tmp2!=NULL) ? tmp->pred->id : -1);
  }

  fprintf(stdout,"Tree edges: %d\nForward edges: %d\n Backward edges: %d\n Cross edges: %d\n",arr[0],arr[1],arr[2],arr[3]);
  return;
}

int graph_dfs_depth (graph_t *g, vertex_t *n){
      int currTime=0;
  vertex_t *tmp, *tmp2;
    int res = 0;
  printf("List of edges:\n");
  currTime = graph_dfs_r_depth (g, n, currTime,&res);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    if (tmp->color == WHITE) {
      currTime = graph_dfs_r_depth (g, tmp, currTime,&res);
    }
  }

  printf("List of vertices:\n");
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    tmp2 = tmp->pred;
    printf("%2d: %2d/%2d (%d)\n",
      tmp->id, tmp->disc_time, tmp->endp_time,
      (tmp2!=NULL) ? tmp->pred->id : -1);
  }


  return res;
}

int graph_dfs_r_depth(graph_t *g, vertex_t *n, int currTime, int *ptr) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: printf("%d -> %d : T\n", n->id, tmp->id);  break;
      case GREY : printf("%d -> %d : B\n", n->id, tmp->id); break;
      case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                  } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                  }
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_r_depth (g, tmp, currTime,ptr);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;
  if (currTime > *ptr){
    *ptr = currTime;
  }

  return currTime;
}

int graph_dfs_r_max_path(graph_t *g, vertex_t *n, int currTime, int *max_path_ptr,int *curr_path_ptr) {
  edge_t *e;
  vertex_t *tmp;
  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: printf("%d -> %d : T\n", n->id, tmp->id); break;
      case GREY : printf("%d -> %d : B\n", n->id, tmp->id);  break;
      case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                  } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                  }
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      (*curr_path_ptr) += e->weight;
      currTime = graph_dfs_r_max_path (g, tmp, currTime,max_path_ptr,curr_path_ptr);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;
  *curr_path_ptr = 0;
  if (*curr_path_ptr >*max_path_ptr){
    *max_path_ptr = *curr_path_ptr;
  }

  return currTime;
}

