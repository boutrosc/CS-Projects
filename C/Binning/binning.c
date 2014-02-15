/***************************************************************  
 Student Name: Charbel Boutros  
 File Name: binning.c  ***************************************************************/


#include <stdio.h>
#include <stdlib.h>
/********************************************
 *Struct Declarations
 *******************************************/
typedef struct HeuristicS {
    struct BBSIS *bbsi;
    struct BBVIS *bbvi;
    struct VBVIS *vbvi;
} *HeuristicP;

typedef struct BBSIS {
    struct FirstFitS *ff;
    struct BestFitS *bf;
    struct NextFitS *nf;
    int itemNum;
    int binNum;
    int binMin;
    int binMax;
    int *items;
} *BBSIP;

typedef struct BBVIS {
    struct FirstFitS *ff;
    struct BestFitS *bf;
    struct NextFitS *nf;
    int itemNum;
    int binNum;
    int binMin;
    int binMax;
    int *items;
} *BBVIP;

typedef struct VBVIS {
    struct FirstFitS *ff;
    struct BestFitS *bf;
    struct NextFitS *nf;
    int itemNum;
    int binNum;
    int binMin;
    int binMax;
    int *items;
} *VBVIP;

typedef struct FirstFitS {
    int binsUsed;
    struct BinS *binRoot;
    struct ErrorS *errorRoot;
    struct BinS *current;

} *FirstFitP;

typedef struct BestFitS {
    int binsUsed;
    struct BinS *binRoot;
    struct ErrorS *errorRoot;
    struct BinS *current;

} *BestFitP;

typedef struct NextFitS {
    int binsUsed;
    struct BinS *binRoot;
    struct ErrorS *errorRoot;
    struct BinS *current;
} *NextFitP;

typedef struct BinS {
    int capacity;
    int size;
    struct BinS *right;
    struct ItemS *down;
} *BinP;

typedef struct ItemS {
    int size;
    struct ItemS *down;
} *ItemP;

typedef struct ErrorS {
    int size;
    int reason;
    struct ErrorS *next;
} *ErrorP;

/********************************************
 *Function prototypes
 *******************************************/
void online(HeuristicP);
void offline(HeuristicP, HeuristicP);
void intialize(HeuristicP, HeuristicP);
void readIn(HeuristicP, HeuristicP, char**);
void createBin(FirstFitP, BestFitP, NextFitP, int, int, int);
BinP intializeBin(int, int);
void matchBins(HeuristicP off, HeuristicP on);
void firstFitOn(int, int*, BinP, ErrorP, BinP);
void nextFitOn(int, int*, BinP, ErrorP, BinP);
void bestFitOn(int, int, int*, BinP, ErrorP, BinP);
void insertBin(BinP, int);
void mergeSort(int *sort, int lower, int upper);
void merge(int *, int, int, int);
int countBins(BinP, BinP);
void errorReport(ErrorP, int, int);
void summary(HeuristicP, HeuristicP);
void logFile(HeuristicP, HeuristicP);
void outputLog(FILE*, BinP, ErrorP, int, int);

int main(int argc, char** argv) {
    srand(time(NULL));
    if (argc != 4) {
        printf("Missing arguments!\n");
        exit(1);
    }
    HeuristicP on = malloc(sizeof (struct HeuristicS));
    HeuristicP off = malloc(sizeof (struct HeuristicS));
    intialize(on, off);
    readIn(on, off, argv);
    online(on);
    offline(off, on);
    summary(on, off);
    return 0;
}

/********************************************
 * Processes the online section
 * 'on' contains the online information
 *******************************************/
