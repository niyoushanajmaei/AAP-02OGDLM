#include <stdio.h>
#include <stdlib.h>
#include "bstPublic.h"

/*
 To get an average logarithmic complexity, we must store the data in a BST. operations on a BST
have an average logarithmic cost because the cost is related to the height of the BST which in average case
grows logarithmically
 the access of each person can be stored in a list with cost O(n).
 We have two set of keys, we can implement two physical BSTs but to save storage, we use one
physical BST that
 is in fact two logical BSTs. using two sets of left and right pointers for each element of the
physical BST.
 using head insertions on the list.
*/

int main(){
    char *file_name = "input.txt";
    bst *rp_ip,*rp_name;
    read(file_name,&rp_ip,&rp_name);
    write(rp_ip,rp_name);
    bst_dispose(rp_ip);
    return 0;
}

