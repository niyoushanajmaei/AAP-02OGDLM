#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 31
int main(int argc, char *argv[])
{
    char s1[MAX_LEN],s2[MAX_LEN];
    int c['z'-'a'];
    int anagram = 1;

    if(argc != 3){
        printf("Wrong number of arguments.");
        return 1;
    }
    for(int i=0;i<'z'-'a';i++){
        c[i]=0;
    }
    strcpy(s1,argv[1]);
    strcpy(s2,argv[2]);
    for (int i = 0; i <strlen(s1);i++){
        c[tolower(s1[i])-'a']++;
    }
    for (int i = 0; i <strlen(s2);i++){
        c[tolower(s2[i])-'a']--;
    }
    for (int i=0;i<'z'-'a';i++){
        if(c[i]!=0){
            anagram = 0;
        }
    }
    if(anagram==1){
        printf("The two strings are anagrams.");
    }else{
        printf("The two strings aren't anagrams.");
    }

    return 0;
}
