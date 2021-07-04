#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 31
#define MAXL 200
#define CODEL 7
#define DATEL 11
#define PROGL 6

typedef struct elem_s {
  char *name;
  char *date;
  char *course;
  int year;
  char *code;
  struct elem_s *leftN;
  struct elem_s *rightN;
  struct elem_s *leftS;
  struct elem_s *rightS;
} elem_t;

void readTree(FILE *, elem_t **, elem_t **);
elem_t *searchS (elem_t *, char *);
elem_t *searchN (elem_t *, char *);
elem_t *insertN(elem_t *, elem_t*);
elem_t *insertS(elem_t *,elem_t*);
void writeTree(FILE *, elem_t *);
void freeTree(elem_t *);
elem_t *myAlloc (void);
elem_t *new_data();
elem_t *readData (char *buffer);
void writeData (FILE *, elem_t *);

int main(){
    FILE *f;
    elem_t *treeS = NULL;
    elem_t *treeN = NULL;
    char name[2*MAXS+1];
    int run = 1;
    char cmd [MAXS], tmp1[MAXS],tmp2[MAXS];
    while (run){
        fprintf(stdout,"1. Enter load to load file.\n2. searchS to search by name\n");
        fprintf(stdout,"3. searchN to search by student number.\n4. save to save data in a file\n");
        fprintf(stdout,"4. quit to exit.\n");
        scanf("%s",cmd);
        gets(tmp1);
        if (strcmp(cmd,"load")==0){
            fprintf(stdout,"Enter the file name:\n");
            scanf("%s",tmp1);
            f= fopen(tmp1,"r");
            if (f==NULL){
                fprintf(stderr,"Error opening file.\n");
                exit(1);
            }
            readTree(f,&treeS,&treeN);
            fclose(f);
        }else if (strcmp(cmd,"searchS")==0){
            fprintf(stdout,"Enter surname:\n");
            scanf("%s",tmp1);
            fprintf(stdout,"Enter first name:\n");
            scanf("%s",tmp2);
            sprintf(name,"%s %s",tmp1,tmp2);
            writeData(stdout,searchS(treeS,name));
        }else if (strcmp(cmd,"searchN")==0){
            fprintf(stdout,"Enter student number");
            scanf("%s",tmp1);
            writeData(stdout,searchN(treeN,tmp1));
        }else if (strcmp(cmd,"save")==0){
            fprintf(stdout,"Enter the file name:\n");
            scanf("%s",tmp1);
            f= fopen(tmp1,"w");
            if (f==NULL){
                fprintf(stderr,"Error opening file.\n");
                exit(1);
            }
            writeTree(f,treeS);
            fclose(f);
        }else if (strcmp(cmd,"quit")==0){
            run = 0;
        }else{
            fprintf(stderr,"wrong command.\n");
        }
    }
    freeTree(treeS);
    return 0;
}

elem_t *searchS (elem_t *rp, char *name){
    if (rp==NULL || strcmp(name,rp->name)==0)
        return (rp);
    if (strcmp(name,rp->name) < 0)
        return (searchS (rp->leftS, name));
    return (searchS (rp->rightS, name));
}

elem_t *searchN (elem_t *rp, char *code){
    if (rp==NULL || strcmp(code,rp->code)==0)
        return (rp);
    if (strcmp(code,rp->code) < 0)
        return (searchN (rp->leftN, code));
    return (searchN (rp->rightN, code));
}

elem_t *insertN (elem_t *rp,elem_t *data){

  /* Empty Tree: Found Position */
  if (rp == NULL)
    return (data);

  /* Duplicated Element */
  if (strcmp(data->code, rp->code) == 0) {
    return (rp);
  }

  if (strcmp(data->code, rp->code) < 0) {
    /* Insert on the left */
    rp->leftN = insertN (rp->leftN, data);
  } else {
    /* Insert on the right */
    rp->rightN = insertN (rp->rightN, data);
  }
  return (rp);
}

elem_t *insertS (elem_t *rp,elem_t *data){

    if (rp == NULL)
        return (data);
  /* Duplicated Element */
  if (strcmp(data->name, rp->name) == 0) {
    return (rp);
  }

  if (strcmp(data->name, rp->name) < 0) {
    /* Insert on the left */
    rp->leftS = insertS (rp->leftS, data);
  } else {
    /* Insert on the right */
    rp->rightS = insertS (rp->rightS, data);
  }
  return (rp);
}

void readTree (FILE *f, elem_t **treePtrS, elem_t **treePtrN){
    elem_t *rpS = *treePtrS;
    elem_t *rpN = *treePtrN;
    elem_t *d;
    char buffer[MAXL];
    while(fgets(buffer,MAXL,f)!=NULL){
        d = new_data();
        d = readData(buffer);
        rpN = insertN(rpN,d);
        rpS = insertS(rpS,d);
    }
    *treePtrS = rpS;
    *treePtrN = rpN;
    return;
}

elem_t *myAlloc (void){
  elem_t *p;

  p = malloc(sizeof(elem_t));
  if (p == NULL) {
    printf ("Allocation Error.\n");
    exit (1);
  }
  return (p);
}

void freeTree (elem_t *rp){
  if (rp == NULL) {
    return;
  }

  freeTree (rp->leftN);
  freeTree (rp->rightN);
  free (rp);

  return;
}

void writeTree (FILE *fp,elem_t *rp){
  if (rp == NULL) {
    return;
  }
  writeTree (fp, rp->leftS);
  writeData(fp, rp);
  writeTree (fp, rp->rightS);
  return;
}

elem_t *new_data(){
    elem_t *data = malloc(sizeof(elem_t));
    if (data==NULL){
        fprintf(stderr,"Error allocating memory");
        exit(1);
    }
    return data;
}

elem_t *readData (char *buffer){
    elem_t *data = new_data();
    char name[2*MAXS+1], fname[MAXS],sname[MAXS], code[CODEL], date[DATEL], prog[PROGL];
    sscanf(buffer,"%s %s %s %s %s %d",code,sname,fname,date,prog,&(data->year));
    data->code = strdup(code);
    data->date = strdup(date);
    data->course = strdup(prog);
    sprintf(name,"%s %s",sname,fname);
    data->name = strdup(name);
    data->leftN = data->leftS = data->rightS = data->rightN = NULL;
    return (data);
}

void writeData (FILE *fp, elem_t *data){
    fprintf(fp, "%s %s %s %s %d\n",data->code,data->name,data->date,data->course,data->year);
    return;
}