void online(HeuristicP on) {
    createBin(on->bbsi->ff, on->bbsi->bf, on->bbsi->nf, on->bbsi->binMin, on->bbsi->binMax, on->bbsi->binNum);
    createBin(on->bbvi->ff, on->bbvi->bf, on->bbvi->nf, on->bbvi->binMin, on->bbvi->binMax, on->bbvi->binNum);
    createBin(on->vbvi->ff, on->vbvi->bf, on->vbvi->nf, on->vbvi->binMin, on->vbvi->binMax, on->vbvi->binNum);
    firstFitOn(on->bbsi->itemNum, on->bbsi->items, on->bbsi->ff->binRoot, on->bbsi->ff->errorRoot, on->bbsi->ff->current);
    firstFitOn(on->bbvi->itemNum, on->bbvi->items, on->bbvi->ff->binRoot, on->bbvi->ff->errorRoot, on->bbvi->ff->current);
    firstFitOn(on->vbvi->itemNum, on->vbvi->items, on->vbvi->ff->binRoot, on->vbvi->ff->errorRoot, on->vbvi->ff->current);
    nextFitOn(on->bbsi->itemNum, on->bbsi->items, on->bbsi->nf->binRoot, on->bbsi->nf->errorRoot, on->bbsi->nf->current);
    nextFitOn(on->bbvi->itemNum, on->bbvi->items, on->bbvi->nf->binRoot, on->bbvi->nf->errorRoot, on->bbvi->nf->current);
    nextFitOn(on->vbvi->itemNum, on->vbvi->items, on->vbvi->nf->binRoot, on->vbvi->nf->errorRoot, on->vbvi->nf->current);
    bestFitOn(on->bbsi->binNum, on->bbsi->itemNum, on->bbsi->items, on->bbsi->bf->binRoot, on->bbsi->bf->errorRoot, on->bbsi->bf->current);
    bestFitOn(on->bbvi->binNum, on->bbvi->itemNum, on->bbvi->items, on->bbvi->bf->binRoot, on->bbvi->bf->errorRoot, on->bbvi->bf->current);
    bestFitOn(on->vbvi->binNum, on->vbvi->itemNum, on->vbvi->items, on->vbvi->bf->binRoot, on->vbvi->bf->errorRoot, on->vbvi->bf->current);
    on->bbsi->ff->binsUsed = countBins(on->bbsi->ff->current, on->bbsi->ff->binRoot);
    on->bbsi->nf->binsUsed = countBins(on->bbsi->nf->current, on->bbsi->nf->binRoot);
    on->bbsi->bf->binsUsed = countBins(on->bbsi->bf->current, on->bbsi->bf->binRoot);
    on->bbvi->ff->binsUsed = countBins(on->bbvi->ff->current, on->bbvi->ff->binRoot);
    on->bbvi->nf->binsUsed = countBins(on->bbvi->nf->current, on->bbvi->nf->binRoot);
    on->bbvi->bf->binsUsed = countBins(on->bbvi->bf->current, on->bbvi->bf->binRoot);
    on->vbvi->ff->binsUsed = countBins(on->vbvi->ff->current, on->vbvi->ff->binRoot);
    on->vbvi->nf->binsUsed = countBins(on->vbvi->nf->current, on->vbvi->nf->binRoot);
    on->vbvi->bf->binsUsed = countBins(on->vbvi->bf->current, on->vbvi->bf->binRoot);

}
/********************************************
 * Processes the offline section
 * 'off' contains the online information
 * 'on' contains the online information
 *******************************************/
