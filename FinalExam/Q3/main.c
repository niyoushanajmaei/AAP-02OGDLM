#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 20

// 1 for the code implemented in the exam text, 0 for the better version I wrote offline
#define EXAM 0

/*
 we store the permutations in a circular list and check if it already exists
 using a function that sets the hptr on the first char of the element of the list on
 the first char of the element we're searching for and traverses the two elements together.
 using tail insertions and making the last element point to the first element.
 backtracking using removal from the current permutation
*/

#if EXAM
typedef struct circlist_s circlist;
typedef struct list_s list;

struct circlist_s{
    char id;
    circlist *next;
};

struct list_s{
    circlist *perm;
    list *next;
};

void circularPermutation (char *str);
void circularPermutation_r (char *str, list **lp,circlist *perm,int n, int pos, int* used);
int inList(list *sol, circlist *perm);
list *insertinList(list *sol, circlist *perm);
circlist *insertinPerm (circlist *perm, char c);
void quit(list *sol);
void printlist(list *sol);
circlist* removefromPerm (circlist *perm);
void printperm(circlist *perm);

int main(){
    char str[M];
    fprintf(stdout,"Enter the str:\n");
    scanf("%s",str);
    circularPermutation(str);
    return 0;
}

void circularPermutation (char *str){
    int *used;
    circlist *perm = NULL;
    list *sol = NULL;
    used = malloc(strlen(str)*sizeof(int));
    if (used == NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }

    for (int i =0;i<strlen(str);i++){
        used[i]=0;
    }
    circularPermutation_r(str,&sol,perm,strlen(str),0,used);
    printlist(sol);
    quit(sol);
    return;
}

void circularPermutation_r (char *str, list **lp,circlist *perm, int n, int pos, int *used){
    int i;
    if (pos>=n){
        if (!inList(*lp,perm)){
            *lp = insertinList(*lp,perm);
        }
        return ;
    }

    for (i=0;i<n;i++){
        if (used[i]==0){
            perm = insertinPerm(perm,str[i]);
            used[i] = 1;
            circularPermutation_r(str,lp,perm,n,pos+1,used);
            perm = removefromPerm(perm);
            used[i] = 0;
        }
    }
    return;
}


//set the hptr on the first element and traverse together;
int inList (list *l, circlist *perm){
    list *hl;
    circlist *hp, *pp;
    int same;
    if (l==NULL){
        return 0;
    }

    for (hl=l;hl!=NULL;hl=hl->next){
        hp = hl->perm;
        pp = perm;
        same = 1;
        while(pp->id!= hp->id){
            pp = pp->next;
        }
        do {
            if (hp->id != pp->id){
                same = 0;
            }
            pp = pp->next;
            hp = hp->next;
        }while (hp!=hl->perm && same == 1);
        if (same == 1){
            return 1;
        }
    }
    return 0;
}

//tail insertion on list.
list *insertinList(list *l, circlist *perm){
    list *ptr, *tmp;
    circlist *p = perm,*tp = NULL;
    tmp = malloc(sizeof(list));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    do{
        tp = insertinPerm(tp,p->id);
        p=p->next;
    }while(p!=perm);

    tmp->perm = tp;
    tmp->next = NULL;
    if (l==NULL){
        l = tmp;
        return l;
    }

    for (ptr = l;ptr->next!=NULL;ptr = ptr->next);
    ptr->next = tmp;
    return l;
}

//tail insertion on Perm.
circlist *insertinPerm (circlist *perm, char c){
    circlist *tmp, *ptr;
    tmp = malloc(sizeof(circlist));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    tmp->id = c;
    tmp->next = NULL;
    if(perm==NULL){
        perm = tmp;
        perm->next = perm;
        return perm;
    }
    if(perm->next == perm){
        tmp->next = perm;
        perm ->next = tmp;
        return perm;
    }
    for (ptr = perm;ptr->next!=perm;ptr = ptr->next);
    tmp->next = perm;
    ptr->next = tmp;
    return perm;
}

//remove from perm's tail.
circlist *removefromPerm(circlist *perm){
    circlist *ptr,*tmp;
    if (perm->next==perm){
        return NULL;
    }
    for (ptr = perm;ptr->next->next!=perm;ptr = ptr->next);
    tmp = ptr->next;
    ptr ->next = perm;
    free(tmp);
    return perm;
}

//free list
void quit(list *l){
    list *tl;
    circlist *tc, *head ;
    while (l!=NULL){
        tl = l;
        l = l->next;
        head = tl->perm;
        while(tl->perm->next!=head){
            tc = tl->perm->next;
            tl->perm->next = tl->perm->next->next;
            free(tc);
        }
        free(head);
        free(tl);
    }
    return;
}

//print all elements of the list as a permutation.
void printlist(list *l){
    list *ptr;
    for (ptr = l;ptr!=NULL;ptr = ptr->next){
        printperm(ptr->perm);
    }
    return;
}

void printperm(circlist *perm){
    circlist *ptr = perm;
    do {
        fprintf(stdout,"%c ",ptr->id);
        ptr= ptr->next;
    }while(ptr!=perm);
    fprintf(stdout,"\n");
    return;
}

#elif !EXAM

void circularPermutation (char *str);
void circularPermutation_r (char *str, char *perm,int n, int pos, int* used);


int main(){
    char str[M];
    fprintf(stdout,"Enter the str:\n");
    scanf("%s",str);
    fprintf(stdout,"Circular Permutations:\n");
    circularPermutation(str);
    return 0;
}

void circularPermutation (char *str){
    int *used;
    char perm[strlen(str)];
    used = calloc(0,strlen(str)*sizeof(int));
    if (used == NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    used[0] = 1;
    perm[0] = str[0];
    circularPermutation_r(str,perm,strlen(str),1,used);
    return;
}

void circularPermutation_r (char *str, char *perm, int n, int pos, int *used){
    int i;
    if (pos>=n){
        fprintf(stdout,"%s\n",perm);
        return ;
    }
    for (i=0;i<n;i++){
        if (used[i]==0){
            perm[pos] = str[i];
            used[i] = 1;
            circularPermutation_r(str,perm,n,pos+1,used);
            used[i] = 0;
        }
    }
    return;
}


#endif
