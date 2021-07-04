#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct box_s box_t;
typedef struct truck_s truck_t;

struct box_s{
    int r,c,used,id;
};

struct truck_s{
    int r,c;
    int **mat;
};

box_t *read_file(char *file_name,int *p);
truck_t *trucks_init(void);
int find_truck(truck_t *trucks, box_t *boxes,int n);
int load_truck_r(truck_t t, box_t *boxes, int n,int pos, int r0, int c0);
void write_truck(truck_t t);
int is_free(truck_t t, box_t box, int r, int c);
void place_b(truck_t t, box_t box, int r, int c);
void remove_b(truck_t t, box_t box, int r, int c);

int main(int argc, char *argv[])
{
    truck_t *trucks;
    box_t *boxes;
    int n = 0,i;
    if (argc!= 2){
        fprintf(stderr,"Wrong number of arguments.\n");
        exit(1);
    }

    trucks = trucks_init();
    boxes = read_file(argv[1],&n);
    i = find_truck(trucks,boxes,n);
    if (i==-1){
        fprintf(stdout,"No truck found.\n");
    }else{
        write_truck(trucks[i]);
    }
    free(trucks);
    free(boxes);
    return 0;
}

box_t *read_file(char *file_name,int *p){
    box_t *boxes;
    FILE *f  = fopen(file_name,"r");
    int n;
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }

    fscanf(f,"%d",&n);

    boxes = malloc(n*sizeof(box_t));
    if(boxes==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }

    for (int i=0;i<n;i++){
        fscanf(f,"%dx%d",&boxes[i].r,&boxes[i].c);
        boxes[i].used = 0;
        boxes[i].id = i+1;
    }

    *p = n;
    fclose(f);
    return boxes;
}

truck_t *trucks_init(void){
    int r[4] = {10,10,15,20};
    int c[4] = {15,20,25,30};
    truck_t *trucks = malloc(4 * sizeof(truck_t));
    if (trucks==NULL){
        fprintf(stderr,"Error allocating memory.\n");
        exit(1);
    }
    for (int i=0;i<4;i++){
        trucks[i].r = r[i];
        trucks[i].c = c[i];
        trucks[i].mat = malloc(r[i]* sizeof(int *));
        if (trucks[i].mat==NULL){
            fprintf(stdout,"Error allocating memory.\n");
            exit(1);
        }
        for (int j=0;j<trucks[i].r;j++){
            trucks[i].mat[j] = malloc(c[i]*sizeof(int));
            if(trucks[i].mat[j]==NULL){
                fprintf(stderr,"Error allocating memory.\n");
                exit(1);
            }
            for(int k=0;k<trucks[i].c;k++){
                trucks[i].mat[j][k] = 0;
            }
        }
    }
    return trucks;
}

int find_truck(truck_t *trucks, box_t *boxes,int n){
    int i, min_s = INT_MAX,min_id = -1;
    for (i=0;i<4;i++){
        for(int j=0;j<n;j++){
            boxes[j].used = 0;
        }
        if(load_truck_r(trucks[i],boxes,n,0,0,0)){
            if(trucks[i].r * trucks[i].c <min_s){
                min_s = trucks[i].r * trucks[i].c;
                min_id = i;
            }
        }
    }

    return min_id;
}

int load_truck_r(truck_t t, box_t *boxes, int n,int pos, int r0, int c0){
    int i,r,c,tmp;
    if(pos>=n){
        return 1;
    }
    for(i=0;i<n;i++){
        if(boxes[i].used == 0){
            // putting the box as it is
            for (r=r0;r<t.r-boxes[i].r;r++){
                for (c=((r==r0)?(c0):0);c<t.c-boxes[i].c;c++){
                    if (is_free(t,boxes[i],r,c)){
                        place_b(t,boxes[i],r,c);
                        boxes[i].used = 1;
                        if(load_truck_r(t,boxes,n,pos+1,0,0)){
                            return 1;
                        }
                        boxes[i].used = 0;
                        remove_b(t,boxes[i],r,c);
                    }
                }
            }
            // putting the box the other way
            tmp = boxes[i].r;
            boxes[i].r = boxes[i].c;
            boxes[i].c = tmp;
            for (r=r0;r<t.r-boxes[i].r;r++){
                for (c=((r==r0)?(c0):0);c<t.c-boxes[i].c;c++){
                    if (is_free(t,boxes[i],r,c)){
                        place_b(t,boxes[i],r,c);
                        boxes[i].used = 1;
                        if(load_truck_r(t,boxes,n,pos+1,0,0)){
                            return 1;
                        }
                        boxes[i].used = 0;
                        remove_b(t,boxes[i],r,c);
                    }
                }
            }
            tmp = boxes[i].r;
            boxes[i].r = boxes[i].c;
            boxes[i].c = tmp;
        }
    }
    return 0;
}

void write_truck(truck_t t){
    for (int i=0;i<t.r;i++){
        for (int j=0;j<t.c;j++){
            if (t.mat[i][j]==0){
                fprintf(stdout,"x");
            }else{
                fprintf(stdout,"%d",t.mat[i][j]);
            }
        }
        fprintf(stdout,"\n");
    }
    return;
}

//places the box in r,c of the truck, returns 1 if successful
int is_free(truck_t t, box_t box, int r, int c){
    for(int i=r;i<r+box.r;i++){
        for (int j=c;j<c+box.c;j++){
            if(t.mat[i][j]!=0){
                return 0;
            }
        }
    }
    return 1;
}

void place_b(truck_t t, box_t box, int r, int c){
    for(int i=r;i<r+box.r;i++){
        for (int j=c;j<c+box.c;j++){
            t.mat[i][j] = box.id;
        }
    }
    return;
}

void remove_b(truck_t t, box_t box, int r, int c){
    for(int i=r;i<r+box.r;i++){
        for (int j=c;j<c+box.c;j++){
            t.mat[i][j] = 0;
        }
    }
    return;
}
