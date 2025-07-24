#include <stdio.h>
#include <string.h>
#include "xsh.h"

#define MAX_LINE 1024
#define MAX_ARGS 64

void print_prompt() {
    printf("cssc0000%% ");
    fflush(stdout);
}

int main() {
    char input[MAX_LINE];

    while (1) {
        print_prompt();

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        trim_newline(input);

        if (strcmp(input, "") == 0)
            continue;

        if (strcmp(input, "exit") == 0)
            break;

        char *commands[MAX_ARGS];
        int num_cmds = split_pipes(input, commands);

        if (num_cmds == 1) {
            execute_single_command(commands[0]);
        } else {
            execute_piped_commands(commands, num_cmds);
        }
    }

    return 0;
}
