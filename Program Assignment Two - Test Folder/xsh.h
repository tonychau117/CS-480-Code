#ifndef XSH_H
#define XSH_H

void trim_newline(char *str); // trims the input
int split_pipes(char *input, char *commands[]); // neatly splits the input and stores it in the *commands array
void parse_args(char *command, char **args); // parses any needed command into args
void execute_single_command(char *command); // runs a single command
void execute_piped_commands(char *commands[], int num_cmds); // runs multiple commands at once

#endif
