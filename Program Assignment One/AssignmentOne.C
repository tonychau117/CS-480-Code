#include <stdio.h>
#include <unistd.h> // needed to get the process id

#include <semaphore.h> // import for semaphore flag
#include <pthread.h> // import for creating the threads

#define NUMBER_OF_THREADS 7 // number of threads

int main()
{
    FILE *fptr;

    fptr = fopen("QUOTE.txt", "w"); // creates the QUOTE.txt file, w used to write in it -> if doesnt exist itll amke one   

    fprintf(fptr, "The ProcessID is" + getpid()); // gets the process ID
    fprintf(fptr, "%d\r\n"); // carriage return and newline, carriage return with \r
    fclose(fptr);          // closes the file that we are writing in

    // creating the semaphore FLAG
    sem_t sem_flag;
    sem_init(&sem_flag, 0, 0);

    // creating threads
    pthread_t threads[NUMBER_OF_THREADS]; // declares seven threads to use
   

    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_create(threads[i++], NULL, thread_function, (void*)i); // initializes them, passes in the thread # for the argument of the fucntion
    }

    // destroying the semaphore
    int sem_destroy(sem_t &sem_flag);

    printf("Hello World");
}

// quote even - “Controlling complexity is the essence of computer programming. --Brian Kernighan
// quote odd - “Computer science is no more about computers than astronomy is about telescopes.” --Edsger Dijkstra

// thread function for what the thread is going to do
void *thread_function(void* tid)
{
    // even threads - once every 2 seconds
    // odd threads - once every 3 seconnds
    if(pthread_self() % 2 == 0)
    {

    }

    fptr = fopen("QUOTE.txt", "w"); // opens the QUOTE file
    
    fprintf(fptr)

    // retrieve the flag
}