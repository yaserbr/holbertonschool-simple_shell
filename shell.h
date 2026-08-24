#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "($) "
#define EXIT_SHELL -1

extern char **environ;

void print_prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute_command(char *line, char *prog_name, int line_number);

char *get_path(void);
char *build_path(char *directory, char *command);
char *find_command(char *command);
void execute_child(char **argv, char *path, char *prog_name);

int run_command(char **argv, char *path, char *prog_name);
int handle_builtin(char **argv);
int command_error(char *prog_name, int line_number, char *command);

#endif /* SHELL_H */