void offline(HeuristicP off, HeuristicP on) {
    mergeSort(off->bbsi->items, 0, (off->bbsi->itemNum - 1));
    mergeSort(off->bbvi->items, 0, (off->bbvi->itemNum - 1));
    mergeSort(off->vbvi->items, 0, (off->vbvi->itemNum - 1));
    createBin(off->bbsi->ff, off->bbsi->bf, off->bbsi->nf, off->bbsi->binMin, off->bbsi->binMax, off->bbsi->binNum);
    createBin(off->bbvi->ff, off->bbvi->bf, off->bbvi->nf, off->bbvi->binMin, off->bbvi->binMax, off->bbvi->binNum);
    createBin(off->vbvi->ff, off->vbvi->bf, off->vbvi->nf, off->vbvi->binMin, off->vbvi->binMax, off->vbvi->binNum);
    matchBins(off, on);
    firstFitOn(off->bbsi->itemNum, off->bbsi->items, off->bbsi->ff->binRoot, off->bbsi->ff->errorRoot, off->bbsi->ff->current);
    firstFitOn(off->bbvi->itemNum, off->bbvi->items, off->bbvi->ff->binRoot, off->bbvi->ff->errorRoot, off->bbvi->ff->current);
    firstFitOn(off->vbvi->itemNum, off->vbvi->items, off->vbvi->ff->binRoot, off->vbvi->ff->errorRoot, off->vbvi->ff->current);
    bestFitOn(off->bbsi->binNum, off->bbsi->itemNum, off->bbsi->items, off->bbsi->bf->binRoot, off->bbsi->bf->errorRoot, off->bbsi->bf->current);
    bestFitOn(off->bbvi->binNum, off->bbvi->itemNum, off->bbvi->items, off->bbvi->bf->binRoot, off->bbvi->bf->errorRoot, off->bbvi->bf->current);
    bestFitOn(off->vbvi->binNum, off->vbvi->itemNum, off->vbvi->items, off->vbvi->bf->binRoot, off->vbvi->bf->errorRoot, off->vbvi->bf->current);
    off->bbsi->ff->binsUsed = countBins(off->bbsi->ff->current, off->bbsi->ff->binRoot);
    off->bbsi->bf->binsUsed = countBins(off->bbsi->bf->current, off->bbsi->bf->binRoot);
    off->bbvi->ff->binsUsed = countBins(off->bbvi->ff->current, off->bbvi->ff->binRoot);
    off->bbvi->bf->binsUsed = countBins(off->bbvi->bf->current, off->bbvi->bf->binRoot);
    off->vbvi->ff->binsUsed = countBins(off->vbvi->ff->current, off->vbvi->ff->binRoot);
    off->vbvi->bf->binsUsed = countBins(off->vbvi->bf->current, off->vbvi->bf->binRoot);
}

/********************************************
 * Intializes both the online and offline sections
 * 'off' contains the online information
 * 'on' contains the online information
 *******************************************/
void intialize(HeuristicP on, HeuristicP off) {
    on->bbsi = malloc(sizeof (struct BBSIS));
    on->bbsi->bf = malloc(sizeof (struct BestFitS));
    on->bbsi->nf = malloc(sizeof (struct NextFitS));
    on->bbsi->ff = malloc(sizeof (struct FirstFitS));
    on->bbsi->bf->errorRoot = malloc(sizeof (struct ErrorS));
    on->bbsi->nf->errorRoot = malloc(sizeof (struct ErrorS));
    on->bbsi->ff->errorRoot = malloc(sizeof (struct ErrorS));
    on->bbvi = malloc(sizeof (struct BBVIS));
    on->bbvi->bf = malloc(sizeof (struct BestFitS));
    on->bbvi->nf = malloc(sizeof (struct NextFitS));
    on->bbvi->ff = malloc(sizeof (struct FirstFitS));
    on->bbvi->bf->errorRoot = malloc(sizeof (struct ErrorS));
    on->bbvi->nf->errorRoot = malloc(sizeof (struct ErrorS));
    on->bbvi->ff->errorRoot = malloc(sizeof (struct ErrorS));
    on->vbvi = malloc(sizeof (struct VBVIS));
    on->vbvi->bf = malloc(sizeof (struct BestFitS));
    on->vbvi->nf = malloc(sizeof (struct NextFitS));
    on->vbvi->ff = malloc(sizeof (struct FirstFitS));
    on->vbvi->bf->errorRoot = malloc(sizeof (struct ErrorS));
    on->vbvi->nf->errorRoot = malloc(sizeof (struct ErrorS));
    on->vbvi->ff->errorRoot = malloc(sizeof (struct ErrorS));
    off->bbsi = malloc(sizeof (struct BBSIS));
    off->bbsi->bf = malloc(sizeof (struct BestFitS));
    off->bbsi->nf = malloc(sizeof (struct NextFitS));
    off->bbsi->ff = malloc(sizeof (struct FirstFitS));
    off->bbsi->bf->errorRoot = malloc(sizeof (struct ErrorS));
    off->bbsi->nf->errorRoot = malloc(sizeof (struct ErrorS));
    off->bbsi->ff->errorRoot = malloc(sizeof (struct ErrorS));
    off->bbvi = malloc(sizeof (struct BBVIS));
    off->bbvi->bf = malloc(sizeof (struct BestFitS));
    off->bbvi->nf = malloc(sizeof (struct NextFitS));
    off->bbvi->ff = malloc(sizeof (struct FirstFitS));
    off->bbvi->ff->binRoot = malloc(sizeof (struct BinS));
    off->bbvi->bf->errorRoot = malloc(sizeof (struct ErrorS));
    off->bbvi->nf->errorRoot = malloc(sizeof (struct ErrorS));
    off->bbvi->ff->errorRoot = malloc(sizeof (struct ErrorS));
    off->vbvi = malloc(sizeof (struct VBVIS));
    off->vbvi->bf = malloc(sizeof (struct BestFitS));
    off->vbvi->nf = malloc(sizeof (struct NextFitS));
    off->vbvi->ff = malloc(sizeof (struct FirstFitS));
    off->vbvi->bf->errorRoot = malloc(sizeof (struct ErrorS));
    off->vbvi->nf->errorRoot = malloc(sizeof (struct ErrorS));
    off->vbvi->ff->errorRoot = malloc(sizeof (struct ErrorS));
}

