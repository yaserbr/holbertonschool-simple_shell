#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: exit status
 */
int main(int argc, char **argv)
{
	char *line;
	int line_number = 0;
	int status = 0;
	int command_status;

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
			command_status = execute_command(line, argv[0], line_number);

			if (command_status == EXIT_SHELL)
			{
				free(line);
				break;
			}

			status = command_status;
		}

		free(line);
	}

	return (status);
}
