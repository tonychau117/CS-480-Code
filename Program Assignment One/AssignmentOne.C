#include <stdio.h>
#include <unistd.h> // needed to get the process id

#include <semaphore.h> // import for semaphore flag
#include <pthread.h> // import for creating the threads
#include <stdlib.h> // import for exit() and dynamic memory

#define NUMBER_OF_THREADS 7 // number of threads
#define EVEN_QUOTE "\"Controlling complexity is the essence of computer programming.\" --Brian Kernighan"
#define ODD_QUOTE "\"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra"

sem_t sem_flag; // global semaphore

int main()
{
    FILE *fptr = fopen("QUOTE.txt", "w"); // creates the QUOTE.txt file, w used to write in it -> if doesnt exist itll amke one
    if (fptr == NULL) { // checks if file was created
    	perror("QUOTE.txt failed");
    	exit(EXIT_FAILURE);
    }
    fprintf(fptr, "The ProcessID is: %d ", getpid()); // gets the process ID
    fprintf(fptr, "\r\n"); // carriage return and newline, carriage return with \r
    fclose(fptr);          // closes the file that we are writing in

    // creating the semaphore FLAG - maybe give it global scope
    if (sem_init(&sem_flag, 0, 1) != 0) { // error check for semaphore
    	perror("Semaphore creation failed");
    	exit(EXIT_FAILURE);
    }

    // creating threads
    pthread_t threads[NUMBER_OF_THREADS]; // declares seven threads to use
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    	int *thread_num = malloc(sizeof(int)); // memory allocation
    	*thread_num = i; // assigns thread number
    	if (pthread_create(&threads[i], NULL, thread_function, (void *)thread_num) !=0) { //error check
    		perror("Thread creation failed");
    		exit(EXIT_FAILURE);
    	}
    }

    // joining thread
    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // destroying the semaphore
    sem_destroy(&sem_flag);
    printf("Threads successfully completed. Program exiting.\n");
    return 0;
}

// quote even - “Controlling complexity is the essence of computer programming. --Brian Kernighan
// quote odd - “Computer science is no more about computers than astronomy is about telescopes.” --Edsger Dijkstra

// thread function for what the thread is going to do
void *thread_function(void *arg)
{
    // even threads - once every 2 seconds
    // odd threads - once every 3 seconnds
    int thread_id = *(int *)arg; // get thread ID from arg
    free(arg); // free allocated memory

    for(int i = 0; i < 8; i++) { // run 8 times
    	if (thread_id % 2 == 0) {
    		 sleep(2); // even threads wait 2 seconds
    	}
    	else {
    		sleep(3); // odd threads wait 3 seconds
    	}

    	sem_wait(&sem_flag); // lock semaphore

    	FILE *fptr = fopen("QUOTE.txt", "a"); // opens the QUOTE file
    	if (fptr == NULL) {
    		sem_post(&sem_flag);
    		pthread_exit(NULL);
    	}

    	fprintf(fptr, "Thread ID %d - ", thread_id); // prints thread ID
    	fprintf(fptr, "%s\r\n", (thread_id % 2 == 0) ? EVEN_QUOTE : ODD_QUOTE); // chooses quote
    	fclose(fptr); // close file

    	printf("Thread %d is running\n", thread_id);

    	sem_post(&sem_flag); // release the semaphore flag

    }

    pthread_exit(NULL);
}

