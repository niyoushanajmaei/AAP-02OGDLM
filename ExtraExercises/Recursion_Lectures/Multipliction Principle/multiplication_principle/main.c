#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_choices;
    int *choices;
}level;

/* print all combinations
    first choice: 0,1
    second choice: 0,1,2
    third choice: 0,1
*/

int main()
{
    int n = 3;
    int pos =0,count = 0;
    int *sol = malloc(n*sizeof(int));
    if (sol==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    level *val = malloc(n*sizeof(level));
    if(val==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }

    val[0].num_choices = 2;
    val[1].num_choices = 3;
    val[2].num_choices = 2;

    for (int i=0;i<n;i++){
        val[i].choices = malloc(val[i].num_choices * sizeof(int));
        if (val[i].choices == NULL){
            fprintf(stderr,"Error allocating memory.");
            exit(1);
        }
    }

    for (int i=0;i<n;i++){
        for (int j = 0;j<2;j++){
            val[i].choices[j] = j;
        }
    }
    val[1].choices[2] = 2;

    count = mult_princ(val,sol,count,pos,n);
    fprintf(stdout,"%d solutions.",count);

    free(sol);
    for (int i=0;i<n;i++){
        free(val[i].choices);
    }
    free(val);
    return 0;
}

int mult_princ (level *val, int *sol, int count, int pos, int n){
    int i;
    if (pos>=n){
        for (i=0;i<n;i++){
            fprintf(stdout,"%d ",sol[i]);
        }
        fprintf(stdout,"\n");
        return count +1;
    }

    for (i=0;i<val[pos].num_choices;i++){
        sol[pos] = val[pos].choices[i];
        count = mult_princ(val,sol,count,pos+1,n);
    }
    return count;
}
