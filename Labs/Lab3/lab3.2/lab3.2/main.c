#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Rectangle {
    char name[5];
    float points [2][2];
    float a;
    float p;
} rect;

int exists(rect arr[],char name[],int n);
void compute_ap(rect arr[],int i);
void sort_array (rect arr[],char c,int n);

int main()
{
    rect arr[100];
    int s[100];
    int i;
    int end = 0;
    char temp_name[5];
    float temp_x,temp_y;
    FILE *f1 = fopen("file1.txt","r");
    FILE *f2 = fopen("file2.txt","w");
    FILE *f3 = fopen("file3.txt","w");

    if(f1==NULL ||f2==NULL ||f3==NULL){
        printf("Error in opening the files.\n");
        exit(1);
    }
    while (fscanf(f1,"%s %f %f",temp_name,&temp_x,&temp_y)==3){
        i = exists(arr,temp_name,end);
        if (i==-1){
            strcpy(arr[end].name,temp_name);
            arr[end].points[0][0] = temp_x;
            arr[end].points[0][1] = temp_y;
            s[end] = 1;
            end++;
        }else if(s[i]==1){
            arr[i].points[1][0] = temp_x;
            arr[i].points[1][1] = temp_y;
            s[i] = 2;
            compute_ap(arr,i);
        }
    }

    sort_array(arr,'a',end);
    for (i=end-1;i>=0;i--){
        fprintf(f2,"%s\n",arr[i].name);
    }

    sort_array(arr,'p',end);
    for (i=end-1;i>=0;i--){
        fprintf(f3,"%s\n",arr[i].name);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

int exists(rect arr[],char name[],int n){
    int res = -1;
    int found = 0;
    for (int i=0;i<n && found == 0;i++){
        if (strcmp(arr[i].name,name)==0){
            res = i;
            found = 1;
        }
    }
    return res;
}

void compute_ap(rect arr[],int i){
    float x = fabs(arr[i].points[0][0] - arr[i].points[1][0]);
    float y = fabs(arr[i].points[0][1] - arr[i].points[1][1]);
    arr[i].a = (x*y);
    arr[i].p = 2*(x+y);
}

void sort_array (rect arr[],char t,int n){
    float tempf;
    char temps[5];
    int i,j,c;
    if (t=='a'){
        for(i=0;i<n-1;i++){
            c = i;
            for(j=i+1;j<n;j++){
                if(arr[j].a<arr[c].a){
                    c = j;
                }
            }
            tempf = arr[i].a;
            arr[i].a = arr[c].a;
            arr[c].a = tempf;
            tempf = arr[i].p;
            arr[i].p = arr[c].p;
            arr[c].p = tempf;
            strcpy(temps, arr[i].name);
            strcpy(arr[i].name, arr[c].name);
            strcpy(arr[c].name, temps);

       }
    }else{
        for(i=0;i<n-1;i++){
            c = i;
            for(j=i+1;j<n;j++){
                if(arr[j].p<arr[c].p){
                    c = j;
                }
            }
            tempf = arr[i].a;
            arr[i].a = arr[c].a;
            arr[c].a = tempf;
            tempf = arr[i].p;
            arr[i].p = arr[c].p;
            arr[c].p = tempf;
            strcpy(temps, arr[i].name);
            strcpy(arr[i].name, arr[c].name);
            strcpy(arr[c].name, temps);

       }
    }
}

