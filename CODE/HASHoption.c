#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#include "HASHoption.h"

#define MAX_NAME    256
#define TABLE_SIZE  10


typedef struct person
{
    int num;
    struct person *next;
}person;

person *hash_table[TABLE_SIZE];

unsigned int hash(int num)
{
    unsigned int hash_value = 0;
    hash_value = num % TABLE_SIZE;
    return hash_value;
}

void init_hash_table()
{
    for(int i=0;i<TABLE_SIZE;i++){
        hash_table[i] = NULL;
    }
    //table is empty
}

void print_table()
{
    printf("start\n");
    for(int i=0;i<TABLE_SIZE;i++){
        if(hash_table[i] == NULL) {
            printf("\t%d\t---\n",i);
        } else {
            printf("\t%d\t",i);
            person *tmp = hash_table[i];
            while(tmp != NULL){
                printf("(%d) - ", tmp->num);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("end\n");
}

void hash_table_insert(int num)
{
    person *newnode = (person *)malloc(sizeof(person));
    newnode->num = num;

    int index = hash(num);
    newnode->next = hash_table[index];
    hash_table[index] = newnode;
}

person *hash_table_lookup(int num)
{
    int index = hash(num);
    person *tmp = hash_table[index];
    while(tmp != NULL && tmp->num != num ){
        tmp = tmp->next;
    }
    return tmp;
}

void HASHoption(FILE *fp, int *number, int ReadNum, int QueryNum)
{
    printf("HASH:\n");
    struct  timeval start;  //timeval = time value
    struct  timeval end;
    unsigned  long diff;


    gettimeofday(&start, NULL);

    init_hash_table();
    char line[4096];
    int count = 0;
    while(fgets(line,4096,fp)!=NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1]== '\n') line[len-1] = '\0';
        hash_table_insert(atoi(line));
        count++;
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);


    gettimeofday(&start, NULL);

    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        //printf("target is %d\n",target);
        person *tmp = NULL;
        if((tmp = hash_table_lookup(target)) != NULL); //printf("I find it!!\n");
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);


    //print_table();
}
