#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	int line_number = 0;
	int status = 0;

	(void)argc;

	while (1)
	{
		print_prompt();
		line = read_line();

		if (line == NULL)
			break;

		line_number++;

		if (line[0] != '\0')
		{
			status = execute_command(line, argv[0], line_number);

			if (status == EXIT_SHELL)
			{
				free(line);
				return (0);
			}
		}

		free(line);
	}

	return (status);
}
