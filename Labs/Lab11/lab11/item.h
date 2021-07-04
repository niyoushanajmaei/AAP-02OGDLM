#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#include <stdio.h>
#define MAXST 10
#define MAXNAME 101

typedef struct item* Item;
typedef char *Key;

Item ITEMread(FILE *f);
void ITEMshow(Item data);
int ITEMcheckvoid(Item data);
Item ITEMsetvoid();
Key KEYread(FILE *f);
int KEYcompare(Key k1, Key k2);
Key KEYget(Item data);
#endif

