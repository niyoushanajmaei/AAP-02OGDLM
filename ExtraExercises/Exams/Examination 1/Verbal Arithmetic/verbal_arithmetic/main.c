#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct character_s{
    char letter;
    int digit;
    struct character_s *next;
}character;

int string_to_int(character *st,int n,character *key);
character *int_to_string(int n,character *key);
int check_solution(character *st1, character *st2, character *key,character *sol);
int verbal_arithmetic_r (character *st1, character *st2,character *sol, character *key, int mark[10],int k, int pos);
character *create_key(character *st1, character *st2,character *sol,int *ptr);
character *create_strings(char *st);
void input_key(character **key_ptr);
void print_output(character *key);
character *new_character(void);
void free_memory(character *st1, character *st2,character *sol, character *key);

int main()
{
    /*
    define int mark[10] with all elements as 1
    get two strings and solution
    ask if verifying or generating solution
    if generating use verbal_arithmetic_r
        pass the total number of chars present in st1 and st2 as k
        make character *key with all present unique chars and all digits as -1
    if verifying use check_solution
        make character *key and pass as key
    free memory
    */

    int mark[10],k=0;
    char s1[9],s2[9],s[9],a,tmp[2];
    character *st1,*st2, *sol,*key;
    for (int i=0;i<10;i++){
        mark[i] = 1;
    }
    fprintf(stdout,"Enter the first string:\n");
    scanf("%s",s1);
    fprintf(stdout,"Enter the second string.\n");
    scanf("%s",s2);
    fprintf(stdout,"Enter the solution of the addition:\n");
    scanf("%s",s);
    fprintf(stdout,"Verify an answer of Generate a key? (V)or(G)\n");
    gets(tmp);
    scanf("%c",&a);
    st1 = create_strings(s1);
    st2 = create_strings(s2);
    sol = create_strings(s);
    key = create_key(st1,st2,sol,&k);
    if (a=='V' || a=='v'){
        input_key(&key);
        if (check_solution(st1,st2,key,sol)){
            fprintf(stdout,"The key is correct");
        }else{
            fprintf(stdout,"The key is wrong.");
        }
    }else if (a=='G' || a=='g'){
        if (verbal_arithmetic_r(st1,st2,sol,key,mark,k,0)){
            print_output(key);
        }else{
            fprintf(stdout,"No key found");
        }
    }else{
        fprintf(stderr,"Wrong command.");
        exit(1);
    }
    return 0;
}


int string_to_int(character *st,int n,character *key){
    int res = 0,i=1,found=0;
    character *ptr1, *ptr2;
    for (ptr1 = st;ptr1!=NULL;ptr1=ptr1->next){
        found = 0;
        for (ptr2=key;ptr2!=NULL && found ==0;ptr2=ptr2->next){
            if (ptr2->letter == ptr1->letter){
                ptr1->digit = ptr2->digit;
                res += ptr1->digit* pow(10,n-i);
                i++;
                found = 1;
            }
        }
    }
    return res;
}

character *int_to_string(int n,character *key){
    int tmp,found;
    character *hptr = NULL,*ptr,*tptr;
    // head insertion
    while(n>0){
        tmp = n %10;
        n = n / 10;
        found = 0;
        for (ptr = key;ptr!=NULL && found == 0;ptr=ptr->next){
            tptr = new_character();
            if (ptr->digit == tmp){
                tptr->digit = ptr->digit;
                tptr->letter = ptr->letter;
                tptr->next  = hptr;
                hptr = tptr;
                found = 1;
            }
        }
    }
    return hptr;
}

/*
check that the addition is correct and
no word starts with a 0
*/
int check_solution(character *st1, character *st2, character *key,character *sol){
    int op1,op2,res,n1=0,n2=0,n3=0;
    character *ptr1,*ptr2,*ptr3;
    for(ptr1=st1;ptr1!=NULL;ptr1=ptr1->next,n1++);
    for(ptr2=st2;ptr2!=NULL;ptr2=ptr2->next,n2++);
    for(ptr3=sol;ptr3!=NULL;ptr3=ptr3->next,n3++);
    op1 = string_to_int(st1,n1,key);
    op2 = string_to_int(st2,n2,key);
    res = string_to_int(sol,n3,key);
    if (((int)log10(op1))+1!=n1 || ((int)log10(op2))+1!=n2 || ((int)log10(res)+1)!=n3){
        return 0;
    }
    if(op1 +op2 == res){
        return 1;
    }
    return 0;
}

