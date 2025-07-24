#ifndef XSH_H
#define XSH_H

void trim_newline(char *str);
int split_pipes(char *input, char *commands[]);
void parse_args(char *command, char **args);
void execute_single_command(char *command);
void execute_piped_commands(char *commands[], int num_cmds);

#endif
