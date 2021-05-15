#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#include "LINKLISToption.h"

typedef struct Node
{
    int cnt;
    struct Node *next;
}node;

void freelist(node *p)
{
    node *temp;
    while(p) {
        temp = p;
        p = p->next;
        free(temp);
    }
}

void printlist(node *p){
    while(p) {
        printf("%d\t",p->cnt);
        p = p->next;
    }
    printf("\n");
}

void addnode(node **start, int num)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->cnt = num;
    newnode->next = NULL;

    if(*start == NULL) {
        *start = newnode;
    }
    else {
        node *cur = *start;
        while(cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newnode;
    }
}

int findlist(node *p,int num)
{
    while(p) {
        if(p->cnt == num) return 1;
        p = p->next;
    }
    return 0;
}

void LINKLISToption(FILE *fp, int *number, int ReadNum, int QueryNum)
{
    printf("LINKLIST:\n");
    struct  timeval start;  //timeval = time value
    struct  timeval end;
    unsigned  long diff;


    gettimeofday(&start, NULL);

    char line[4096];
    node *head = NULL;
    int count = 0;
    while(fgets(line,4096,fp)!=NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1]== '\n') line[len-1] = '\0';
        addnode(&head,atoi(line));
        count++;
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);


    gettimeofday(&start, NULL);

    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        if(findlist(head,target) == 1);
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);


    //printlist(head);
    freelist(head);
}
