#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int mult(int a,int b);
void d2b (int d, int *b);
int catalan (int n, int c[100]);
int countSpaces (char *s);
int isPalindrome (char *s, int l);
void triangle (int n);
void triangle2 (int n,int start);

int main()
{
    char test, tmp[2];
    int a,b,i=0;
    int c[100];
    char *s = malloc(100 * sizeof(char));
    for (int i=0;i<100;i++){
        c[i] = -1;
    }
    fprintf(stdout,"Which function do you want to test?\n");
    fprintf(stdout,"A: multiplication\nB:Decimal to Binary\n");
    fprintf(stdout,"C: First 50 Catalan numbers\nD: Count spaces\n");
    fprintf(stdout,"E: isPalindorme.\nF: triangle of numbers.\n");
    fprintf(stdout,"G: triangle of numbers without iteration\n");
    scanf("%s",tmp);
    test =tmp[0];
    gets(s);
    switch (test){
        case 'A':
            printf("Enter a and b:\n");
            scanf("%d %d",&a,&b);
            printf("result: %d\n",mult(a,b));
            break;
        case 'B':
            printf("Enter decimal number:\n");
            scanf("%d",&a);
            d2b(a,&b);
            printf("Binary format is: %d",b);
            break;
        case 'C':
            for (int i=0;i<20;i++){
                printf("%d \n",catalan(i,c));
            }
            break;
        case 'D':
            printf("Enter you input:\n");
            gets(s);
            fprintf(stdout,"%d ",countSpaces (s));
            break;
        case 'E':
            printf("Enter you input:\n");
            gets(s);
            a=0;
            while (s[i]!='\0'){
                a++;
                i++;
            }
            if (isPalindrome(s,a)==0){
                fprintf(stdout,"Palindrome");
            }else{
                fprintf(stdout,"Not Palindrome");
            }
            break;
        case 'F':
            fprintf(stdout,"Enter n:\n");
            scanf("%d",&a);
            triangle(a);
            break;
        case 'G':
            fprintf(stdout,"Enter n:\n");
            scanf("%d",&a);
            triangle2(a,1);
            break;
        default:
            printf("wrong command");
    }
    return 0;
}

int mult(int a,int b){
    if (b == 1){
        return a;
    }
    return a + mult(a,b-1);
}

void d2b (int d, int *b){
    if (d<2){
        *b = d;
        return;
    }
    d2b(d/2,b);
    *b =  *b * 10 + d%2;
    return;
}

/*
    C_0 = 1     for n=0
    and
    C_{n} = sum_{i=0}^{i=(n-1)} (C_i * C_{n-1-i})     for n>=1
*/
int catalan (int n,int c[100]){
    int sum = 0;
    if(n==0){
        c[0] = 1;
        return 1;
    }
    for (int i=0;i<n;i++){
        if (c[i]==-1){
            c[i] = catalan(i,c);
        }
        if(c[n-1-i]==-1){
            c[n-1-i] = catalan(n-1-i,c);
        }
        sum += c[i] * c[n-1-i];
    }
    return sum;
}

int countSpaces (char *s){
    if (s[0] == '\0'){
        return 0;
    }
    if (isspace(s[0])){
        return 1 + countSpaces(&s[1]);
    }
    return countSpaces(&s[1]);
}

int isPalindrome (char *s, int l){
    int start = 0;
    int end = l-1;
    int length = l;
    if (l == 0 || l==1){
        return 0;
    }
    while (isalnum(s[start])==0){
        start++;
    }
    while (isalnum(s[end])==0){
        end--;
    }
    length = end - start +1;
    if (tolower(s[start]) == tolower(s[end]) && isPalindrome(&s[start+1],length -2)){
        return 0;
    }
    return 1;
}

void triangle (int n){
    if (n <=0){
        return;
    }
    triangle(n-1);
    for(int i=0;i<n;i++){
        fprintf(stdout,"%d ",n);
    }
    fprintf(stdout,"\n");
}

void triangle2 (int n, int i){
    // print n times the value n and then \n, go to the next n
    if (n<=0){
        return;
    }
    if (i>n){
        triangle2(n-1,1);
        fprintf(stdout,"\n");
        return;
    }
    triangle2(n,i+1);
    fprintf(stdout,"%d",n);
    return;
}
