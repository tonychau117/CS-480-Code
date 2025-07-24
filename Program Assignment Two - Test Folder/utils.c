#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "xsh.h"

#define MAX_ARGS 64

void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

int split_pipes(char *input, char *commands[]) {
    int count = 0;
    char *token = strtok(input, "|");
    while (token != NULL && count < MAX_ARGS) {
        while (*token == ' ') token++;  // skip leading space
        commands[count++] = token;
        token = strtok(NULL, "|");
    }
    commands[count] = NULL;
    return count;
}

void parse_args(char *command, char **args) {
    int i = 0;
    args[i] = strtok(command, " ");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " ");
    }
    args[i] = NULL;
}

void execute_single_command(char *command) {
    char *args[MAX_ARGS];
    parse_args(command, args);

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
    }
}

void execute_piped_commands(char *commands[], int num_cmds) {
    int i, fd[2], in_fd = 0;

    for (i = 0; i < num_cmds; ++i) {
        pipe(fd);
        pid_t pid = fork();

        if (pid == 0) {
            dup2(in_fd, 0);
            if (i < num_cmds - 1)
                dup2(fd[1], 1);
            close(fd[0]);

            char *args[MAX_ARGS];
            parse_args(commands[i], args);
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        } else if (pid < 0) {
            perror("fork failed");
            return;
        } else {
            wait(NULL);
            close(fd[1]);
            in_fd = fd[0];
        }
    }
}
