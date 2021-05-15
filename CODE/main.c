#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>

#include "HASHoption.h"
#include "ARRBSoption.h"
#include "ARRoption.h"
#include "BSToption.h"
#include "LINKLISToption.h"

#define FALSE 0
#define TRUE 1

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
