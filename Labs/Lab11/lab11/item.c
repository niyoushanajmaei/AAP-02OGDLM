#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "item.h"

struct item {
  char *regisNumber;
  char *name;
  int credLoaded;
  int credPassed;
};

Item ITEMread (FILE *f) {
  char regisNumber[MAXST];
  char name[MAXNAME];
  int credLoaded;
  int credPassed;

  if(fscanf (f, "%s %s %d %d", regisNumber, name, &credLoaded, &credPassed)!=4){
    return ITEMsetvoid();
    }

  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp == NULL) {
    return ITEMsetvoid();
  } else {
    tmp->regisNumber = strdup(regisNumber);
    tmp->name = strdup(name);
    tmp->credLoaded = credLoaded;
    tmp->credPassed = credPassed;
  }

  return tmp;
}

void ITEMshow (Item data) {
  fprintf (stdout, "\t registery number = %s name = %s credits loaded = %d credits passed = %d \n", data->regisNumber,data->name, data->credLoaded, data->credPassed);
}

int ITEMcheckvoid(Item data) {
  Key k1, k2 = "";

  k1 = KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return 1;
  else
    return 0;
}

Item ITEMsetvoid() {
  char regisNumber[MAXST] = "";
  char name[MAXNAME] = "";

  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp != NULL) {
    tmp->regisNumber = strdup(regisNumber);
    tmp->name = strdup(name);
    tmp->credLoaded = -1;
    tmp->credPassed = -1;
  }
  return tmp;
}

Key KEYread(FILE *f) {
  char regisNumber[MAXST];
  Key k;

  fscanf(f, "%s", regisNumber);
  k = strdup(regisNumber);
  return k;
}

int  KEYcompare(Key k1, Key k2) {
  return strcmp(k1,k2);
}

Key KEYget(Item data) {
  return data->regisNumber;
}
