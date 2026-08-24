#include "shell.h"

/**
 * handle_builtin - handles built-in commands
 * @argv: command and arguments
 *
 * Return: 1 if a built-in was handled, 0 otherwise
 */
int handle_builtin(char **argv)
{
	char **env;

	if (strcmp(argv[0], "exit") == 0)
	{
		free(argv);
		exit(0);
	}

	if (strcmp(argv[0], "env") == 0)
	{
		env = environ;
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return (1);
	}

	return (0);
}
