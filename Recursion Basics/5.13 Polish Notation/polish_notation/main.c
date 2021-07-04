#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

float eval(char *s, int *ptr);

int main()
{
    char st[100];
    printf("Enter the string:\n");
    gets(st);
    int c = 0;
    printf("%.2f", eval(st,&c));
    return 0;
}

float eval(char *st, int *ptr){
    char op;
    float res,o1,o2;
    char temp[100];
    int c = *ptr;
    int i;
    if (sscanf(&st[c],"%s%n",temp,&i)==EOF){
        return;
    }
    *ptr += i;
    if (isdigit(temp[0])){
        sscanf(temp,"%f",&res);
        return res;
    }
    op = temp[0];
    o1 = eval(st,ptr);
    o2 = eval(st,ptr);
    switch (op){
    case '+':
        return o1 + o2;
    case '-':
        return o1 - o2;
    case '*':
        return o1 *o2;
    case '/':
        return o1 / o2;
    }
}
