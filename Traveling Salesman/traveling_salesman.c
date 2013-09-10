/***************************************************************  
 Student Name: Charbel Boutros  
 File Name: traveling_salesman.c  ***************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h> 
#include <time.h> 

/********************************************
 *Program type definitions
 *******************************************/
typedef struct BruteForce *BF;
typedef struct GeneticAlgorithm *GA;

/********************************************
 *Function prototypes
 *******************************************/
int Fact(int);
void CreateBrute(int, int, double[20][20], BF);
void Permutations(int, int, int, double*, double[20][20], BF);
void CalcWeight(int, int, double*, double [20][20], BF);
void CreateGenetic(int, int, double [20][20], GA);
void GeneticWeight(int, int, int *, double **, double [20][20], GA);
void IterativePerm(int, int, int *, int, double **, double [20][20], GA);

/********************************************
 *Contains Brute Force Data
 *******************************************/
struct BruteForce {
    double elite[20];
    int size;
    unsigned long start;
    unsigned long end;
};

/********************************************
 *Contains Genetic Algorithm Data
 *******************************************/
struct GeneticAlgorithm {
    double elite[20][20];
    int size;
    int generations;
    int runs;
    double mutation;
    unsigned long start;
    unsigned long end;
};

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int i = 0, j = 0;
    if (argc != 2) {
        printf("Missing arguments!\n");
        exit(1);
    }
    FILE *data = fopen(argv[1], "r");
    if (data == 0) {
        printf("Could not open file\n");
        exit(1);
    }
    double cityWeights[20][20];
    double temp;
    //Inputs city weights into 2D array
    while (!feof(data)) {
        fscanf(data, "%lf", &temp);
        if (i == j && j != 19) {
            cityWeights[i][j] = 0;
            j++;
        } else if (i == j && j >= 19) break;
        cityWeights[i][j] = temp;
        cityWeights[j][i] = temp;
        if (j == 19 && i != 19) {
            i++;
            j = i;
        } else j++;
    }
    fclose(data);
    BF Brute = malloc(sizeof (struct BruteForce));
    GA Genetic = malloc(sizeof (struct GeneticAlgorithm));
    int cityNum, cityStart;
    printf("Number of cities in current run : ");
    scanf("%i", &cityNum);
    printf("Starting city : ");
    scanf("%i", &cityStart);
    while (cityStart > cityNum || cityStart <= 0) {
        printf("Starting city must be greater than zero and less than number of cities\n");
        printf("Starting city : \n");
        scanf("%i", &cityStart);
    }
    printf("Number of generations to run : ");
    scanf("%i", &Genetic->generations);
    printf("Number of individuals in each generation : ");
    scanf("%i", &Genetic->runs);
    printf("Percentage of each generation to be made with mutations : ");
    scanf("%lf", &Genetic->mutation);
    Genetic->mutation = (int) ((Genetic->runs * (Genetic->mutation / 100)) + 0.5);
    CreateBrute(cityStart, cityNum, cityWeights, Brute);
    CreateGenetic(cityStart, cityNum, cityWeights, Genetic);
    printf("Optimal cost: %lf\n", Brute->elite[Brute->size]);
    printf("Best cost found: %lf\n", Genetic->elite[0][Genetic->size]);
    printf("Percentage of optimum: %lf%%\n", ((Brute->elite[Brute->size] / Genetic->elite[0][Genetic->size])*100));
    printf("Optimal route:    ");
    for (i = 0; i < Brute->size; i++) printf("%i ", (int) Brute->elite[i] + 1);
    printf("%i", cityStart);
    printf("\nBest route found: ");
    for (i = 0; i < Genetic->size; i++) printf("%i ", (int) Genetic->elite[0][i] + 1);
    printf("%i", cityStart);




}

/********************************************
 * Calculates X into factorial
 *******************************************/
int Fact(int x) {
    int i, z = 1;
    for (i = 2; i <= x; i++) z *= i;
    return z;
}

/********************************************
 * Brute Force Section
 * Citystart = starting city
 * cityNum = number of cities
 * cityWeights = weight of cities
 * Brute = struct containing brute information
 *******************************************/
