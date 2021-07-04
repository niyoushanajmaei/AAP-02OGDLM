#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 31
#define MAX_PROF 21
#define MAX_TITLE 41
#define MAX 100

typedef struct member_s{
    char* name;
    char* job;
    int age;
    struct member_s *next;
}member;

typedef struct job_s{
    char *activity;
    int n;
    struct job_s *next;
}job;

typedef struct film_s{
    char *title;
    int duration,avg_age,n;
    struct job_s *jobs;
    struct film_s *next;
}film;

member *read_members(char *file_name);
film *read_films(char *file_name);
void read_rentals(char *file_name, film *films,member *members);
member *find_member(member *members,char *name);
void find_film(film *films, char *title,member *tmp);
job *add_job(job *jobs,char *title);
void display(char *file_name,film *films);
member *new_member(void);
film *new_film(void);
job *new_job(void);
void free_memory(member *members, film *films);

int main()
{
    char *member_file = "member.txt";
    char *film_file = "film.txt";
    char *rent_file = "rent.txt";
    char *output_file = "output.txt";
    member *members;
    film *films;

    members = read_members(member_file);
    films = read_films(film_file);
    read_rentals(rent_file,films,members);
    display(output_file,films);
    free_memory(members,films);
    return 0;
}

member *read_members(char *file_name){
    member *hptr = NULL;
    char tname[MAX_NAME],tjob[MAX_PROF],line[MAX];
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file %s.",file_name);
        exit(1);
    }

    while (fgets(line,MAX,f)!=NULL){
        member *tmp = new_member();
        sscanf(line,"%s %s %d",tname,tjob,&(tmp->age));
        tmp->name = strdup(tname);
        tmp->job = strdup(tjob);
        tmp->next = hptr;
        hptr = tmp;
    }

    fclose(f);
    return hptr;
}

film *read_films(char *file_name){
    film *hptr = NULL;
    char ttitle[MAX_TITLE],line[MAX];
    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file %s.",file_name);
        exit(1);
    }

    while (fgets(line,MAX,f)!=NULL){
        film *tmp = new_film();
        sscanf(line,"%s %d",ttitle,&(tmp->duration));
        tmp->title = strdup(ttitle);
        tmp->n = 0;
        tmp->avg_age =0;
        tmp->jobs = NULL;
        tmp->next = hptr;
        hptr = tmp;
    }

    fclose(f);
    return hptr;
}

void read_rentals(char *file_name, film *films, member *members){
    char name[MAX_NAME], title[MAX_TITLE], line [MAX];

    FILE *f = fopen(file_name,"r");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }

    while(fgets(line,MAX,f)!=NULL){
        sscanf(line,"%s %s",name,title);
        member *t_member = find_member(members,name);
        find_film(films,title,t_member);
    }

    return;
}

member *find_member(member *members,char *name){
    member *hptr, *tmp;
    int found = 0;
    for (hptr = members;hptr != NULL && found == 0;hptr = hptr->next){
        if (strcmp(name,hptr->name) == 0){
            tmp = hptr;
            found = 1;
        }
    }
    return tmp;
}

void find_film(film *films, char *title, member *tmp){
    film *hptr;
    int found = 0;
    for (hptr = films;hptr != NULL && found == 0;hptr = hptr->next){
        if (strcmp(title,hptr->title) == 0){
            (hptr->n)++;
            hptr->avg_age = (((hptr->avg_age) * ((hptr->n)-1) )+ tmp->age ) / hptr->n;
            hptr->jobs = add_job(hptr->jobs,tmp->job);
            found = 1;
        }
    }
    return;
}

job *add_job(job *jobs,char *title){
    job *ptr1;
    int found = 0;
    for (ptr1 = jobs;ptr1 != NULL && found == 0; ptr1= ptr1->next){
        if (strcmp(ptr1->activity,title)==0){
            (ptr1->n)++;
            found = 1;
        }
    }
    if (found == 0){
        job *tmp = new_job();
        tmp->activity = strdup(title);
        tmp->n = 1;
        tmp->next = jobs;
        jobs = tmp;
    }
    return jobs;
}

void display(char *file_name, film *films){
    film *tmp_film;
    job *tmp_job;
    FILE *f = fopen(file_name,"w");
    if (f==NULL){
        fprintf(stderr,"Error opening file.");
        exit(1);
    }
    for (tmp_film=films;tmp_film !=NULL;tmp_film = tmp_film->next){
        if (tmp_film ->n >0){
            fprintf(f,"%s %d %d %d -> ",tmp_film->title,tmp_film->duration,tmp_film->n,tmp_film->avg_age);
            for (tmp_job = tmp_film->jobs ;tmp_job!=NULL;tmp_job = tmp_job->next){
                fprintf(f,"%s %d ",tmp_job->activity,tmp_job->n);
            }
            fprintf(f,"\n");
        }
    }
    fclose(f);
    return;
}

member *new_member(void){
    member *mem = malloc (sizeof(member));
    if (mem==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    return mem;
}

film *new_film(void){
    film *f = malloc(sizeof(film));
    if (f ==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return f;
}

job *new_job(void){
    job *j = malloc(sizeof(job));
    if (j==NULL){
        fprintf(stderr,"Error allocating memory.");
        exit(1);
    }
    return j;
}

void free_memory(member *members, film *films){
    member *tm, *hm = members;
    film *tf, *hf = films;
    while (hm != NULL){
        tm = hm;
        hm = hm->next;
        free(tm->name);
        free(tm->job);
        free(tm);
    }
    while (hf != NULL){
        tf = hf;
        hf = hf->next;
        free(tf->title);

        job *tj, *hj = tf->jobs;
        while(hj!=NULL){
            tj = hj;
            hj = hj->next;
            free(tj->activity);
            free(tj);
        }

        free(tf);
    }
}
