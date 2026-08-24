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
 * trailing newline so the result can be split into command tokens.
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
 * @line: the command line to run, may include arguments
 * @prog_name: the shell's own program name, used for error messages
 *
 * Description: splits the line into a command and its arguments,
 * then forks a child process to run it with execve. The parent
 * waits for the child to finish before returning to the main loop.
 * A line with no tokens (blank or whitespace-only) is a no-op.
 */
void execute_command(char *line, char *prog_name)
{
	pid_t child_pid;
	int status;
	char **argv;

	argv = split_line(line);
	if (argv == NULL || argv[0] == NULL)
	{
		free(argv);
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(prog_name);
		free(argv);
		return;
	}

	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(prog_name);
			_exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}

	free(argv);
}
