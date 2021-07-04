#include <stdio.h>
#include <stdlib.h>

typedef struct clause_s clause_t;
typedef struct variable_s variable_t;

struct clause_s{
    int value;
    int n;
    int *f;

};


clause_t *read_file(FILE *f, int n);
int *find_mapping(clause_t *formula, int n,int m);
int find_mapping_r(clause_t *formula, int n, int m, int *mapping,int pos);
int solve(clause_t *formula,int *mapping ,int n, int m);

int main(int argc, char *argv[])
{
    clause_t *formula;
    int *mapping;
    int n,m;
    FILE *f;
    if (argc!=2){
        fprintf(stderr,"Wrong number of arguments.\n");
        exit(1);
    }

    f=fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d %d",&n,&m);
    formula = malloc(n*sizeof(clause_t));
    if (formula==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    formula = read_file(f,n);
    mapping = find_mapping(formula,n,m);
    if(mapping !=NULL){
        for(int i=0;i<m;i++){
            fprintf(stdout,"x_%d = %d\n",i+1,mapping[i]);
        }
    }else{
        fprintf(stdout,"No mapping found.\n");
    }

    for(int i=0;i<n;i++){
        free(formula[i].f);
    }
    free(formula);
    free(mapping);
    fclose(f);
    return 0;
}

clause_t *read_file(FILE *f, int n){
    clause_t *formula = malloc(n*sizeof(clause_t));
    int i,j;
    if(formula==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    for(i=0;i<n;i++){
        fscanf(f,"%d",&formula[i].n);
        formula[i].f = malloc(formula[i].n *sizeof(int));
        if (formula[i].f==NULL){
            fprintf(stderr,"Error allocating memory.\n");
            exit(1);
        }
        for(j=0;j<formula[i].n;j++){
            fscanf(f,"%d",&formula[i].f[j]);
        }
    }

    return formula;
}

int *find_mapping(clause_t *formula, int n,int m){
    int *mapping = malloc(m*sizeof(int));
    if (mapping ==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    if(find_mapping_r(formula,n,m,mapping,0)){
        return mapping;
    }
    return NULL;
}

int find_mapping_r(clause_t *formula, int n, int m,int *mapping,int pos){
    int i;
    if(pos >= m){
        return (solve(formula,mapping,n,m));
    }
    for (i=0;i<2;i++){
        mapping[pos] = i;
        if (find_mapping_r(formula,n,m,mapping,pos+1)){
            return 1;
        }
    }
    return 0;
}

int solve(clause_t *formula,int *mapping ,int n, int m){
    int res = 1,i,j,tmp,var;

    for(i=0;i<n;i++){
        tmp = 0;
        for (j=0;j<formula[i].n;j++){

            if (formula[i].f[j]<0){
                formula[i].f[j] *=-1;
                var = mapping[formula[i].f[j]-1];
                var = (var+1)%2;
                formula[i].f[j] *=-1;
            }else{
                var = mapping[formula[i].f[j]-1];
            }

            tmp+= var;

            if (tmp>1)
                tmp = 1;
        }
        res *= tmp;
    }
    return res;
}

