#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Rectangle {
    char name[5];
    float points [2][2];
    float a;
    float p;
    int n;
} rect;

rect *read_input(char *name,int *n);
int exists(rect *rect,char name[],int n);
void compute_ap(rect *rect,int i);
void sort_array (rect *rect,char c,int n);

int main()
{
    int n;
    rect *rects;
    FILE *f2 = fopen("file2.txt","w");
    FILE *f3 = fopen("file3.txt","w");

    if(f2==NULL ||f3==NULL){
        printf("Error in opening the files.\n");
        exit(1);
    }
    rects = read_input("file1.txt",&n);
    sort_array(rects,'a',n);
    for (int i=n-1;i>=0;i--){
        fprintf(f2,"%s\n",rects[i].name);
    }

    sort_array(rects,'p',n);
    for (int i=n-1;i>=0;i--){
        fprintf(f3,"%s\n",rects[i].name);
    }

    fclose(f2);
    fclose(f3);
    free(rects);
    return 0;
}

rect *read_input(char *name,int *p){
    rect *rects;
    int end = 0;
    int i;
    char temp_name[5];
    float temp_x,temp_y;
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    fscanf(f,"%d",p);
    rects = malloc(*p * sizeof(rect));
    if (rects==NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    while (fscanf(f,"%s %f %f",temp_name,&temp_x,&temp_y)==3){
        i = exists(rects,temp_name,end);
        if (i==-1){
            strcpy(rects[end].name,temp_name);
            rects[end].points[0][0] = temp_x;
            rects[end].points[0][1] = temp_y;
            rects[end].n = 1;
            end++;
        }else if(rects[i].n==1){
            rects[i].points[1][0] = temp_x;
            rects[i].points[1][1] = temp_y;
            rects[i].n = 2;
            compute_ap(rects,i);
        }
    }
    fclose(f);
    return rects;
}

int exists(rect *rects,char name[],int n){
    int res = -1;
    int found = 0;
    for (int i=0;i<n && found == 0;i++){
        if (strcmp(rects[i].name,name)==0){
            res = i;
            found = 1;
        }
    }
    return res;
}

void compute_ap(rect *rects,int i){
    float x = fabs(rects[i].points[0][0] - rects[i].points[1][0]);
    float y = fabs(rects[i].points[0][1] - rects[i].points[1][1]);
    rects[i].a = (x*y);
    rects[i].p = 2*(x+y);
    return;
}

void sort_array (rect *rects,char t,int n){
    float tempf;
    char temps[5];
    int i,j,c;
    if (t=='a'){
        for(i=0;i<n-1;i++){
            c = i;
            for(j=i+1;j<n;j++){
                if(rects[j].a<rects[c].a){
                    c = j;
                }
            }
            tempf = rects[i].a;
            rects[i].a = rects[c].a;
            rects[c].a = tempf;
            tempf = rects[i].p;
            rects[i].p = rects[c].p;
            rects[c].p = tempf;
            strcpy(temps, rects[i].name);
            strcpy(rects[i].name, rects[c].name);
            strcpy(rects[c].name, temps);

       }
    }else{
        for(i=0;i<n-1;i++){
            c = i;
            for(j=i+1;j<n;j++){
                if(rects[j].p<rects[c].p){
                    c = j;
                }
            }
            tempf = rects[i].a;
            rects[i].a = rects[c].a;
            rects[c].a = tempf;
            tempf = rects[i].p;
            rects[i].p = rects[c].p;
            rects[c].p = tempf;
            strcpy(temps, rects[i].name);
            strcpy(rects[i].name,rects[c].name);
            strcpy(rects[c].name, temps);

       }
    }
    return;
}

