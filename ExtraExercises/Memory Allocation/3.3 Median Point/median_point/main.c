#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Point{
    float x;
    float y;
    float z;
    float dist;
} point;

int main()
{
    int n, i = 0,j;
    float dist;
    point *points;
    float tx,ty,tz;
    int min=0;
    char temp[4];
    FILE *f = fopen("file.txt","r");
    if (f == NULL){
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    fscanf(f,"%d",&n);
    points = (point *)malloc(n*sizeof(point));
    if (points == NULL){
        fprintf(stderr,"Error allocating memory\n");
        exit(1);
    }
    while (fscanf(f,"%s %f %f %f",temp,&tx,&ty,&tz)==4){
        points[i].x = tx;
        points[i].y = ty;
        points[i].z = tz;
        i++;
    }

    for(i=0;i<n;i++){
        points[i].dist = 0;
        for (j=0;j<n ;j++){
            points[i].dist += sqrt(pow(points[i].x-points[j].x,2) + pow(points[i].y-points[j].y,2) + pow(points[i].z-points[j].z,2));
        }
        if (points[i].dist < points[min].dist){
            min = i;
        }
    }
    fprintf(stdout,"median is: (%.2f,%.2f,%.2f)",points[min].x,points[min].y,points[min].z);
    free(points);
    fclose(f);
    return 0;
}