/********************************************
 * Stores the .txt information into arrays
 * 'off' contains the online information
 * 'on' contains the online information
 * 'argv' is an array containing user command input
 *******************************************/
void readIn(HeuristicP on, HeuristicP off, char** argv) {
    int info[4], i, x;
    for (x = 1; x < 4; x++) {
        FILE *input = fopen(argv[x], "r");
        for (i = 0; i < 4; i++) fscanf(input, "%i", &info[i]);
        int *array = malloc(info[0] * sizeof (int));
        i = 0;
        while (!feof(input)) {
            fscanf(input, "%i", &array[i]);
            i++;
        }
        if (x == 1) {
            on->bbsi->items = malloc(info[0] * sizeof (int));
            on->bbsi->itemNum = info[0];
            on->bbsi->binNum = info[1];
            on->bbsi->binMin = info[2];
            on->bbsi->binMax = info[3];
            on->bbsi->items = array;
            off->bbsi->items = malloc(info[0] * sizeof (int));
            off->bbsi->itemNum = info[0];
            off->bbsi->binNum = info[1];
            off->bbsi->binMin = info[2];
            off->bbsi->binMax = info[3];
            off->bbsi->items = array;
        } else if (x == 2) {
            on->bbvi->items = malloc(info[0] * sizeof (int));
            on->bbvi->itemNum = info[0];
            on->bbvi->binNum = info[1];
            on->bbvi->binMin = info[2];
            on->bbvi->binMax = info[3];
            on->bbvi->items = array;
            off->bbvi->items = malloc(info[0] * sizeof (int));
            off->bbvi->itemNum = info[0];
            off->bbvi->binNum = info[1];
            off->bbvi->binMin = info[2];
            off->bbvi->binMax = info[3];
            off->bbvi->items = array;
        } else if (x == 3) {
            on->vbvi->items = malloc(info[0] * sizeof (int));
            on->vbvi->itemNum = info[0];
            on->vbvi->binNum = info[1];
            on->vbvi->binMin = info[2];
            on->vbvi->binMax = info[3];
            on->vbvi->items = array;
            off->vbvi->items = malloc(info[0] * sizeof (int));
            off->vbvi->itemNum = info[0];
            off->vbvi->binNum = info[1];
            off->vbvi->binMin = info[2];
            off->vbvi->binMax = info[3];
            off->vbvi->items = array;
        }
    }
}
/********************************************
 * Creates all bins for all algorithms
 * 'ff' is first fit algorithm
 * 'bf' is best fit algorithm
 * 'nf' is next fit algorithm
 * binMin is the minimum weight for bins
 * minMax is the maximum weight of bins
 * binNum is the number of bins
 *******************************************/
