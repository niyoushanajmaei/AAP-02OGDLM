#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH   20
#define MAX_WORD_NUMBER  100
#define MAX_LINE_LENGTH  100

typedef struct {
  char word[MAX_WORD_LENGTH+1];
  int occurrences;
} index;

index *read_words(char *name , int *p);
void read_text(char *name, index *words, int n);
void display_index(index *words, int n);
int compare(char *st1, char *st2);

int main()
{
    char *input_st = "input.txt";
    char *words_st = "words.txt";
    int n;
    index *words = read_words(words_st,&n);
    read_text(input_st,words,n);
    display_index(words,n);
    free(words);
    return 0;
}

index *read_words(char *name , int *p){
    index *words;
    FILE *f = fopen(name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d",p);
    words = malloc(*p *sizeof(index));
    if (words == NULL){
        fprintf(stderr,"Error allocating memory");
        fclose(f);
        exit(1);
    }
    for (int i=0;i<*p;i++){
        fscanf(f,"%s",words[i].word);
        words[i].occurrences = 0;
    }
    fclose(f);
    return words;
}

void read_text(char *name, index *words, int n){
    char temp[MAX_WORD_LENGTH+1];
    FILE *f = fopen(name,"r");
    if(f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    while (fscanf(f,"%s",temp)!= EOF){
        int found = 0;
        for (int i=0;i<n && found == 0;i++){
            if (compare(words[i].word,temp)){
                words[i].occurrences ++;
                found = 1;
            }
        }
    }
    fclose(f);
    return;
}

void display_index(index *words, int n){
    for (int i=0;i<n;i++){
        fprintf(stdout,"%s: %d\n",words[i].word,words[i].occurrences);
    }
}

int compare(char *st1, char *st2){
    if (strlen(st1) != strlen(st2)){
        return 0;
    }
    for (int i=0;i<strlen(st1) ;i++){
        if (tolower(st1[i])!= tolower(st2[i])){
            return 0;
        }
    }
    return 1;
}
