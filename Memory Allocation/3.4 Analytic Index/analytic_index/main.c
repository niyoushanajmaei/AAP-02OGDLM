#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX_C 100
#define MAX_W 20
#define MAX_I 10

typedef struct INDEX{
    char word[MAX_W+1];
    int c;
    int index[MAX_I];
}index;

index *word_read(char *name, int *num_ptr);
void text_read(char *name,index *indexes,int n);
void index_display(index *indexes,int n);
int compare (char *src,char *dst);

int main()
{
    char *file_name_1 = "file1.txt";
    char *file_name_2 = "file2.txt";
    int n;

    index *indexes = word_read(file_name_2,&n);
    text_read(file_name_1,indexes,n);
    index_display(indexes,n);

    free(indexes);
    return 0;
}

index *word_read(char *name, int *num_ptr){
    FILE *f =fopen(name,"r");
    fscanf(f,"%d",num_ptr);
    int n = *num_ptr;
    index *indexes = malloc(n *sizeof(index));
    if (indexes == NULL){
        fprintf(stderr,"Error allocating memory\n");
        exit(1);
    }
    int i;
    for (i=0;i<n;i++){
        fscanf(f,"%s",indexes[i].word);
        indexes[i].c = 0;
    }
    fclose(f);
    return indexes;
}

void text_read(char *name,index *indexes,int n){
    FILE *f = fopen(name,"r");
    int i;
    int pos =0;
    char temp[MAX_W+1];
    while(fscanf(f,"%s",temp)==1){
        pos++;
        for(i=0;i<n;i++){
            if (!compare(temp,indexes[i].word)){
                indexes[i].c ++;
                if (indexes[i].c <= MAX_I){
                    indexes[i].index[indexes[i].c-1] = pos;
                }
            }
        }
    }
    fclose(f);
}

void index_display(index *indexes,int n){
    for(int i=0;i<n;i++){
        printf("%s - occurrence(s): %d - position(s): ",indexes[i].word,indexes[i].c);
        for(int j=0;j<indexes[i].c;j++){
            printf("%d ",indexes[i].index[j]);
        }
        printf("\n");
    }
}

int compare (char *src,char *dst){
    int flag = 0;
    int done = 0;
    int i ;
    for(i=0;i<strlen(src) && i<strlen(dst) && done == 0;i++){
        if (tolower(src[i]) != tolower(dst[i])){
            flag = 1;
            done = 1;
        }
    }
    if(i!= strlen(src) || i!= strlen(dst)){
        flag = 1;
    }
    return flag;
}