void createBin(FirstFitP ff, BestFitP bf, NextFitP nf, int binMin, int binMax, int binNum) {
    int i;
    ff->binRoot = intializeBin(binMin, binMax);
    nf->binRoot = intializeBin(binMin, binMax);
    bf->binRoot = intializeBin(binMin, binMax);
    ff->current = ff->binRoot;
    bf->current = bf->binRoot;
    nf->current = nf->binRoot;
    for (i = 0; i < (binNum - 1); i++) {
        ff->current->right = intializeBin(binMin, binMax);
        nf->current->right = intializeBin(binMin, binMax);
        bf->current->right = intializeBin(binMin, binMax);
        nf->current = nf->current->right;
        bf->current = bf->current->right;
        ff->current = ff->current->right;
    }

    if (binMin != binMax) {
        ff->current = ff->binRoot;
        bf->current = bf->binRoot;
        nf->current = nf->binRoot;
        for (i = 0; i < binNum; i++) {
            ff->current->capacity = nf->current->capacity;
            bf->current->capacity = nf->current->capacity;
            nf->current = nf->current->right;
            bf->current = bf->current->right;
            ff->current = ff->current->right;
        }
    }
}
/********************************************
 * Intializes a bin
 * binMin is the minimum weight for bins
 * minMax is the maximum weight of bins
 *******************************************/
BinP intializeBin(int binMin, int binMax) {
    BinP newBin = malloc(sizeof (struct BinS));
    newBin->down = NULL;
    newBin->right = NULL;
    newBin->size = 0;
    if (binMin == binMax) newBin->capacity = binMax;
    else newBin->capacity = (rand() % (binMax - binMin)) + binMin;
    return newBin;
}

/********************************************
 * Intializes both the online and offline sections
 * 'off' contains the offline information
 * 'on' contains the online information
 *******************************************/
void matchBins(HeuristicP off, HeuristicP on){
    off->bbsi->bf->current = off->bbsi->bf->binRoot;
    off->bbvi->bf->current = off->bbvi->bf->binRoot;
    off->vbvi->bf->current = off->vbvi->bf->binRoot;
    off->bbsi->ff->current = off->bbsi->ff->binRoot;
    off->bbvi->ff->current = off->bbvi->ff->binRoot;
    off->vbvi->ff->current = off->vbvi->ff->binRoot;
    on->bbsi->bf->current = on->bbsi->bf->binRoot;
    on->bbvi->bf->current = on->bbvi->bf->binRoot;
    on->vbvi->bf->current = on->vbvi->bf->binRoot;
    on->bbsi->ff->current = on->bbsi->bf->binRoot;
    on->bbvi->ff->current = on->bbvi->bf->binRoot;
    on->vbvi->ff->current = on->vbvi->bf->binRoot;
    while (off->bbsi->bf->current){
        off->bbsi->bf->current->capacity = on->bbsi->bf->current->capacity;
        off->bbsi->ff->current->capacity = on->bbsi->ff->current->capacity;
        off->bbsi->bf->current = off->bbsi->bf->current->right;
        off->bbsi->ff->current = off->bbsi->ff->current->right;
        on->bbsi->bf->current = on->bbsi->bf->current->right;
        on->bbsi->ff->current = on->bbsi->ff->current->right;

    }
    while (off->bbvi->bf->current){
        off->bbvi->bf->current->capacity = on->bbvi->bf->current->capacity;
        off->bbvi->ff->current->capacity = on->bbvi->ff->current->capacity;
        off->bbvi->bf->current = off->bbvi->bf->current->right;
        off->bbvi->ff->current = off->bbvi->ff->current->right;
        on->bbvi->bf->current = on->bbvi->bf->current->right;
        on->bbvi->ff->current = on->bbvi->ff->current->right;
    }
    while (off->vbvi->bf->current){
        off->vbvi->bf->current->capacity = on->vbvi->bf->current->capacity;
        off->vbvi->ff->current->capacity = on->vbvi->ff->current->capacity;
        off->vbvi->bf->current = off->vbvi->bf->current->right;
        off->vbvi->ff->current = off->vbvi->ff->current->right;
        on->vbvi->bf->current = on->vbvi->bf->current->right;
        on->vbvi->ff->current = on->vbvi->ff->current->right;
    }
}

