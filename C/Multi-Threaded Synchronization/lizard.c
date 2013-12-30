/***************************************************************
 Author: Charbel Boutros
 File Name: lizard.c
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#ifdef __APPLE__
#include <mach/semaphore.h>
#include <mach/task.h>
#define sem_init(a,b,c)     semaphore_create(mach_task_self(), (semaphore_t *)a, SYNC_POLICY_FIFO, c)
#define sem_destroy(a)      semaphore_destroy(mach_task_self(), *((semaphore_t *)a))
#define sem_post(a)         semaphore_signal(*((semaphore_t *)a))
#define sem_wait(a)         semaphore_wait(*((semaphore_t *)a))
#define sem_t               semaphore_t
#else
#include <semaphore.h>
#endif

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */

/*
 * Function prototypes go here
 * You may need more functions, but I don't think so
 */
void * lizardThread(void * param);

/*
 * Define "constant" values here
 */

/*
 * Make this 1 to check for lizards traveling in both directions
 * Leave it 0 to allow bidirectional travel
 */
#define UNIDIRECTIONAL       0

/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
#define WORLDEND             30

/*
 * Number of lizard threads to create
 */
#define NUM_LIZARDS          20

/*	
 * Maximum lizards crossing at once before alerting cats
 */
#define MAX_LIZARD_CROSSING  4

/*
 * Maximum seconds for a lizard to sleep
 */
#define MAX_LIZARD_SLEEP     3

/*
 * Maximum seconds for a lizard to eat
 */
#define MAX_LIZARD_EAT       5

/*
 * Number of seconds it takes to cross the driveway
 */
#define CROSS_SECONDS        2

/*
 * Declare global variables here
 */

pthread_mutex_t mutex;              
sem_t empty;                        
sem_t full;                         /**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
int numCrossingSago2MonkeyGrass;
int numCrossingMonkeyGrass2Sago;
int debug;
int running;
/**************************************************/

/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv) {
	/*
	 * Declare local variables
	 */
	int i;                          
	pthread_t threads[NUM_LIZARDS]; 

	/*
	 * Check for the debugging flag (-d)
	 */
	debug = 0;
	if (argc > 1)
		if (strncmp(argv[1], "-d", 2) == 0)
			debug = 1;

	/*
	 * Initialize variables
	 */
	numCrossingSago2MonkeyGrass = 0;
	numCrossingMonkeyGrass2Sago = 0;
	running = 1;

	/*
	 * Initialize random number generator
	 */
	srandom((unsigned int) time(NULL));

	/*
	 * Initialize locks and/or semaphores
	 */

	sem_init(&empty, 0, MAX_LIZARD_CROSSING);   
	sem_init(&full, 0, 0);                      

	/*
	 * Create NUM_LIZARDS lizard threads
	 */
	for (i = 0; i < NUM_LIZARDS; i++)
		pthread_create(&threads[i], NULL, lizardThread, (void*) (intptr_t) i);  

	/*
	 * Now let the world run for a while
	 */
	sleep( WORLDEND);

	/*
	 * That's it - the end of the world
	 */
	running = 0;

	/*
	 * Wait until all threads terminate
	 */
	for (i = 0; i < NUM_LIZARDS; i++)
		pthread_join(threads[i], NULL);     

	/*
	 * Delete the locks and semaphores
	 */
	pthread_mutex_destroy(&mutex);      
	sem_destroy(&empty);                
	sem_destroy(&full);                 
	/*
	 * Exit happily
	 */
	return 0;
}

/*
 * These prototypes are declared here so that main()
 * can't use them directly.  Functions and variables
 * must be declared before they can be used.  Using them
 * below this point is fine.
 */

void lizard_sleep(int num);
void sago_2_monkeyGrass_is_safe(int num);
void cross_sago_2_monkeyGrass(int num);
void made_it_2_monkeyGrass(int num);
void lizard_eat(int num);
void monkeyGrass_2_sago_is_safe(int num);
void cross_monkeyGrass_2_sago(int num);
void made_it_2_sago(int num);

/*
 * lizardThread()
 *
 * Follows the algorithm provided in the assignment
 * description to simulate lizards crossing back and forth
 * between a sago palm and some monkey grass.  
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void * lizardThread(void * param) {
	int num = (int) (intptr_t) param;   
	if (debug) {
		printf("[%2d] lizard is alive\n", num);
		fflush(stdout);
	}

	/*
	 * Follow the algorithm given in the assignment
	 * using calls to the functions declared above.
	 * You'll need to complete the implementation of
	 * some functions by filling in the code.  Some
	 * are already completed - see the comments.
	 */
    while(running){
        lizard_sleep(num);                  
        sago_2_monkeyGrass_is_safe(num);    
        cross_sago_2_monkeyGrass(num);      
        made_it_2_monkeyGrass(num);         
        lizard_eat(num);                    
        monkeyGrass_2_sago_is_safe(num);    
        cross_monkeyGrass_2_sago(num);      
        made_it_2_sago(num);                
    }
	pthread_exit(NULL);
}

