#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#include "ARRoption.h"

int findnum(int *number, int idx, int target)
{
    for(int j=0;j<idx;j++)  if(number[j] == target) return 1;
    return 0;
}

void ARRprint(int *number,int idx){
    for(int i=0;i<idx;i++) printf("%d\t",number[i]);
    printf("\n");
}

void ARRoption(FILE *fp, int *number, int ReadNum, int QueryNum)
{
    printf("ARR:\n");
    struct  timeval start;  //timeval = time value
    struct  timeval end;
    unsigned  long diff;


    gettimeofday(&start, NULL);

    char line[4096];
    int idx = 0;
    int count = 0;
    while(fgets(line,4096,fp) != NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1] == '\n') line[len-1] = '\0';
        number[idx++] = atoi(line);
        count++;
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);


    gettimeofday(&start, NULL);

    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        if(findnum(number,idx,target) == 1);
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);


    //ARRprint(number,idx);
}
