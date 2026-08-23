#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the shell's own program name
 *
 * Description: reads one command per line in a loop, forks a child
 * process to execute it, and waits for the child to finish before
 * looping back. Exits on end-of-file (Ctrl+D).
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;

	(void)argc;

	while (1)
	{
		print_prompt();
		line = read_line();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] != '\0')
			execute_command(line, argv[0]);

		free(line);
	}

	return (0);
}
