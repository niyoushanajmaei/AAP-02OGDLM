#ifndef BSTPRIVATE_H_INCLUDED
#define BSTPRIVATE_H_INCLUDED

#include "bstPublic.h"

typedef struct login_s login;

struct bst_s{
    char *ip;
    char *name;
    login *login;
    bst *left_ip;
    bst *right_ip;
    bst *left_name;
    bst *right_name;
};

struct login_s{
    char *time;
    char *resource;
    int type;
    int res;
    login *next;
};

#endif // BSTPRIVATE_H_INCLUDED
