#include "shell.h"

/**
 * print_prompt - displays the shell prompt when running interactively
 *
 * Description: nothing is printed when standard input is not a
 * terminal (e.g. piped input), so non-interactive mode stays silent.
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

/**
 * read_line - reads one line of input from standard input
 *
 * Description: uses getline to read an entire line, then strips the
 * trailing newline so the result can be used directly as a command.
 *
 * Return: a pointer to the line read, or NULL on end of file (Ctrl+D)
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - forks a child process and executes a command
 * @line: the command to run (a single word, no arguments)
 * @prog_name: the shell's own program name, used for error messages
 *
 * Description: the parent process waits for the child to finish
 * before returning control to the main loop. If the command cannot
 * be executed, an error is printed and the child exits without
 * affecting the parent shell.
 */
void execute_command(char *line, char *prog_name)
{
	pid_t child_pid;
	int status;
	char *argv[2];

	argv[0] = line;
	argv[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(prog_name);
		return;
	}

	if (child_pid == 0)
	{
		if (execve(line, argv, environ) == -1)
		{
			perror(prog_name);
			_exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
