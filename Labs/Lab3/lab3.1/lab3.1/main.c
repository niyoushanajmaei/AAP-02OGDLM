#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_S 20
#define MAX_L 100

int main()
{
    char words [100][MAX_S+1];
    char temps[MAX_S+2];
    char templ[MAX_L+2];
    int c =0;
    int i,j,k,flag;
    FILE *f1 = fopen("file1.txt","r");
    FILE *f2 = fopen("file2.txt","r");
    if (f1 == NULL || f2 == NULL){
        printf("error opening files.\n");
        exit(1);
    }
    while(fgets(temps,MAX_S+2,f2)!= NULL){
        sscanf(temps,"%s",words[c]);
        c++;
    }
    int count[c];
    for(i=0;i<c;i++){
        count[i]=0;
    }
    while(fgets(templ,MAX_L+2,f1)!=NULL){
        for(i=0;i<c;i++){
            j=0;
            while(templ[j]!= '\0'){
                if (tolower(words[i][0])==tolower(templ[j])){
                    flag = 1;
                }
                for(k=1;k<strlen(words[i]);k++){
                    if(tolower(templ[j+k])!=tolower(words[i][k])){
                        flag = 0;
                    }
                }
                if (flag ==1 && !isalpha(templ[j+k])){
                    count[i]++;
                }
                j++;
            }
        }
    }
    for (i=0;i<c;i++){
        printf("%s - %d occurance(s)\n",words[i],count[i]);
    }
    fclose(f1);
    fclose(f2);

    return 0;
}
