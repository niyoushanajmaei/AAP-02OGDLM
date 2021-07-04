#include "treeAddition.h"

int find_level(node_t *root, int key);

void countNode (node_t *root, int *array){
    if (root->left == NULL && root->right == NULL){
        array[0]++;
        return;
    }
    if (root->left == NULL){
        array[1]++;
        countNode(root->right,array);
    }
    if (root->right ==NULL){
        array[1]++;
        countNode(root->left,array);
    }
    array[2]++;
    countNode(root->left,array);
    countNode(root->right,array);
    return;
}

void countLevel (node_t * root, int *array, int l){
    if (root==NULL){
        return;
    }
    array[l]++;
    countLevel(root->left,array,l+1);
    countLevel(root->right,array,l+1);
    return;
}

void countPath (node_t * root, int *np, int *length){
    if (root==NULL){
        (*np) ++;
        return;
    }
    if (root->right !=NULL ){
        (*length)+=1;
        countPath(root->right,np,length);
    }
    if (root->left != NULL){
        (*length)+=1;
        countPath(root->left,np,length);
    }
    return;
}

int visit (node_t *root, int key1, int key2){
    int l1=0,l2=0,key;
    if (root->val == key1 || root->val == key2){
        if (root->val == key1){
            key = key2;
        }else{
            key = key1;
        }
        return find_level(root,key);
    }
    if (root->val <key1 &&root->val <key2){
        return visit(root->right,key1,key2);
    }
    if (root->val >key1 &&root->val >key2){
        return visit(root->left,key1,key2);
    }
    l1 = find_level(root,key1);
    l2 = find_level(root,key2);
    return l1+l2;
}

int find_level(node_t *root, int key){
    if (root->val == key){
        return 0;
    }
    if (key >root->val){
        return 1 + find_level(root->r,key);
    }
    return 1+ find_level(root->l,key);
}

int height(node_t root){
    int l,r;
    if (root==NULL){
        return 0;
    }
    r = height(root->right);
    l = height(root->left);
    if (r>l){
        return r;
    }
    return l;
}
