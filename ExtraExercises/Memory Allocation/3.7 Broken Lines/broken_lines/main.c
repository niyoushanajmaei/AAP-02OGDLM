#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int p1[2];
    int p2[2];
    int right;
    int left;
}segment;

segment *read_input(char *name,int *ptr);
void connect(segment *segments,int n);
void check (segment *segments, int n);

int main()
{
    int n;
    char *name = "file.txt";
    segment* segments = read_input(name, &n);
    connect(segments,n);
    check(segments,n);
    free(segments);
    return 0;
}

segment *read_input(char *name,int *ptr){
    FILE *f = fopen(name,"r");
    if (f ==NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d",ptr);
    segment *segments = malloc (*ptr * sizeof(segment));
    for (int i=0;i<*ptr;i++){
        fscanf(f,"%d %d %d %d",&segments[i].p1[0],&segments[i].p1[1],&segments[i].p2[0],&segments[i].p2[1]);
        segments[i].left = 0;
        segments[i].right = 0;
    }
    fclose(f);
    return segments;
}

void connect(segment *segments,int n){
    for (int i=0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if (segments[i].p1[0]==segments[j].p1[0] && segments[i].p1[1]==segments[j].p1[1]){
                segments[i].left++;
                segments[j].left++;
            }
            if (segments[i].p2[0]==segments[j].p2[0] && segments[i].p2[1]==segments[j].p2[1]){
                segments[i].right++;
                segments[j].right++;
            }
            if (segments[i].p1[0]==segments[j].p2[0] && segments[i].p1[1]==segments[j].p2[1]){
                segments[i].left++;
                segments[j].right++;
            }
            if (segments[i].p2[0]==segments[j].p1[0] && segments[i].p2[1]==segments[j].p1[1]){
                segments[i].right++;
                segments[j].left++;
            }
        }
    }
}

void check (segment *segments ,int n){
    int dis =0;
    int mult =0;
    for (int i=0;i<n;i++){
        printf("segment: %d %d %d %d, left: ",segments[i].p1[0],segments[i].p1[1],segments[i].p2[0],segments[i].p2[1]);
        if (segments[i].left == 0){
            dis++;
            printf("disconnected");
        }
        if (segments[i].left > 1){
            mult++;
            printf("Multiple connections");
        }
        if (segments[i].left ==1){
            printf("Ok");
        }
        printf(" ,right: ");
        if (segments[i].right == 0){
            dis++;
            printf("disconnected");
        }
        if (segments[i].right > 1){
            mult++;
            printf("Multiple connections");
        }
        if (segments[i].right ==1){
            printf("Ok");
        }
        printf("\n");
    }
    if(dis>2 && mult == 0){
        printf("Broken line with disconnected segments.\n");
    }else if (dis == 2 && mult == 0){
        printf("One Broken line");
    }else if (mult >2){
        printf("multiple branches.\n");
    }
}
