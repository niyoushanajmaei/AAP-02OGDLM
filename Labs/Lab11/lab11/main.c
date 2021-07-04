#include <stdio.h>
#include <stdlib.h>
#include "treePublic.h"
#include "st.h"

#define N 3



int main(int argc,char *argv[])
{
    node_t *rp = createEmptyTree();
    ST st;
    if (argc!= 3){
        fprintf(stderr,"Wrong number of arguments.\n");
        exit(1);
    }
    FILE *f_input = fopen(argv[1],"r");
    FILE *f_output = fopen(argv[2],"w");
    if (f_input==NULL || f_output == NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    rp = readTree(f_input);
    st = STinit(N);
    write_tree_in_table_r(rp,st);
    STdisplay(st);
    print_tree_levels(rp,st);
    freeTree(rp);
    fclose(f_input);
    fclose(f_output);
    return 0;
}


