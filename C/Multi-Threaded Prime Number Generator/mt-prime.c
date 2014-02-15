/***************************************************************
 Author: Charbel Boutros
 File Name: mt-prime.c
 ***************************************************************/

//Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define BILLION 1E9
#define TRUE 1
#define FALSE 0

/* Function declarations */
void process(int, int);
void* primalityCheck(void*);
int isPrime(int);
void handleInput(int);
void print(struct timespec, struct timespec, int, int);

//Global variable
int COUNTER = 1;

int main(int argc, char *argv[]) {
	handleInput(argc);
	int max = atoi(argv[1]), numberOfThreads = atoi(argv[2]);
	clockid_t clk_id = 0;
	struct timespec start, stop;
	clock_gettime(clk_id, &start);
	process(max, numberOfThreads);
	clock_gettime(clk_id, &stop);
	print(start, stop, max, numberOfThreads);
	pthread_exit(NULL);
	return 0;
}

/*
 * Creates threads and checks for prime numbers
 * @param max number of values to check for prime numbers
 * @param numberOfThreads number of threads to use
 */
void process(int max, int numberOfThreads) {
	int i;
	pthread_t threads[numberOfThreads];
	for (i = 0; i < numberOfThreads; i++)
		pthread_create(&threads[i], NULL, primalityCheck, (void*) &max);
	for (i = 0; i < numberOfThreads; i++)
		pthread_join(threads[i], NULL);
}

/*
 * Loops through number to test if prime
 * @param max number of values to check for prime numbers
 */
void* primalityCheck(void* max) {
	int* maxNum = (int*) max;
	while (COUNTER < *maxNum) {
		if (isPrime(COUNTER) == TRUE)
			fprintf(stdout, "%i\n", COUNTER);
		COUNTER++;
	}
	pthread_exit(NULL);
}

/*
 * Checks if number is a prime number
 * @param number value to check if prime
 */
int isPrime(int number) {
	int i;
	if (number == 1)
		return FALSE;
	if (number == 2)
		return TRUE;
	if (number % 2 == 0)
		return FALSE;
	for (i = 3; i <= (int) sqrt((double) number); i += 2) {
		if (number % i == 0)
			return FALSE;
	}
	return TRUE;
}

/*
 * Handles input error
 * @param argc number of input tokens
 */
void handleInput(int argc) {
	if (argc != 3) {
		fprintf(stderr, "Usage : <maxNumbers> <numberOfThreads>\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Prints summary to console
 * @param start contains start time values
 * @param stop contains stop time values
 * @param max number of values to check for prime numbers
 * @param numberOfThreads number of threads used
 */
void print(struct timespec start, struct timespec stop, int max, int numberOfThreads) {
	double accum = (stop.tv_sec - start.tv_sec)
			+ (stop.tv_nsec - start.tv_nsec) / BILLION;
	fprintf(stderr, "Max numbers: %i\nThreads: %i\nElasped time: %lf\n", max, numberOfThreads, accum);
}