/********************************************
 * Processes the first fit algorithm
 * itemNum is number of items
 * items is array of all items
 * binRoot is the root of bins
 * errorRoot is root of errors
 * current is the current bin
 *******************************************/
void firstFitOn(int itemNum, int *items, BinP binRoot, ErrorP errorRoot, BinP current) {
    int i, error;
    errorRoot->size = -1;
    for (i = (itemNum - 1); i >= 0; i--) {
        current = binRoot;
        error = 0;
        while (error != 1 && current) {
            if (items[i] > (current->capacity - current->size)) {
                error = 0;
                if (items[i] > current->capacity) error = -1;
                current = current->right;
            } else {
                insertBin(current, items[i]);
                error = 1;
            }
        }
        if (error != 1) errorReport(errorRoot, items[i], error);
    }
}

/********************************************
 * Processes the next fit algorithm
 * itemNum is number of items
 * items is array of all items
 * binRoot is the root of bins
 * errorRoot is root of errors
 * current is the current bin
 *******************************************/
void nextFitOn(int itemNum, int *items, BinP binRoot, ErrorP errorRoot, BinP current) {
    int i, error;
    errorRoot->size = -1;
    current = binRoot;
    for (i = 0; i < itemNum; i++) {
        error = 0;
        while (error != 1 && current) {
            if (items[i] > (current->capacity - current->size)) {
                error = 0;
                if (items[i] > current->capacity) error = -1;
                current = current->right;
            } else {
                insertBin(current, items[i]);
                error = 1;
            }
        }
        if (!current) {
            current = binRoot;
            while (current->right) current = current->right;
            if (items[i] > current->capacity) error = -1;
            else error = 0;
            current = NULL;
        }
        if (error != 1) errorReport(errorRoot, items[i], error);
    }
}

/********************************************
 * Processes the best fit algorithm
 * binNum is the number of bins
 * itemNum is number of items
 * items is array of all items
 * binRoot is the root of bins
 * errorRoot is root of errors
 * current is the current bin
 *******************************************/
void bestFitOn(int binNum, int itemNum, int *items, BinP binRoot, ErrorP errorRoot, BinP current) {
    int i, x, error, goal = 9999;
    BinP best = malloc(sizeof (struct BinS));
    for (i = itemNum - 1; i >= 0; i--) {
        current = binRoot;
        error = 0;
        goal = 9999;
        for (x = 0; x < binNum; x++) {
            if (items[i] > (current->capacity - current->size)) current = current->right;
            else if (goal > (items[i] + (current->capacity - current->size))) {
                goal = items[i] + current->capacity - current->size;
                best = current;
                current = current->right;
            }
        }
        if (goal != 9999) {
            error = 1;
            insertBin(best, items[i]);
        } else {
            current = binRoot;
            while (current->right) current = current->right;
            if (items[i] > current->capacity) error = -1;
            else error = 0;
        }
        if (error != 1) errorReport(errorRoot, items[i], error);
    }
}

/********************************************
 * Inserts an item into a bin
 * item is an item to be inserted
 * current is the current bin
 *******************************************/
void insertBin(BinP current, int item) {
    current->size += item;
    ItemP insert = malloc(sizeof (struct ItemS));
    insert->size = item;
    insert->down = NULL;
    if (!current->down) current->down = insert;
    else {
        ItemP temp = malloc(sizeof (struct ItemS));
        temp = current->down;
        while (temp->down) temp = temp->down;
        temp->down = insert;
    }
}

/********************************************
 * Merge sort algorithm
 * sort is the array to be sorted
 * lower is the lower end
 * upper is the upper end
 *******************************************/
void mergeSort(int *sort, int lower, int upper) {
    if (lower < upper) {
        int mid;

        mid = (lower + upper) / 2;
        mergeSort(sort, lower, mid);
        mergeSort(sort, mid + 1, upper);
        merge(sort, lower, mid, upper);
    }
}

/********************************************
 * Merge sort algorithm
 * sort is the array to be sorted
 * lower is the lower end
 * mid is the middle
 * upper is the upper end
 *******************************************/
