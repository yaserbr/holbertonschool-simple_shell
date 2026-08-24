#include "shell.h"

/**
 * handle_builtin - handles built-in commands
 * @argv: command and arguments
 *
 * Return: 1 if exit, 2 if env, 0 otherwise
 */
int handle_builtin(char **argv)
{
	char **env;

	if (strcmp(argv[0], "exit") == 0)
		return (1);

	if (strcmp(argv[0], "env") == 0)
	{
		env = environ;
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return (2);
	}

	return (0);
}

/**
 * command_error - prints an error for an unknown command
 * @prog_name: shell name
 * @line_number: command line number
 * @command: command name
 *
 * Return: 127
 */
int command_error(char *prog_name, int line_number, char *command)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
		prog_name, line_number, command);
	return (127);
}