/*
character *key contains all present unique chars is st1 and st2
k is the total number of present chars
*/
int verbal_arithmetic_r (character *st1, character *st2,character *sol, character *key, int mark[10],int k, int pos){
    character *ptr;
    int i=0;
    if (pos==k){
        return check_solution(st1,st2,key,sol);
    }
    // make ptr point to the pos-th element of key
    for (ptr=key;i<pos;i++,ptr=ptr->next);
    // select key->digit and backtrack
    for (i=0;i<10;i++){
        if (mark[i]==1){
            ptr->digit = i;
            mark[i] = 0;
            if (verbal_arithmetic_r(st1,st2,sol,key,mark,k,pos+1)){
                return 1;
            }
            ptr->digit = -1;
            mark[i] =1;
        }
    }
    return 0;
}

character *create_key(character *st1, character *st2,character *sol,int *p){
    character *ptr,*ptrk,*tptr;
    character *key = NULL;
    int found, n = *p;
    for (ptr = st1;ptr!=NULL;ptr=ptr->next){
        found = 0;
        for (ptrk = key;ptrk!=NULL;ptrk=ptrk->next){
            if (ptrk->letter==ptr->letter){
                found = 1;
            }
        }
        if (found==0){
            tptr = new_character();
            tptr->letter = ptr->letter;
            tptr->digit = -1;
            tptr->next = key;
            key = tptr;
            n++;
        }
    }
    for (ptr = st2;ptr!=NULL;ptr=ptr->next){
        found = 0;
        for (ptrk = key;ptrk!=NULL;ptrk=ptrk->next){
            if (ptrk->letter==ptr->letter){
                found = 1;
            }
        }
        if (found==0){
            tptr = new_character();
            tptr->letter = ptr->letter;
            tptr->digit = -1;
            tptr->next = key;
            key = tptr;
            n++;
        }
    }
    for (ptr = sol;ptr!=NULL;ptr=ptr->next){
        found = 0;
        for (ptrk = key;ptrk!=NULL;ptrk=ptrk->next){
            if (ptrk->letter==ptr->letter){
                found = 1;
            }
        }
        if (found==0){
            tptr = new_character();
            tptr->letter = ptr->letter;
            tptr->digit = -1;
            tptr->next = key;
            key = tptr;
            n++;
        }
    }
    *p = n;
    return key;
}

character *create_strings(char *st){
    character *hptr = NULL,*tptr;
    int n = strlen(st),i=1;
    while (i<=n){
        tptr = new_character();
        tptr->letter = st[n-i];
        tptr->next = hptr;
        hptr = tptr;
        i++;
    }
    return hptr;
}

void input_key(character **key_ptr){
    character *key = *key_ptr;
    character *ptr;
    for (ptr = key;ptr!=NULL;ptr = ptr->next){
        fprintf(stdout,"%c = ? ",ptr->letter);
        scanf("%d",&ptr->digit);
    }
    *key_ptr = key;
    return;
}

void print_output(character *key){
    character *ptr;
    fprintf(stdout,"The Key is: \n");
    for (ptr = key;ptr!=NULL;ptr = ptr->next){
        fprintf(stdout,"%c : %d\n",ptr->letter,ptr->digit);
    }
    return;
}

character *new_character(void){
    character *tptr = malloc(sizeof(character));
    if (tptr==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return tptr;
}

void free_memory(character *st1, character *st2, character *sol, character *key){
    character *tptr,*hptr;
    hptr=st1;
    while(hptr!=NULL){
        tptr = hptr;
        hptr = hptr->next;
        free(tptr);
    }
    hptr=st2;
    while(hptr!=NULL){
        tptr = hptr;
        hptr = hptr->next;
        free(tptr);
    }
    hptr=key;
    while(hptr!=NULL){
        tptr = hptr;
        hptr = hptr->next;
        free(tptr);
    }
    hptr=sol;
    while(hptr!=NULL){
        tptr = hptr;
        hptr = hptr->next;
        free(tptr);
    }
    return;
}
