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

void read_input(char *file_name, word **head, word **tail);
void add_word(word **head, word **tail, char *text);
void write_output(char *file_name, word *head);
word *new_word(void);
void free_memory(word *hptr);

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
    word *words_head = NULL;
    word *words_tail = NULL;
    read_input(input_file, &words_head, &words_tail);
    write_output(output_file,words_head);



    return 0;
}

void read_input(char *file_name, word **head, word **tail){
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
                add_word(head,tail,text);
                j = 0;
            }
        }
        text[j] = '\0';
        add_word(head,tail,text);
        j = 0;
    }
    fclose(f);
    return;
}

/* tail insertion */

void add_word(word **head,word **tail, char *text){
    word *ptr, *tmp;
    int found = 0;
    for (ptr = *head; ptr != NULL && found == 0;ptr = ptr->next){
        if (strcmp(ptr->text,text)==0){
            ptr->n++;
            found = 1;
        }
    }
    if (found ==0){
        tmp = new_word();
        tmp->text = strdup(text);
        tmp->n = 1;
        tmp->next = NULL;
        if (*head == NULL){
            *head = tmp;
            *tail = *head;
        }else{
            (*tail)->next = tmp;
            *tail = tmp;
        }
    }
    return;
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

void free_memory(word *hptr){
    while (hptr != NULL){
        word *tmp = hptr;
        hptr = hptr->next;
        free(tmp->text);
        free(tmp);
    }
    return;
}
