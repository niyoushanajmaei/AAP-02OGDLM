#ifndef BSTPUBLIC_H_INCLUDED
#define BSTPUBLIC_H_INCLUDED

#include <string.h>

#define M 100

//ACCEPT for 200 and REJECT for 401
enum {GET,POST,ACCEPT,REJECT};

typedef struct bst_s bst;

void read(char *file_name, bst **rp_ip_ptr, bst **rp_name_ptr);
bst *insert_r_ip(bst *rp, bst *tmp);
bst *insert_r_name (bst *rp, bst *tmp);
void bst_dispose(bst *rp);
bst *search_ip_r(bst *rp,char *ip);
void insert_login (bst *node, bst *tmp);
void write(bst *rp_ip,bst *rp_name);
void bst_print_ip_r(bst* rp);
void bst_print_name_r (bst *rp);

#endif // BSTPUBLIC_H_INCLUDED
