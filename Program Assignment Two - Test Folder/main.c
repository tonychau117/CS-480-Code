#include <stdio.h>
#include <string.h>
#include "xsh.h" // header
#include <stdbool.h> // boolean control

#define MAX_LINE 1024 // max length for our lines
#define MAX_ARGS 64 // max number for the arguments

// main
int main() {
    char input[MAX_LINE]; // set the input

    bool loop = true; // setting the loop cond

    while (loop) { // while loop for "infinite" runtime
        printf("cssc0000%% "); // prints the cssc of the user

        if (fgets(input, sizeof(input), stdin) == NULL) // reading for user input, 
            break; // exits the loop if it is invalid or error occurs

        trim_newline(input); // shortens the inputs to avoid any potential errors

        if (strcmp(input, "") == 0) // if there is no input entered
            continue; // just continue as normal

        if (strcmp(input, "exit") == 0)
            break; // user typing "exit" to end the shell itself

        char *commands[MAX_ARGS]; // holds the commands
        int num_cmds = split_pipes(input, commands); // calls on helper function to check for the # of commands

        if (num_cmds == 1) { // if else statement to control pipes to see wwhere single or many pipes are needed
            execute_single_command(commands[0]);
        } else {
            execute_piped_commands(commands, num_cmds);
        }
    }

    return 0; // returns 0 to signal the end
}
