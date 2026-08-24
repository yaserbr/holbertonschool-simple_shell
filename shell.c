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
 * execute_child - executes a command in the child process
 * @argv: command and arguments
 * @path: full path of the command
 * @prog_name: name of the shell
 */
void execute_child(char **argv, char *path, char *prog_name)
{
	if (execve(path, argv, environ) == -1)
	{
		perror(prog_name);
		_exit(127);
	}
}

/**
 * run_command - creates a child and runs a command
 * @argv: command and arguments
 * @path: full path of the command
 * @prog_name: name of the shell
 *
 * Return: nothing
 */
int run_command(char **argv, char *path, char *prog_name)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror(prog_name);
		return (1);
	}

	if (child_pid == 0)
		execute_child(argv, path, prog_name);

	waitpid(child_pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
/**
 * execute_command - creates a child and executes a command
 * @line: command line
 * @prog_name: name of the shell
 * @line_number: number of the command line
 *
 * Return: exit status of the command
 */
int execute_command(char *line, char *prog_name, int line_number)
{
	char **argv;
	char *path;
	int status;

	argv = split_line(line);
	if (argv == NULL || argv[0] == NULL)
	{
		free(argv);
		return (0);
	}

	if (handle_builtin(argv))
	{
		free(argv);
		return (0);
	}

	path = find_command(argv[0]);
	if (path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_number, argv[0]);
		free(argv);
		return (127);
	}

	status = run_command(argv, path, prog_name);

	free(path);
	free(argv);

	return (status);
}
