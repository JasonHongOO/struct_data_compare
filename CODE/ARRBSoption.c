#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#include "ARRBSoption.h"

int partition(int *num,int left,int right)
{
    int i=left;
    for(int j=left;j<right;j++) {   //把比最右邊小的數從最左邊開始一個一個排
        if(num[j]<=num[right]) {
            int t = num[i];
            num[i] = num[j];
            num[j] = t;

            i++;
        }
    }

    int t = num[i];                    //互換後，剛好切一半，左邊都是比num[right}小的，右邊都是比num[right}大的
    num[i] = num[right];
    num[right] = t;

    return i;
}

void quicksort(int *num,int left,int right)
{
    if(left<right) {                                              //一直不斷切，切到最後，一個區塊只有3個數或以下時，就會排序完成
        int q = partition(num ,left ,right);                      //切兩半
        quicksort(num,left,q-1);                                  //左半部不斷切
        quicksort(num,q+1,right);                                 //右半部不斷切
    }
}

int BinarySearch(int *n, int idx, int target)
{
    int high = idx-1;
    int low = 0;
    if(n[high] == target || n[low] == target) return 1;
    while(low<high) {
        int mid =(high+low)/2;

        if(n[mid]>target)           high = mid;
        else if(n[mid]<target)     low = mid;
        else if(n[mid] == target)  return 1;
        if((high-low)<=1)           return 0;
    }
}

void ARRBSprint(int *number,int idx){
    for(int i=0;i<idx;i++) printf("%d\t",number[i]);
    printf("\n");
}

void ARRBSoption(FILE *fp, int *number, int ReadNum, int QueryNum)
{
    printf("ARRBS:\n");
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

    quicksort(number,0,idx-1);


    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);


    gettimeofday(&start, NULL);

    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        if(BinarySearch(number,idx,target) == 1);
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);


    //ARRBSprint(number,idx);
}
