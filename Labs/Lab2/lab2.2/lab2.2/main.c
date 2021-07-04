#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define L 5

int main(int argc ,char *argv[])
{
    int cv [MAX];
    char temp [MAX +2];
    int v = 0, h = 0;

    for (int i=0; i<MAX;i++){
        cv[i] = 0;
    }

    if(argc!= 2){
        printf("wrong number of arguments.");
        return 1;
    }

   FILE *f = fopen(argv[1],"r");
   if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
   }

    while(fgets(temp, MAX +2 ,f) != NULL){
        int ch = 0;
        for(int i=0;temp[i]!='\0';i++){
            if (temp[i] == 'h'){
                ch ++;
                if (ch >= L){
                    h++;
                }
            }else{
                ch = 0;
            }
            if(temp[i] == 'v'){
                cv[i]++;
                if (cv[i]>=L){
                    v++;
                }
            }else{
                cv[i] =0;
            }

        }
    }
    printf("Horizontal Sequence: %d \nVertical Sequence  : %d",h,v);
    fclose(f);
    return 0;
}
