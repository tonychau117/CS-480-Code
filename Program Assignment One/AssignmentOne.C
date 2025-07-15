#include <stdio.h>
#include <unistd.h> // needed to get the process id

#include <semaphore.h> // import for semaphore flag
#include <pthread.h> // import for creating the threads

#define NUMBER_OF_THREADS 7 // number of threads
#define EVEN_QUOTE "“Controlling complexity is the essence of computer programming.” --Brian Kernighan"
#define ODD_QUOTE "“Computer science is no more about computers than astronomy is about telescopes.” --Edsger Dijkstra"

sem_t sem_flag;

int main()
{
    FILE *fptr = fopen("QUOTE.txt", "w"); // creates the QUOTE.txt file, w used to write in it -> if doesnt exist itll amke one   

    fprintf(fptr, "The ProcessID is: ", getpid()); // gets the process ID
    fprintf(fptr, "\r\n"); // carriage return and newline, carriage return with \r
    fclose(fptr);          // closes the file that we are writing in

    // creating the semaphore FLAG - maybe give it global scope
    sem_t sem_flag;
    sem_init(&sem_flag, 0, 0);

    // creating threads
    pthread_t threads[NUMBER_OF_THREADS]; // declares seven threads to use
    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_create(threads[i], NULL, thread_function, (void*)i); // initializes them, passes in the thread # for the argument of the fucntion, maybe change last argument
    }








    // destroying the semaphore
    sem_destroy(&sem_flag);
}

// quote even - “Controlling complexity is the essence of computer programming. --Brian Kernighan
// quote odd - “Computer science is no more about computers than astronomy is about telescopes.” --Edsger Dijkstra

// thread function for what the thread is going to do
void *thread_function(void* tid)
{
    // even threads - once every 2 seconds
    // odd threads - once every 3 seconnds
    if(<thread_id> % 2 == 0) // do something about finding the argument for getting the thread id
    {

    }
    else
    {

    }

    FILE *fptr = fopen("QUOTE.txt", "w"); // opens the QUOTE file
    
    fprintf(fptr, "\r\nThread ID: ", pthread_self(), <insert the quote here depending on thread even/odd); // writing hte thread id, quote, carr return + newline
    printf("\nThread <get the number of the thread here> is running"); // writing to the console
    fclose(fptr); // closes the file

    // release the semaphore flah
    
}