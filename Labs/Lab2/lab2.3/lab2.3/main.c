#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILE 100
#define MAX_ST 20

int min(int a,int b);

int main()
{
    FILE *f1, *f2;
    char temp[MAX_FILE+2];
    //char st1[MAX_ST+1], st2[MAX_ST+1];

    f1 = fopen("file1.txt","r");
    f2 = fopen("file2.txt","w");
    char st1[MAX_ST+1] = "test";
    char st2[MAX_ST+1] = "check";

    while (fgets(temp,MAX_FILE+2,f1)!=NULL){
        int start = 0;
        for(int i=0;i<strlen(temp)-strlen(st1);i++){
            int flag = 1;
            for (int j=0;flag == 1 && j <strlen(st1);j++){
                if (temp[i+j]!=st1[j]){
                    flag = 0;
                }
            }
            if(flag == 1 ){
                for (int j=start;j<i;j++){
                    fputc(temp[j],f2);
                }
                for (int j=0;j<strlen(st2);j++){
                    fputc(st2[j],f2);
                }
                i += strlen(st2) -2;
                start = i+1;
            }
        }
        for (int j=start;j<strlen(temp);j++){
            fputc(temp[j],f2);
        }
    }

    fclose(f1);
    fclose(f2);
    return 0;
}

int min(int a,int b){
    if(a<b){
        return a;
    }else{
        return b;
    }
}
