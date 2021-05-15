#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#include "BSToption.h"

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
}treenode;

void Tree_inOrder(treenode *n)

{
     if(n==0) return;

     Tree_inOrder(n->left);
     printf("%d\t", n->value);
     Tree_inOrder(n->right);
}

void free_tree (treenode * p)
{
    if(p==NULL) return;

    free_tree(p->right);
    free_tree(p->left);

    free(p);
}

treenode *creatnode(int value)
{
    treenode *result = malloc(sizeof(treenode));
    if(result != NULL){
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return result;
}

bool insertnumber(treenode **rootptr, int value)
{
    treenode *root = *rootptr;
    if(root == NULL) {
        //tree empty
        (*rootptr) = creatnode(value);
        return true;
    }

    if(value == root->value) return false;
    if(value < root->value) return insertnumber(&(root->left), value);
    else return insertnumber(&(root->right), value);

}

bool findnumber(treenode *root, int value)
{
    if(root == NULL) return false;
    if(value == root->value) return true;
    if(value < root->value) return findnumber(root->left, value);
    else return findnumber(root->right, value);
}

void BSToption(FILE *fp, int *number, int ReadNum, int QueryNum)
{
    printf("BST:\n");
    struct  timeval start;  //timeval = time value
    struct  timeval end;
    unsigned  long diff;


    gettimeofday(&start, NULL);

    treenode *root = NULL;
    char line[4096];
    int idx = 0;
    int count = 0;
    while(fgets(line,4096,fp) != NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1] == '\n') line[len-1] = '\0';
        number[idx++] = atoi(line);
        insertnumber(&root, number[idx-1]);
        count++;
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);


    gettimeofday(&start, NULL);

    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        if(findnumber(root,target));
    }

    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);


    //Tree_inOrder(root);
    //printf("\n");
    free_tree(root);
}
