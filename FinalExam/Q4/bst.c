#include <stdio.h>
#include <stdlib.h>
#include "bstPrivate.h"

void read(char *file_name, bst **rp_ip_ptr, bst **rp_name_ptr){
    FILE *f;
    char tip[M],ttime[M], tname[M], tsource[M], ttype[M];
    int tres;
    bst *tmp, *rp_ip = NULL , *rp_name = NULL, *tmp2;
    login *tlog;
    f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }

    while (fscanf(f,"%s %s %s %s %s %d",tip,tname,ttime,ttype,tsource,&tres)!= EOF ){
        tmp = malloc(sizeof(bst));
        tlog = malloc(sizeof(login));
        if (tmp==NULL ||tlog == NULL){
            fprintf(stderr,"Error allocating memory.");
            exit(1);
        }
        tmp->login = tlog;
        tmp->ip = strdup(tip);
        tmp->name = strdup(tname);
        tmp->login->time = strdup(ttime);
        tmp->login->resource = strdup(tsource);
        if (strcmp(ttype,"GET")==0){
            tmp->login->type = GET;
        }else{
            tmp->login->type = POST;
        }
        if(tres==200){
            tmp->login->res = ACCEPT;
        }else{
            tmp->login->res = REJECT;
        }
            tmp->login->next = NULL;
            tmp->left_ip = NULL;
            tmp->right_ip = NULL;
            tmp->left_name = NULL;
            tmp->right_name = NULL;
        if(search_ip_r(rp_ip,tmp->ip)==NULL){
            rp_ip = insert_r_ip(rp_ip, tmp);
            rp_name = insert_r_name(rp_name,tmp);
        }else{
            tmp2 = search_ip_r(rp_ip,tmp->ip);
            insert_login(tmp2,tmp);
        }
    }

    *rp_ip_ptr = rp_ip;
    *rp_name_ptr = rp_name;
    fclose(f);
    return;
}

bst *insert_r_ip(bst *rp, bst *tmp){
    if (rp==NULL){
        return tmp;
    }
    if (strcmp(tmp->ip,rp->ip)<0){
        rp->left_ip = insert_r_ip(rp->left_ip,tmp);
    }
    if (strcmp(tmp->ip,rp->ip)>0){
        rp->right_ip = insert_r_ip(rp->right_ip,tmp);
    }
    return rp;
}

//same as insert_r_id using name as key and left_name and right_name
bst *insert_r_name (bst *rp, bst *tmp){
    if (rp==NULL){
        return tmp;
    }
    if (strcmp(tmp->name,rp->name)<0){
        rp->left_name = insert_r_name(rp->left_name,tmp);
    }
    if (strcmp(tmp->name,rp->name)>0){
        rp->right_name = insert_r_name(rp->right_name,tmp);
    }
    return rp;
}

//free one rp
void bst_dispose(bst *rp){
    if (rp!=NULL){
        bst_dispose(rp->left_ip);
        bst_dispose(rp->right_ip);
        free(rp);
    }
    return;
}

//search the BST return NULL if not found.
bst *search_ip_r(bst *rp,char *ip){
    //not found
    if (rp==NULL){
        return NULL;
    }
    if (strcmp(ip,rp->ip)<0){
        return search_ip_r(rp->left_ip,ip);
    }
    if (strcmp(ip,rp->ip)>0){
        return search_ip_r(rp->right_ip,ip);
    }
    //if matching ip
    return rp;
}

void insert_login (bst *node, bst *tmp){
    tmp->login->next = node->login;
    node->login = tmp->login;
    return;
}

//write function to check the reading process
void write(bst *rp_ip,bst *rp_name){
    fprintf(stdout,"The BST with IP as they key. In Order:\n\n");
    bst_print_ip_r(rp_ip);
    fprintf(stdout,"\n\nThe BST with username as they key. In Order:\n\n");
    bst_print_name_r(rp_name);
    return;
}

void bst_print_ip_r(bst* rp){
    login *log;
    if (rp==NULL){
        return;
    }
    bst_print_ip_r(rp->left_ip);
    fprintf(stdout,"%s %s\n",rp->ip,rp->name);
    for(log = rp->login;log!=NULL;log=log->next){
        fprintf(stdout,"\t%s ",log->time);
        if (log->type == GET){
            fprintf(stdout,"GET ");
        }else{
            fprintf(stdout,"POST ");
        }
        fprintf(stdout,"%s ",log->resource);
        if (log->res == ACCEPT){
            fprintf(stdout,"200\n");
        }else{
            fprintf(stdout,"401\n");
        }
    }
    bst_print_ip_r (rp->right_ip);
    return;
}

void bst_print_name_r(bst* rp){
    login *log;
    if (rp==NULL){
        return;
    }
    bst_print_name_r(rp->left_name);
    fprintf(stdout,"%s %s\n",rp->ip,rp->name);
    for(log = rp->login;log!=NULL;log=log->next){
        fprintf(stdout,"\t%s ",log->time);
        if (log->type == GET){
            fprintf(stdout,"GET ");
        }else{
            fprintf(stdout,"POST ");
        }
        fprintf(stdout,"%s ",log->resource);
        if (log->res == ACCEPT){
            fprintf(stdout,"200\n");
        }else{
            fprintf(stdout,"401\n");
        }
    }
    bst_print_name_r (rp->right_name);
    return;
}
