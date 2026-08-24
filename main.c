#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: exit status of the shell
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
			status = execute_command(line, argv[0], line_number);

		free(line);
	}

	return (status);
}