void CreateBrute(int cityStart, int cityNum, double cityWeights[20][20], BF Brute) {
    int i = cityNum - 1;
    i = Fact(i);
    double* tour;
    int x, y;
    //Creates array for brute force tours
    tour = (double *) malloc((cityNum+1) * sizeof (double));
    for (i = 0; i < cityNum; i++)
    tour[i] = i;
    tour[0] = cityStart - 1;
    tour[cityStart - 1] = 0;
    i = cityNum - 1;
    i = Fact(i);
    Brute->size = cityNum;
    Brute->elite[cityNum] = 9999;
    Brute->start = clock();
    Permutations(i, cityNum, cityNum, tour, cityWeights, Brute);
    Brute->end = clock() - Brute->start;
    Brute->end = Brute->end / (CLOCKS_PER_SEC / 1000);
    printf("\n---------------------------------------\n");
        printf("\t\tResults\n");
            printf("---------------------------------------");
    printf("\nBrute force took %lu msecs to calculate", Brute->end);
}

/********************************************
 * Recursive permutation code
 * Row = number of rows in array
 * Col = number of columns in array
 * Count = current row position
 * N = current col position
 * cityWeights = weight of cities
 * Brute = contains brute force information
 *******************************************/
void Permutations(int row, int col, int n, double* tour, double cityWeights[20][20], BF Brute) {
    int temp, i;
    if (n == 1) CalcWeight(row, col,tour, cityWeights, Brute);
    else {
        for (i = 1; i < n; i++) {
            temp = tour[i];
            tour[i] = tour[n - 1];
            tour[n - 1] = temp;
            Permutations(row, col, (n - 1), tour, cityWeights, Brute);
            temp = tour[i];
            tour[i] = tour[n - 1];
            tour[n - 1] = temp;
        }
    }
}

/********************************************
 * Calculates weight of each tour
 * and stores best routes
 * Row = number of rows in array
 * Col = number of columns in array
 * Count = current row position
 * tour = 2D array containing tours
 * cityWeights = weight of cities
 * Brute = contains brute force information
 *******************************************/
void CalcWeight(int row, int col, double* tour, double cityWeights[20][20], BF Brute) {
    double weight;
    int i, xOne, xTwo;
    weight = 0;
    //Calculates weight of tour 
    for (i = 0; i < (col - 1); i++) {
        xOne = tour[i];
        xTwo = tour[i + 1];
        weight += cityWeights[xOne][xTwo];
    }
    xOne = tour[col - 1];
    xTwo = tour[0];
    weight += cityWeights[xOne][xTwo];
    tour[col] = weight;
    //Finds best routes 
    if (tour[col] < Brute->elite[col])
        for (i = 0; i <= col; i++) Brute->elite[i] = tour[i];
}

/********************************************
 * Genetic Algorithm section
 * cityStart = starting city
 * cityNum = number of cities
 * cityWeights = weight of cities
 * Genetic = struct containing genetic information
 *******************************************/
