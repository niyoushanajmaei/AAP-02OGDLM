#include <stdio.h>
#include <stdlib.h>

/*
    used=1 if tile used as in file
    used=-1 if tile used revers
    used=0 if not used
*/

typedef struct tile_s{
    int id;
    int n1;
    int n2;
    int used;
}tile;

/*
    init does malloc and initiliazing
*/

tile * read_file(char *file_name,int *p);
tile *init(int n);
int chain(tile *list, tile *curr,tile *best, int i, int n);
void chain_r(tile *list, tile *curr,tile *best, int cl, int *bl_ptr, int n);
void print_chain(tile *sol,char *file_name, int n);

int main(int argc, char *argv[])
{
    int n,bl = 0,i;
    tile *list,*curr,*best;
    if (argc!= 4){
        fprintf(stderr,"Wrong number of arguments.\n");
        exit(1);
    }

    sscanf(argv[2],"%d",&i);

    list = read_file(argv[1],&n);

    curr = init(n);
    best = init(n);
    bl = chain(list,curr,best,i,n);

    fprintf(stdout,"%d \n",bl);
    for(int i=0;i<bl;i++){
        fprintf(stdout,"%d  %d-%d\n",best[i].id,best[i].n1,best[i].n2);
    }

    free(list);
    free(curr);
    free(best);
    return 0;
}

tile *read_file(char *file_name,int *p){
    tile *list;
    int n = 0;
    char tmp[10];
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }

    for (;fgets(tmp,10,f)!=NULL;n++);
    list = init(n);
    fclose(f);
    f = fopen(file_name,"r");

    for (int i =0;i<n;i++){
        fgets(tmp,10,f);
        sscanf(tmp,"%d %d-%d",&list[i].id,&list[i].n1,&list[i].n2);
    }
    fclose(f);
    *p = n;
    return list;
}

tile *init(int n){
    tile *list = malloc(n*sizeof(tile));
    if (list==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    for (int i=0;i<n;i++){
        list[i].id = -1;
        list[i].n1= -1;
        list[i].n2 = -1;
        list[i].used = 0;
    }
    return list;
}

int chain(tile *list, tile *curr,tile *best, int i,int n){
    int l1 = 0,l2 = 0,j;
    tile *b1, *b2;
    //find first dominoes and recur with both used=1 and used=-1
    for (j=0;j<n;j++){
        if(list[j].id==i){
            b1 = init(n);
            b2 = init(n);

            curr[0].id = list[j].id;
            curr[0].n1 = list[j].n1;
            curr[0].n2 = list[j].n2;
            list[j].used = 1;
            chain_r(list,curr,b1,1,&l1,n);
            for (int c=0;c<n;c++){
                list[c].used = 0;
            }
            curr[0].n1 = list[j].n2;
            curr[0].n2 = list[j].n1;
            list[j].used = -1;
            chain_r(list,curr,b2,1,&l2,n);
            if (l1>=l2){
                for (int k=0;k<l1;k++){
                    best[k] = b1[k];
                }
                return l1;
            }else{
                for (int k=0;k<l2;k++){
                    best[k] = b2[k];
                }
                return l2;
            }
        }
    }

    return -1;
}

void chain_r(tile *list, tile *curr,tile *best, int cl, int *bl_ptr,int n){
    int i;
    if(cl>*bl_ptr){
        for (i=0;i<cl;i++){
            best[i].id = curr[i].id;
            best[i].n1 = curr[i].n1;
            best[i].n2 = curr[i].n2;
        }
        *bl_ptr = cl;
    }
    for (int i=0;i<n;i++){
        //using the tile as it is
        if (list[i].used == 0 && list[i].n1 == curr[cl-1].n2){
            curr[cl].id = list[i].id;
            curr[cl].n1 = list[i].n1;
            curr[cl].n2 = list[i].n2;
            list[i].used = 1;
            chain_r(list,curr,best,cl+1,bl_ptr,n);
            list[i].used = 0;
        }
        //using the tile backwards
        if (list[i].used == 0 && list[i].n2 == curr[cl-1].n2){
            curr[cl].id = list[i].id;
            curr[cl].n2 = list[i].n1;
            curr[cl].n1 = list[i].n2;
            list[i].used = -1;
            chain_r(list,curr,best,cl+1,bl_ptr,n);
            list[i].used = 0;
        }
    }

    return;
}

void print_chain(tile *sol,char *file_name,int n){
    FILE *f = fopen(file_name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }

    fprintf(f,"%d \n",n);
    for(int i=0;i<n;i++){
        fprintf(f,"%d  %d-%d\n",sol[i].id,sol[i].n1,sol[i].n2);
    }

    fclose(f);
    return;
}
