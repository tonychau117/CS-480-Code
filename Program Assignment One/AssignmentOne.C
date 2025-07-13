#include <stdio.h>
#include <unistd.h>



int  main(){
    FILE *fptr;

    fptr = fopen("QUOTE.txt", "w"); // creates the QUOTE.txt file, w used to write in it -> if doesnt exist itll amke one

    printf("Hello World");
}