void CreateGenetic(int cityStart, int cityNum, double cityWeights[20][20], GA Genetic) {
    double **tour, temp, weight;
    int i, x, y, a, b, best, worst, rOne, rTwo, xOne, xTwo;
    //Creates 2D array to hold tours
    tour = (double **) malloc(Genetic->runs * 1.5 * sizeof (double*));
    for (x = 0; x <= Genetic->runs; x++)
        tour[x] = (double *) malloc(cityNum * 1.5 * sizeof (double));
    for (i = 0; i < cityNum; i++) {
        tour[0][i] = i;
    }
    tour[0][0] = (cityStart - 1) * 100;
    tour[0][cityStart - 1] = 0;
    Genetic->size = cityNum;
    Genetic->elite[0][cityNum] = 9999;
    Genetic->elite[1][cityNum] = 9999;
    int count = 1, *countP;
    countP = &count;
    Genetic->start = clock();
    //Creates intial population
    for (y = 0; y < Genetic->runs; y++)
        IterativePerm(Genetic->runs, cityNum, countP, cityNum, tour, cityWeights, Genetic);
    //Performs mutations per i generations
    for (i = 0; i < Genetic->generations; i++) {
        for (x = 0; x < Genetic->mutation; x++) {
            a = 9999;
            b = 0;
            weight = 0;
            do {
                rOne = (rand() % (cityNum - 2)) + 1;
                rTwo = (rand() % (cityNum - 2)) + 1;
            } while (rOne == rTwo);
            for (y = 0; y < Genetic->runs; y++) {
                if (tour[y][cityNum] > b) {
                    b = tour[y][cityNum];
                    worst = y;
                }
            }
            for (y = 0; y <= cityNum; y++) tour[worst][y] = Genetic->elite[0][y];
            temp = tour[worst][rOne];
            tour[worst][rOne] = tour[worst][rTwo];
            tour[worst][rTwo] = temp;
            for (y = 0; y < (cityNum - 1); y++) {
                xOne = tour[worst][y];
                xTwo = tour[worst][y + 1];
                weight += cityWeights[xOne][xTwo];
            }
            xOne = tour[worst][cityNum - 1];
            xTwo = tour[worst][0];
            weight += cityWeights[xOne][xTwo];
            tour[worst][cityNum] = weight;
            if (tour[worst][cityNum] < Genetic->elite[0][cityNum])
            for (y = 0; y <= cityNum; y++) Genetic->elite[0][y] = tour[worst][y];

        }
    }
    Genetic->end = clock() - Genetic->start;
    Genetic->end = Genetic->end / (CLOCKS_PER_SEC / 1000);
    printf("\nGenetic algorithm took %lu msecs to calculate\n", Genetic->end);

}

/********************************************
 * Calculates weight of each tour
 * and stores best routes
 * Row = number of rows in array
 * Col = number of columns in array
 * Count = current row position
 * tour = 2D array containing tours
 * cityWeights = weight of cities
 * Genetic = contains genetic force information
 *******************************************/
void GeneticWeight(int row, int col, int *count, double **tour, double cityWeights[20][20], GA Genetic) {
    tour[0][0] /= 100;
    double weight;
    int i, xOne, xTwo;
    weight = 0;
    //Calculates weight of tour 
    for (i = 0; i < (col - 1); i++) {
        xOne = tour[0][i];
        xTwo = tour[0][i + 1];
        weight += cityWeights[xOne][xTwo];
    }
    xOne = tour[0][col - 1];
    xTwo = tour[0][0];
    weight += cityWeights[xOne][xTwo];
    tour[0][col] = weight;
    if (*count == row) return;
    //Stores tours in 2D array 
    for (i = 0; i <= col; i++) {
        tour[*count][i] = tour[0][i];
    }
    //Finds best routes 
    if (tour[*count][col] < Genetic->elite[0][col])
        for (i = 0; i <= col; i++) Genetic->elite[0][i] = tour[*count][i];
    else if (tour[*count][col] < Genetic->elite[1][col])
        for (i = 0; i <= col; i++) Genetic->elite[1][i] = tour[*count][i];
    *count += 1;
    tour[0][0] *= 100;
}

/********************************************
 * Iterative permutation code
 * Row = number of rows in array
 * Col = number of columns in array
 * Count = current row position
 * N = current col position
 * s = 2D array containing tours
 * cityWeights = weight of cities
 * Genetic = contains genetic force information
 *******************************************/
void IterativePerm(int row, int col, int *count, int n, double **s, double cityWeights[20][20], GA Genetic) {
    int nf = n, i, m, k, p, q;
    nf = Fact(n);
    if (nf > 362880) nf = Fact(9);
    double temp;
    for (i = 1; i < nf; i++) {
        m = n - 2;
        while (s[0][m] > s[0][m + 1]) m--;
        k = n - 1;
        while (m < 0)m++;
        while (s[0][m] > s[0][k]) k--;
        temp = s[0][m];
        s[0][m] = s[0][k];
        s[0][k] = temp;
        p = m + 1;
        q = n - 1;

        while (p < q) {
            temp = s[0][p];
            s[0][p] = s[0][q];
            s[0][q] = temp;
            p++;
            q--;
        }
    }
    GeneticWeight(row, col, count, s, cityWeights, Genetic);
} 