#include <stdio.h>
#include <stdlib.h>

int main()
{
    char st[10] = {"something"};
    print(st);
    return 0;
}

void print(char *s){
    if (s[0] == '\0'){
        return;
    }
    print(&s[1]);
    printf("%c",s[0]);
    return;
}
