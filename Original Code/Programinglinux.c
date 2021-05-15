#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#define FALSE 0
#define TRUE 1


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
//-------------------------------
    init_hash_table();
    char line[4096];
    int count = 0;
    while(fgets(line,4096,fp)!=NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1]== '\n') line[len-1] = '\0';
        hash_table_insert(atoi(line));
        count++;
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
//-------------------------------


    gettimeofday(&start, NULL);
//-------------------------------
    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        //printf("target is %d\n",target);
        person *tmp = NULL;
        if((tmp = hash_table_lookup(target)) != NULL); //printf("I find it!!\n");
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);
//-------------------------------
    //print_table();
}


/*------------------------------------------------------------------*/


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
//--------------------------------
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
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
//-------------------------------


    gettimeofday(&start, NULL);
//-------------------------------
    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        //printf("target is %d\n",target);
        if(findnumber(root,target)); //printf("I find it!!\n");
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);
//-------------------------------


    //Tree_inOrder(root);
    //printf("\n");
    free_tree(root);
}


/*------------------------------------------------------------------*/


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
//-------------------------------
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

//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
//-------------------------------


    gettimeofday(&start, NULL);
//-------------------------------
    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        //printf("target is %d\n",target);
        if(BinarySearch(number,idx,target) == 1); //printf("I find it!!\n");
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);
//-------------------------------

    //ARRBSprint(number,idx);
}


/*------------------------------------------------------------------*/


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
//-------------------------------
    char line[4096];
    node *head = NULL;
    int count = 0;
    while(fgets(line,4096,fp)!=NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1]== '\n') line[len-1] = '\0';
        addnode(&head,atoi(line));
        count++;
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
//-------------------------------


    gettimeofday(&start, NULL);
//-------------------------------
    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        //printf("target is %d\n",target);
        if(findlist(head,target) == 1); //printf("I find it!!\n");
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);
//-------------------------------

    //printlist(head);
    freelist(head);
}



/*--------------------------------------------------------------------------*/

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
//-------------------------------
    char line[4096];
    int idx = 0;
    int count = 0;
    while(fgets(line,4096,fp) != NULL && count < ReadNum){
        int len = strlen(line);
        if(line[len-1] == '\n') line[len-1] = '\0';
        number[idx++] = atoi(line);
        count++;
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
//-------------------------------


    gettimeofday(&start, NULL);
//-------------------------------
    for(int i=0;i<QueryNum;i++){
        int target = rand() % 1000000 + 1;
        //printf("target is %d\n",target);
        if(findnum(number,idx,target) == 1); //printf("I find it!!\n");
    }
//-------------------------------
    gettimeofday(&end, NULL);
//-------------------------------
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n", diff / 1000000.0);
//-------------------------------

    //ARRprint(number,idx);
}






int main(int argc,char **argv) {

    int ARR = FALSE;
    int LINKLIST = FALSE;
    int ARRBS = FALSE;
    int BST = FALSE;
    int HASH = FALSE;

    int ReadNum = 1, QueryNum = 1;
    for(int i=1;i<argc;i++){
        if(argv[i][0] == '-') {
            if(argv[i][1] == 'd') {
                int cmdnum = 0;
                if(argv[i+1][0] == '1' && argv[i+1][1] == 'e' && argv[i+1][3] == '\0') cmdnum = (argv[i+1][2] - '0');
                for(int i=0;i<cmdnum;i++) ReadNum *= 10;
                i++;
                continue;
            }
            if(argv[i][1] == 'q') {
                int cmdnum = 0;
                if(argv[i+1][0] == '1' && argv[i+1][1] == 'e' && argv[i+1][3] == '\0') cmdnum = (argv[i+1][2] - '0');
                for(int i=0;i<cmdnum;i++) QueryNum *= 10;
                i++;
                continue;
            }
            if(argv[i][1] == 'a' && argv[i][2] == 'r' && argv[i][3] == 'r' && argv[i][4] == '\0') {
                ARR = TRUE;
                continue;
            }
            if(argv[i][1] == 'l' && argv[i][2] == 'l' && argv[i][3] == '\0') {
                LINKLIST = TRUE;
                continue;
            }
            if(argv[i][1] == 'b' && argv[i][2] == 's' && argv[i][3] == '\0') {
                ARRBS = TRUE;
                continue;
            }
            if(argv[i][1] == 'b' && argv[i][2] == 's' && argv[i][3] == 't' && argv[i][4] == '\0') {
                BST = TRUE;
                continue;
            }
            if(argv[i][1] == 'h' && argv[i][2] == 'a' && argv[i][3] == 's' && argv[i][4] == 'h' && argv[i][5] == '\0') {
                HASH = TRUE;
                continue;
            }
            fprintf(stderr,"nrecognized Arguments\n");
            exit(1);
        }
        else {
            fprintf(stderr,"nrecognized Arguments\n");
            exit(1);
        }
    }

    printf("ReadNum = %d, QueryNum = %d\n",ReadNum,QueryNum);

    int *number = malloc(sizeof(int) * 1000000);
    FILE *fp1 = fopen("dataset5.txt","r");
    FILE *fp2 = fopen("dataset5.txt","r");
    FILE *fp3 = fopen("dataset5.txt","r");
    FILE *fp4 = fopen("dataset5.txt","r");
    FILE *fp5 = fopen("dataset5.txt","r");

    if(fp1 == NULL) {
        printf("read error\n");
        return 0;
    }


    if(ARR) {ARRoption(fp1,number,ReadNum,QueryNum);printf("\n");}

    if(LINKLIST) {LINKLISToption(fp2,number,ReadNum,QueryNum);printf("\n");}

    if(ARRBS) {ARRBSoption(fp3,number,ReadNum,QueryNum);printf("\n");}

    if(BST) {BSToption(fp4,number,ReadNum,QueryNum);printf("\n");}

    if(HASH) {HASHoption(fp5,number,ReadNum,QueryNum);printf("\n");}


    free(number);
    fclose(fp1);fclose(fp2);fclose(fp3);fclose(fp4);fclose(fp5);

    return 0;
}