void merge(int *sort, int lower, int mid, int upper) {
    int i, midP, start, *tempArray;
    tempArray = (int *) malloc(sizeof (int) *1000010);
    i = lower;
    midP = mid + 1;
    start = 0;
    while (i <= mid && midP <= upper) {
        if (sort[i] < sort[midP]) {
            tempArray[start] = sort[i];
            i++;
        } else {
            tempArray[start] = sort[midP];
            midP++;
        }
        start++;
    }
    while (i <= mid) {
        tempArray[start] = sort[i];
        i++;
        start++;
    }
    while (midP <= upper) {
        tempArray[start] = sort[midP];
        midP++;
        start++;
    }
    start = 0;
    for (i = lower; i <= upper; i++, start++) sort[i] = tempArray[start];
    free(tempArray);
}

/********************************************
 * Counts number of bins
 * current is the current bin
 * binRoot is root of bins
 *******************************************/
int countBins(BinP current, BinP binRoot) {
    int count = 0;
    current = binRoot;
    while (current) {
        if (current->down) count++;
        current = current->right;
    }
    return count;


}

/********************************************
 * Stores error information
 * errorRoot is root of errors
 * item is item to be processed
 * error is the reason
 *******************************************/
void errorReport(ErrorP errorRoot, int item, int error) {
    ErrorP insert = malloc(sizeof (struct ErrorS));
    insert->size = item;
    insert->reason = error;
    insert->next = NULL;
    if (errorRoot->size == -1) {
        errorRoot->next = NULL;
        errorRoot->reason = error;
        errorRoot->size = item;
    } else {
        ErrorP temp = malloc(sizeof (struct ErrorS));
        temp = errorRoot;
        while (temp->next) temp = temp->next;
        temp->next = insert;
    }
}

/********************************************
 * prints out detailed summary to console
 *******************************************/
void summary(HeuristicP on, HeuristicP off) {
    printf("Policy\t Big bins\t Big Bins\tVariable bins\n");
    printf("\tsmall items\tvariable items\tvariable items\n");
    printf("Online\n");
    printf("First Fit   %i\t\t    %i\t\t\t%i\n", on->bbsi->ff->binsUsed, on->bbvi->ff->binsUsed, on->vbvi->ff->binsUsed);
    printf("Next Fit    %i\t\t    %i\t\t\t%i\n", on->bbsi->nf->binsUsed, on->bbvi->nf->binsUsed, on->vbvi->nf->binsUsed);
    printf("Best Fit    %i\t\t    %i\t\t\t%i\n", on->bbsi->bf->binsUsed, on->bbvi->bf->binsUsed, on->vbvi->bf->binsUsed);
    printf("Offline\n");
    printf("First Fit   %i\t\t    %i\t\t\t%i\n", off->bbsi->ff->binsUsed, off->bbvi->ff->binsUsed, off->vbvi->ff->binsUsed);
    printf("Best Fit    %i\t\t    %i\t\t\t%i\n", off->bbsi->bf->binsUsed, off->bbvi->bf->binsUsed, off->vbvi->bf->binsUsed);
    logFile(on, off);
}

/********************************************
 * prints out detailed log file to hdd
 *******************************************/
