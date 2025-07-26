#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "xsh.h" // header

#define MAX_ARGS 64 // the max amt of arguments

// helper function to trim the passed in string
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

// splits the inputted string
int split_pipes(char *input, char *commands[]) {
    int count = 0; // holds the count of the amt of commands to be returned
    char *token = strtok(input, "|"); // sections off the first possible segment, holds the segment of the input string
    while (token != NULL && count < MAX_ARGS) { // while loop to 
        while (*token == ' ') { // checking spaces
            token++; // increments token by one if met
        }
        commands[count++] = token; // indexes token in the commands array
        token = strtok(NULL, "|"); // finds the next section of " | " in the inputted string
    }
    commands[count] = NULL; // NULL signifies the end
    return count; // returns the # of commands used
}

// helper function for the parsing
void parse_args(char *command, char **args) {
    int i = 0; // starting point
    args[i] = strtok(command, " "); // first index in args
    while (args[i] != NULL && i < MAX_ARGS - 1) { // while loop
        args[++i] = strtok(NULL, " "); // jumps to the next index, splits the string at the next found space
    }
    args[i] = NULL; // NULL signifies the ending
}


// helper function that executes a single command
void execute_single_command(char *command) {
    char *args[MAX_ARGS];
    parse_args(command, args); // calls on parse function

    pid_t pid = fork(); // process id from forking
    if (pid == 0) { // if the process id meets cond of 0
        execvp(args[0], args); // running exec
        perror("exec failed"); // prints the error msg
        exit(1); // exits bc failed
    } else if (pid > 0) {
        wait(NULL); // waits for process to complete before moving on
    } else {
        perror("fork failed"); // error msg
    }
}

// helper function that executes multiple commands 
void execute_piped_commands(char *commands[], int num_cmds) {

    // declares and initializes two vars to be used - fd for pipe and in_fd for the next command
    int fd[2] = 0;
    int in_fd = 0;

    // loop to run
    for (i = 0; i < num_cmds; ++i) {
        pipe(fd); // creation of pipe
        pid_t pid = fork(); // process id is forked

        if (pid == 0) {
            dup2(in_fd, 0); // sets it to wahtever the last command was
            if (i < num_cmds - 1) 
                dup2(fd[1], 1); // if its not the last command, change what it is set to
            close(fd[0]); // closes

            char *args[MAX_ARGS];
            parse_args(commands[i], args); // parsing
            execvp(args[0], args); // runs exec
            perror("exec failed"); // error msg
            exit(1); // exits bc failure
        } else if (pid < 0) {
            perror("fork failed"); // error msg + returns since failure
            return; 
        } else {
            wait(NULL); // waiting for completion
            close(fd[1]); 
            in_fd = fd[0]; // closes + save and waits for th e next command 
        }
    }
}
