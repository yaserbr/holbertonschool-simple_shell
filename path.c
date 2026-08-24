#include "shell.h"

/**
 * get_path - gets the PATH variable
 *
 * Return: pointer to PATH value, or NULL
 */
char *get_path(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
	}

	return (NULL);
}

/**
 * build_path - builds a full command path
 * @directory: directory from PATH
 * @command: command name
 *
 * Return: full path, or NULL on failure
 */
char *build_path(char *directory, char *command)
{
	char *path;
	size_t length;

	length = strlen(directory) + strlen(command) + 2;

	path = malloc(length);
	if (path == NULL)
		return (NULL);

	sprintf(path, "%s/%s", directory, command);

	return (path);
}

/**
 * find_command - searches for a command in PATH
 * @command: command name
 *
 * Return: full path if found, or NULL
 */
char *find_command(char *command)
{
	char *path;
	char *copy;
	char *directory;
	char *full_path;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));

		return (NULL);
	}

	path = get_path();
	if (path == NULL)
		return (NULL);

	copy = strdup(path);
	if (copy == NULL)
		return (NULL);

	directory = strtok(copy, ":");

	while (directory != NULL)
	{
		full_path = build_path(directory, command);

		if (full_path != NULL && access(full_path, X_OK) == 0)
		{
			free(copy);
			return (full_path);
		}

		free(full_path);
		directory = strtok(NULL, ":");
	}

	free(copy);

	return (NULL);
}