void logFile(HeuristicP on, HeuristicP off) {
    FILE *output = fopen("summary", "w");
    fprintf(output, "*****************ONLINE*****************\n");
    fprintf(output, "***Big bin, small items***\n");
    fprintf(output, "**First Fit**\n");
    outputLog(output, on->bbsi->ff->binRoot, on->bbsi->ff->errorRoot, on->bbsi->ff->binsUsed, on->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Next Fit**\n");
    outputLog(output, on->bbsi->nf->binRoot, on->bbsi->nf->errorRoot, on->bbsi->nf->binsUsed, on->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Best Fit**\n");
    outputLog(output, on->bbsi->bf->binRoot, on->bbsi->bf->errorRoot, on->bbsi->bf->binsUsed, on->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "***Big bin, variable items***\n");
    fprintf(output, "**First Fit**\n");
    outputLog(output, on->bbvi->ff->binRoot, on->bbvi->ff->errorRoot, on->bbvi->ff->binsUsed, on->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Next Fit**\n");
    outputLog(output, on->bbvi->nf->binRoot, on->bbvi->nf->errorRoot, on->bbvi->nf->binsUsed, on->bbvi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Best Fit**\n");
    outputLog(output, on->bbvi->bf->binRoot, on->bbvi->bf->errorRoot, on->bbvi->bf->binsUsed, on->bbvi->binNum);
    fprintf(output, "\n");
    fprintf(output, "***Variable bin, variable items***\n");
    fprintf(output, "**First Fit**\n");
    outputLog(output, on->vbvi->ff->binRoot, on->vbvi->ff->errorRoot, on->vbvi->ff->binsUsed, on->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Next Fit**\n");
    outputLog(output, on->vbvi->nf->binRoot, on->vbvi->nf->errorRoot, on->vbvi->nf->binsUsed, on->bbvi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Best Fit**\n");
    outputLog(output, on->vbvi->bf->binRoot, on->vbvi->bf->errorRoot, on->vbvi->bf->binsUsed, on->bbvi->binNum);
    fprintf(output, "\n");
    fprintf(output, "*****************OFFLINE*****************\n");
    fprintf(output, "***Big bin, small items***\n");
    fprintf(output, "**First Fit**\n");
    outputLog(output, off->bbsi->ff->binRoot, off->bbsi->ff->errorRoot, off->bbsi->ff->binsUsed, off->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Best Fit**\n");
    outputLog(output, off->bbsi->bf->binRoot, off->bbsi->bf->errorRoot, off->bbsi->bf->binsUsed, off->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "***Big bin, variable items***\n");
    fprintf(output, "**First Fit**\n");
    outputLog(output, off->bbvi->ff->binRoot, off->bbvi->ff->errorRoot, off->bbvi->ff->binsUsed, off->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Best Fit**\n");
    outputLog(output, off->bbvi->bf->binRoot, off->bbvi->bf->errorRoot, off->bbvi->bf->binsUsed, off->bbvi->binNum);
    fprintf(output, "\n");
    fprintf(output, "***Variable bin, variable items***\n");
    fprintf(output, "**First Fit**\n");
    outputLog(output, off->vbvi->ff->binRoot, off->vbvi->ff->errorRoot, off->vbvi->ff->binsUsed, off->bbsi->binNum);
    fprintf(output, "\n");
    fprintf(output, "**Best Fit**\n");
    outputLog(output, off->vbvi->bf->binRoot, off->vbvi->bf->errorRoot, off->vbvi->bf->binsUsed, off->bbvi->binNum);
}

/********************************************
 * prints out detailed log to hdd 
 *******************************************/
void outputLog(FILE *output, BinP binRoot, ErrorP errorRoot, int binsUsed, int binNum)
{
    int i = 1;
    BinP current = malloc(sizeof (struct BinS));
    ItemP temp = malloc(sizeof (struct ItemS));
    ErrorP error = malloc(sizeof (struct ErrorS));
    current = binRoot;
    while (current) {
        temp = current->down;
        if (temp) {
            fprintf(output, "Bin%i(%i) ", i, current->capacity);
            while (temp) {
                if (!temp->down) fprintf(output, "%i", temp->size);
                else fprintf(output, "%i,", temp->size);
                temp = temp->down;
            }
            fprintf(output, "\n");
        }
        current = current->right;
        i++;
    }

    error = errorRoot;
    if (error && error->size != -1){
    fprintf(output, "Did not place item: ");
    while (error) {
        if (error->reason == 0 && error->size != -1) fprintf(output, "%i (no bins left)", error->size);
        else if (error->reason == 1 && error->size != -1) fprintf(output, "%i (too big)", error->size);
        if (error->next) fprintf(output, ", ");
        error = error->next;
    }
    fprintf(output, "\n");
    }

    current = binRoot;
    temp = current->down;
    i = 1;
    if(binsUsed < binNum) fprintf(output, "Did not use ");
    while (current) {
        temp = current->down;
        if (!temp) {
            fprintf(output, "Bin%i(%i) ", i, current->capacity);

        }
        current = current->right;
        i++;
    }
    fprintf(output, "\n");
}
