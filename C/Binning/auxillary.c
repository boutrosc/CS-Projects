/***************************************************************  
 Student Name: Charbel Boutros  
 File Name: auxillary.c  ***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/********************************************
 *Function prototypes
 *******************************************/
void input();
void process(char *, int, int, int, int, int, int);

int main() {
    srand(time(NULL));
    int i;
    for (i = 0; i < 3; i++) {
        if (i == 0) printf("Big bins, small items\n");
        else if (i == 1) printf("\nBig bins, variable-sized items\n");
        else printf("\nVariable sized bins, variable-sized items\n");
        input();
    }
    return;
}

/********************************************
 * reads in user input
 *******************************************/
void input() {
    int itemNum, itemMin, itemMax, binNum, binMin, binMax;
    char fname[20];
    printf("Name output file : \n");
    scanf("%s", fname);
    printf("Number of items : \n");
    scanf("%i", &itemNum);
    printf("Min range of item weight : \n");
    scanf("%i", &itemMin);
    printf("Max range of item weight : \n");
    scanf("%i", &itemMax);
    printf("Number of bins : \n");
    scanf("%i", &binNum);
    printf("Min range of bin weight : \n");
    scanf("%i", &binMin);
    printf("Max range of bin weight : \n");
    scanf("%i", &binMax);
    process(fname, itemNum, itemMin, itemMax, binNum, binMin, binMax);
}

/********************************************
 * process' the users request
 * fname is the output file name
 * itemNum is number of items
 * itemMin is minimum weight of items
 * itemMax is maximum weight of items
 * binNum is number of bins
 * binMin is minimum weight of bins
 * binMax is maximum weight of bins
 *******************************************/
void process(char fname[20], int itemNum, int itemMin, int itemMax, int binNum, int binMin, int binMax) {
    int i, gen;
    FILE *outFile = fopen(fname, "w");
    fprintf(outFile, "%i %i %i %i\n", itemNum, binNum, binMin, binMax);
    if (itemMin == itemMax)
        for (i = 0; i < itemNum; i++) fprintf(outFile, "%i\n", itemMin);
    else for (i = 0; i < itemNum; i++) {
            gen = (rand() % (itemMax - itemMin)) + itemMin;
            fprintf(outFile, "%i\n", gen);
        }
}
