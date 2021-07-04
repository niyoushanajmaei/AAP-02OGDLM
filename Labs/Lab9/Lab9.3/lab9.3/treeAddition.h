#ifndef TREEADDITION_H_INCLUDED
#define TREEADDITION_H_INCLUDED

#include "treePublic.h"

void countNode (node_t *root, int *array);
void countLevel (node_t * root, int *array, int l);
void countPath (node_t * root, int *np, int *length);
int visit (node_t *root, int key1, int key2);
int height (node_t *root);

#endif // TREEADDITION_H_INCLUDED
