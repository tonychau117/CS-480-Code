#include <stdio.h>
#include <unistd.h> // needed to get the process id

#include <semaphore.h> // import for semaphore flag

int main()
{
    FILE *fptr;

    fptr = fopen("QUOTE.txt", "w"); // creates the QUOTE.txt file, w used to write in it -> if doesnt exist itll amke one
    pid_t processID = getpid();     // gets the process ID

    fprintf(fptr, "The ProcessID is" + processID);
    fprintf(fptr, "\r\n"); // carriage return and newline, carriage return with \r
    fclose(fptr);          // closes the file that we are writing in

    // creating the semaphore FLAG
    sem_t sem_flag;
    sem_init(&sem_flag, 0, 0);

    printf("Hello World");
}