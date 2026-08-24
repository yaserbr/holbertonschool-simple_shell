#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "($) "

extern char **environ;

void print_prompt(void);
char *read_line(void);
void trim_line(char *line);
void execute_command(char *line, char *prog_name);

#endif /* SHELL_H */
