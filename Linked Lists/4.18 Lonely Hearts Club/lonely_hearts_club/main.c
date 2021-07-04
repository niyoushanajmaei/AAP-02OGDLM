#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 101

typedef struct trait_s{
    char *id;
    struct trait_s *next;
}trait;

typedef struct member_s{
    char *name;
    char sex;
    trait *features;
    struct member_s *next;
}member;

member *load(char *file_name);
trait *read(char *sex_ptr);
void process(member *club,char sex,trait *features);
int check(trait *hptr1,trait *hptr2);
void destroy(trait *hptr);
void quit(member *hptr);
member *new_member(void);
trait *new_trait(void);

int main()
{
    member *club =NULL;
    trait *features =NULL;
    char sex;
    char *file_name;
    file_name = "input.txt";
    club = load(file_name);
    do {
        features = read(&sex);
        if(features != NULL){
            process(club,sex,features);
            destroy(features);
        }
    }while (sex != 'T');
    quit(club);
    return 0;
}

member *load(char *file_name){
    char firstname[MAX], surname[MAX],trait_k[MAX],trait_v[MAX],line[MAX], sex[MAX],name[MAX],trait_kv[MAX];
    member *tmember;
    trait *tmp;
    member *hptr = NULL;
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    while(fgets(line,MAX,f)!=NULL){
        if(line[0]=='#'){
            tmember = new_member();
            sscanf(&line[1],"%s %s %s",firstname,surname,sex);
            sprintf(name,"%s %s",firstname,surname);
            tmember->sex = sex[0];
            tmember->name = strdup(name);
            tmember->features =NULL;
            tmember->next = hptr;
            hptr = tmember;
        }else{
            tmp = new_trait();
            sscanf(line,"%s %s",trait_k,trait_v);
            sprintf(trait_kv,"%s %s",trait_k,trait_v);
            tmp->id = strdup(trait_kv);
            tmp->next = hptr->features;
            hptr->features = tmp;
        }
    }
    fclose(f);
    return hptr;
}

trait *read(char *sex_ptr){
    trait *hptr = NULL;
    trait *feature;
    char line[MAX], trait_k[MAX], trait_v[MAX], trait_kv[MAX];
    char *ptr;
    int n;

    fprintf(stdout,"Input query: \n");
    fgets(line,MAX,stdin);
    sscanf(line,"%c",sex_ptr);
    if (*sex_ptr == 'T'){
        return NULL;
    }
    ptr = &line[1];
    while (sscanf(ptr,"%s %s%n",trait_k,trait_v,&n)!=EOF){
        sprintf(trait_kv,"%s %s",trait_k,trait_v);
        ptr += n;
        feature = new_trait();
        feature->id = strdup(trait_kv);
        feature->next = hptr;
        hptr = feature;
    }
    return hptr;
}


void process(member *club,char sex,trait *features){
    member *tmp;
    member *mate = NULL;
    int max=0,similarity;

    for (tmp=club;tmp!=NULL;tmp=tmp->next){
        if (tmp->sex != sex){
            similarity = check(tmp->features,features);
            if (mate ==NULL || similarity > max){
                mate = tmp;
                max = similarity;
            }
        }
    }
    fprintf(stdout,"The best match is: %s (similarity: %d) \n",mate->name,max);
    return;
}

int check(trait *hptr1,trait *hptr2){
    trait *tmp1, *tmp2;
    int sim = 0,found;
    for (tmp1=hptr1;tmp1!=NULL;tmp1=tmp1->next){
        found = 0;
        for (tmp2=hptr2;tmp2!=NULL && found ==0;tmp2=tmp2->next){
            if (strcmp(tmp1->id, tmp2->id)==0){
                sim++;
                found = 1;
            }
        }
    }
    return sim;
}

void destroy(trait *hptr){
    trait *tmp;
    while(hptr!=NULL){
        tmp = hptr;
        hptr = hptr->next;
        free(tmp->id);
        free(tmp);
    }
    return;
}

void quit(member *hptr){
    member *tmp;
    while (hptr!=NULL){
        tmp = hptr;
        hptr = hptr->next;
        destroy(tmp->features);
        free(tmp->name);
        free(tmp);
    }
}

member *new_member(void){
    member *tmember = malloc(sizeof(member));
    if (tmember==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return tmember;
}

trait *new_trait(void){
    trait *tmp = malloc(sizeof(trait));
    if (tmp==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return tmp;
}
