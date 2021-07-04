#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_S 20
#define MAX_L 100

typedef struct word_s{
    char *text;
    int n ;
    struct word_s *next;
}word;

word *read_input(char *file_name);
word *add_word(word *words, char *text);
void write_output(char *file_name, word *words);
word *new_word(void);

int main()
{
    /* if (argc!= 3){
        fprintf(stderr,"wrong number of arguments.");
        exit(1);
    }
    word *words = read_input(argv[1]);
    write_output(argv[2],words);
    */

    char *input_file = "input.txt";
    char *output_file = "output.txt";
    word *words = read_input(input_file);
    write_output(output_file,words);

    while (words != NULL){
        word *tmp = words;
        words = words->next;
        free(tmp->text);
        free(tmp);
    }

    return 0;
}

word *read_input(char *file_name){
    word *words = NULL;
    char text[MAX_S+1],line[MAX_L+2];
    FILE *f = fopen(file_name,"r");
    if (f == NULL ){
        printf("error opening files.\n");
        exit(1);
    }
    while(fgets(line,MAX_L+2,f)!=NULL){
        int j = 0;
        for (int i= 0;line[i]!='\n';i++){
            text[j] = tolower(line[i]);
            j++;
            if (line[i]==' '){
                text[j] = '\0';
                words = add_word(words,text);
                j = 0;
            }
        }
        text[j] = '\0';
        words = add_word(words,text);
        j = 0;
    }
    fclose(f);
    return words;
}

/* ordered insertion */

word *add_word(word *words, char *text){
    word *hptr = words;
    word *ptr, *tmp, *ptr2;
    int found = 0;
    for (ptr = hptr; ptr != NULL && found == 0;ptr = ptr->next){
        if (strcmp(ptr->text,text)==0){
            ptr->n++;
            found = 1;
        }
    }
    if (found ==0){
        tmp = new_word();
        tmp->text = strdup(text);
        tmp->n = 1;
        if (hptr ==NULL){
            tmp->next = hptr;
            hptr = tmp;
        }else if(hptr->next == NULL){
            if (strcmp(hptr->text,tmp->text)>0){
                tmp->next = hptr;
                hptr = tmp;
            }else{
                tmp->next =  NULL;
                hptr->next = tmp;
            }
        }else{
            int done = 0;
            for (ptr = hptr, ptr2 = hptr->next;ptr2 != NULL && done == 0;ptr = ptr->next , ptr2 = ptr2->next){
                if (strcmp(ptr->text,tmp->text)>0){
                    tmp->next = hptr;
                    hptr = tmp;
                    done = 1;
                }
                else if (strcmp(ptr2->text,tmp->text) > 0){
                    tmp->next = ptr->next;
                    ptr->next = tmp;
                    done = 1;
                }
            }
        }
    }
    return hptr;
}

void write_output(char *file_name, word *words){
    word *ptr ;
    FILE *f = fopen(file_name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    for (ptr = words; ptr!=NULL;ptr = ptr->next){
        fprintf(f,"%s %d\n",ptr->text,ptr->n);
    }
    fclose(f);
    return;
}

word *new_word(void){
    word *tmp = malloc (sizeof(word));
    if (tmp ==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    return tmp;
}