/*
 * lizard_sleep()
 *
 * Simulate a lizard sleeping for a random amount of time
 * input: lizard number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void lizard_sleep(int num) {
	int sleepSeconds;

	sleepSeconds = 1 + (int) (random() / (double) RAND_MAX * MAX_LIZARD_SLEEP);

	if (debug) {
		printf("[%2d] sleeping for %d seconds\n", num, sleepSeconds);
		fflush( stdout);
	}

	sleep(sleepSeconds);

	if (debug) {
		printf("[%2d] awake\n", num);
		fflush( stdout);
	}
}

/*
 * sago_2_monkeyGrass_is_safe()
 *
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void sago_2_monkeyGrass_is_safe(int num) {
	if (debug) {
		printf("[%2d] checking  sago -> monkey grass\n", num);
		fflush( stdout);
	}

	sem_wait(&empty);               
	pthread_mutex_lock(&mutex);     
	numCrossingSago2MonkeyGrass++;  
	pthread_mutex_unlock(&mutex);   
	sem_post(&full);                

	if (debug) {
		printf("[%2d] thinks  sago -> monkey grass  is safe\n", num);
		fflush( stdout);
	}
}

/*
 * cross_sago_2_monkeyGrass()
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void cross_sago_2_monkeyGrass(int num) {
	if (debug) {
		printf("[%2d] crossing  sago -> monkey grass\n", num);
		fflush( stdout);
	}

	/*
	 * Check for too many lizards crossing
	 */
	if (numCrossingSago2MonkeyGrass
			+ numCrossingMonkeyGrass2Sago> MAX_LIZARD_CROSSING) {
		printf("\tThe cats are happy - they have toys.\n");
		printf("\t%d crossing sago -> monkey grass\n",
				numCrossingSago2MonkeyGrass);
		exit(-1);
	}

	/*
	 * Check for lizards cross both ways
	 */
	if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL) {
		printf("\tCrash!  We have a pile-up on the concrete.\n");
		printf("\t%d crossing sago -> monkey grass\n",
				numCrossingSago2MonkeyGrass);
		printf("\t%d crossing monkey grass -> sago\n",
				numCrossingMonkeyGrass2Sago);
		exit(-1);
	}

	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep( CROSS_SECONDS);

	/*
	 * That one seems to have made it
	 */
	sem_wait(&full);                
	pthread_mutex_lock(&mutex);     
	numCrossingSago2MonkeyGrass--;  
	pthread_mutex_unlock(&mutex);   
	sem_post(&empty);               
}

/*
 * made_it_2_monkeyGrass()
 *
 * Tells others they can go now
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void made_it_2_monkeyGrass(int num) {
	/*
	 * Whew, made it across
	 */
	if (debug) {
		printf("[%2d] made the  sago -> monkey grass  crossing\n", num);
		fflush( stdout);
	}

}

/*
 * lizard_eat()
 *
 * Simulate a lizard eating for a random amount of time
 * input: lizard number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void lizard_eat(int num) {
	int eatSeconds;

	eatSeconds = 1 + (int) (random() / (double) RAND_MAX * MAX_LIZARD_EAT);

	if (debug) {
		printf("[%2d] eating for %d seconds\n", num, eatSeconds);
		fflush( stdout);
	}

	/*
	 * Simulate eating by blocking for a few seconds
	 */
	sleep(eatSeconds);

	if (debug) {
		printf("[%2d] finished eating\n", num);
		fflush( stdout);
	}
}

/*
 * monkeyGrass_2_sago_is_safe()
 *
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void monkeyGrass_2_sago_is_safe(int num) {
	if (debug) {
		printf("[%2d] checking  monkey grass -> sago\n", num);
		fflush( stdout);
	}

	sem_wait(&empty);               
	pthread_mutex_lock(&mutex);     
	numCrossingMonkeyGrass2Sago++;  
	pthread_mutex_unlock(&mutex);   
	sem_post(&full);                

	if (debug) {
		printf("[%2d] thinks  monkey grass -> sago  is safe\n", num);
		fflush( stdout);
	}
}

/*
 * cross_monkeyGrass_2_sago()
 *
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void cross_monkeyGrass_2_sago(int num) {
	if (debug) {
		printf("[%2d] crossing  monkey grass -> sago\n", num);
		fflush( stdout);
	}

	/*
	 * Check for too many lizards crossing
	 */
	if (numCrossingMonkeyGrass2Sago
			+ numCrossingSago2MonkeyGrass> MAX_LIZARD_CROSSING) {
		printf("\tThe cats say yum! - they love lizards.\n");
		printf("\t%d crossing monkey grass -> sago\n",
				numCrossingMonkeyGrass2Sago);
		exit(-1);
	}

	/*
	 * Check for lizards cross both ways
	 */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL) {
		printf("\tOh No!, the lizards have cats all over them.\n");
		printf("\t%d crossing sago -> monkey grass\n",
				numCrossingSago2MonkeyGrass);
		printf("\t%d crossing monkey grass -> sago\n",
				numCrossingMonkeyGrass2Sago);
		exit(-1);
	}

	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep( CROSS_SECONDS);

	/*
	 * That one seems to have made it
	 */
	sem_wait(&full);                
	pthread_mutex_lock(&mutex);     
	numCrossingMonkeyGrass2Sago--;  
	pthread_mutex_unlock(&mutex);   
	sem_post(&empty);               
}

/*
 * made_it_2_sago()
 *
 * Tells others they can go now
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void made_it_2_sago(int num) {
	/*
	 * Whew, made it across
	 */
	if (debug) {
		printf("[%2d] made the  monkey grass -> sago  crossing\n", num);
		fflush( stdout);
	}

}

